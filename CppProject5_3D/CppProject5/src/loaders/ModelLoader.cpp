#include <iostream>

#include "ModelLoader.h"
#include "models\ModelBank.h"
#include "world\Map.h"

ModelLoader* ModelLoader::instance = new ModelLoader();

ModelLoader* ModelLoader::getInstance() {
	if (instance == nullptr)
		instance = new ModelLoader();
	return instance;
}

ModelLoader* ModelLoader::getInstance(const char* loadingMsg) {
	if (instance == nullptr)
		instance = new ModelLoader();
	Logs::println(loadingMsg);
	return instance;
}

bool ModelLoader::deleteInstance() {
	if (instance == nullptr)
		return false;
	delete instance;
	instance = nullptr;
	return true;
}

/* --- [MEMORY]--- */
ModelLoader::ModelLoader() {
	vaos = new std::vector<unsigned int>();
	vbos = new std::vector<unsigned int>();
	textures = new std::vector<unsigned int>();
}

/* --- [MEMORY]--- */
ModelLoader::~ModelLoader() {
	for (unsigned int ui = 0; ui < vaos->size(); ui++) {
		glDeleteVertexArrays(1, &vaos->at(ui));
	}

	for (unsigned int ui = 0; ui < vbos->size(); ui++) {
		glDeleteBuffers(1, &vbos->at(ui));
	}

	for (unsigned int ui = 0; ui < textures->size(); ui++) {
		glDeleteTextures(1, &textures->at(ui));
	}

	delete vaos;
	delete vbos;
	delete textures;
}


/*
	--- [MEMORY USING]---
	Loads model data to a model object.
	Generates a new RawModel object.
	@positions corresponds to the model vertices,
	@positionSize is the size, in bytes, of the positions buffer,
	@texCoords correponds to the model texture coordinates (to establish the model's texture),
	@texCoordsSize is the size, in bytes, of the texCoords buffer,
	@indices corresponds to the model indices buffer, which is used to improve rendering performance,
	@indicesSize is the size, in bytes, of the indices buffer;
	All size parameters can be obtained using sizeof(buffer) (before enter in the method body).
*/

RawModel* ModelLoader::loadToVAO(float* positions, unsigned int positionsSize, float* normals, unsigned int normalsSize, float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize) {

	// generates and loads a new VAO
	int vaoID = generateVAO();
	Logs::println("Model's VAO generated.");
	// binds the model indices
	bindIndicesBuffer(indices, indicesSize);
	Logs::println("Model's indices buffer bound.");

	// [IE] we put 3D coordinates 
	// but it will be used as 2D ones
	// stores the model's positions
	storeDataInAttributeList(0, 3, positions, positionsSize);
	Logs::println("Model's position vertices stored.");
	// stores the model's texture coordinates 
	storeDataInAttributeList(1, 2, texCoords, texCoordsSize);
	Logs::println("Model's texture coordinates stored.");
	// stores the model's normal attribute,
	// which are used to reflect lights
	storeDataInAttributeList(2, 3, normals, normalsSize);
	// unbind the generated VAO
	unbindVAO();
	Logs::println("Model's VAO unbound.");

	return new RawModel(vaoID, indicesSize / sizeof(float), true);
}


/*
	--- [MEMORY USING]---
	Loads model data to a model object.
	Generates a new TexturedModel object.
	@textureFilePath is the texture file relative to project directory path.
	See RawModel @loadToVAO for more information.
*/
TexturedModel* ModelLoader::loadToVAO(const char* textureFilePath, float* positions, unsigned int positionsSize,
	float* normals, unsigned int normalsSize, float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize, float size) {

	RawModel* model = loadToVAO(positions, positionsSize, normals, normalsSize, texCoords, texCoordsSize, indices, indicesSize);
	Logs::println("Raw model loaded.");
	ModelTexture* modelTexture = TextureLoader::generateModelTexture(textureFilePath);

	Logs::println("Model texture loaded.");
	TexturedModel* texturedModel = new TexturedModel(model, modelTexture, size);
	Logs::println("Textured model loading completed successfully.");
	Logs::println();

	return texturedModel;
}

TexturedModel* ModelLoader::loadToVAO(const char* textureFilePath, float* positions, unsigned int positionsSize,
	float* normals, unsigned int normalsSize, float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize) {

	// generates the model
	RawModel* model = loadToVAO(positions, positionsSize, normals, normalsSize, texCoords, texCoordsSize, indices, indicesSize);
	Logs::println("Raw model loaded.");

	// generate the texture
	ModelTexture* modelTexture = TextureLoader::generateModelTexture(textureFilePath);

	Logs::println("Model texture loaded.");
	TexturedModel* texturedModel = new TexturedModel(model, modelTexture);
	Logs::println("Textured model loading completed successfully.");
	Logs::println();

	return texturedModel;
}

/*
	Generates a new VAO,
	adds it to the vao memory,
	binds it and returns it.
*/
unsigned int ModelLoader::generateVAO() {
	unsigned int vaoID;
	// generates a vao
	glGenVertexArrays(1, &vaoID);
	// puts it in memory
	vaos->push_back(vaoID);
	// binds it
	glBindVertexArray(vaoID);
	return vaoID;
}

/*
	Generates a new VBO if given buffer type is either
	GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER,
	(if not, throws a runtime error),
	adds it to the vbo memory,
	binds it and returns it.
*/
unsigned int ModelLoader::generateVBO(unsigned int GL_BUFFER_TYPE) {
	Checker::isEqualToOneOf<unsigned int>(GL_BUFFER_TYPE, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER);
	unsigned int vboID;
	// generates a vbo
	glGenBuffers(1, &vboID);
	// puts it in memory
	vbos->push_back(vboID);
	// binds it
	glBindBuffer(GL_BUFFER_TYPE, vboID);
	return vboID;
}

/*
	Binds a model indices buffer.
	Indices buffer are used to __potentially__ reduce the
	memory size used by the program.
*/
void ModelLoader::bindIndicesBuffer(int* indices, unsigned int indicesSize) {
	// generates a VBO ID and stores it to the memory
	// we don't need to manipulate it
	generateVBO(GL_ELEMENT_ARRAY_BUFFER);
	// stores the buffer in the vbo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
}

/*
	Stores some data into an attribute list
	of the VAO currently bound.
	@attrIndex is the attribute list index,
	@dimension is the dimension value of the data,
	@data is the data we want to store,
	@dataSize is the size of the data.
*/
void ModelLoader::storeDataInAttributeList(unsigned int attrIndex, int dimension, float* data, unsigned int dataSize) {
	// generates the vbo ID
	unsigned int vboID = generateVBO(GL_ARRAY_BUFFER);
	// creates and initializes a buffer object's data store
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// defines an array of generic vertex attribute data
	glVertexAttribPointer(attrIndex, dimension, GL_FLOAT, false, 0, 0);
	// unbinds the previously generated buffer
	unbindVBO(GL_ARRAY_BUFFER);
}

/* Unbinds the currently bound VAO. */
void ModelLoader::unbindVAO() const {
	glBindVertexArray(0);
}

/* 
	Unbinds the currently bound VBO of GL_BUFFER_TYPE GL type.
	Yes, if GL implements GL_BUFFER_TYPE, the program does not
	longer compile.
*/
void ModelLoader::unbindVBO(unsigned int GL_BUFFER_TYPE) const {
	Checker::isEqualToOneOf<unsigned int>(GL_BUFFER_TYPE, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_BUFFER_TYPE, 0);
}

/* Disables the VBO data of index @index of the currently bound VAO. */
void ModelLoader::disableVertexAttribArray(int index) const {
	glDisableVertexAttribArray(index);
}

/* Loads a squared model */
TexturedModel* ModelLoader::loadRectangleModel(const char* texturePath, float width, float height) {

	float* recVertices = ModelBank::Vertices::generateRectangleVertices(width, height);
	int* recIndices = ModelBank::Indices::RECTANGLE_INDICES;
	float* recTexCoords = ModelBank::TextureCoords::RECTANGLE_TEX_COORDS;
	float* recNormals = ModelBank::Normals::RECTANGLE_NORMALS;

	unsigned int recVertSize = ModelBank::Vertices::REC_VERTICES_SIZE;
	unsigned int recIndicesSize = ModelBank::Indices::REC_INDICES_SIZE;
	unsigned int recTexCoordsSize = ModelBank::TextureCoords::REC_TEX_COORDS_SIZE;
	unsigned int recNormalsSize = ModelBank::Normals::RECTANGLE_NORMALS_SIZE;

	return loadToVAO(texturePath, recVertices, recVertSize, recNormals, recNormalsSize, recTexCoords, recTexCoordsSize, recIndices, recIndicesSize);
}

// Loads a map model
TexturedModel* ModelLoader::loadMap(const char* mapTexture, unsigned int s, unsigned int verticesCount) {
	Logs::println("Map loading...");

	// map size
	unsigned int size = s; // 500
	// edge vertices number
	unsigned int edgeVerticesCount = verticesCount;
	// base area
	unsigned int area = edgeVerticesCount * edgeVerticesCount;
	float fedgeVerticesCount = float(edgeVerticesCount - 1);

	float* vertices = new float[area * 3];
	float* normals = new float[area * 3];
	float* texCoords = new float[area * 2];

	unsigned int vertexPtr = 0;
	for (int z = 0; z < (int) edgeVerticesCount; z++) {
		for (int x = 0; x < (int) edgeVerticesCount; x++) {

			float fz = static_cast<float>(z);
			float fx = static_cast<float>(x);

			// vertices
			vertices[vertexPtr * 3] = fx / fedgeVerticesCount * size;
			vertices[vertexPtr * 3 + 1] = 0.0f; // flat terrain
			vertices[vertexPtr * 3 + 2] = fz / fedgeVerticesCount * size; //  -(fz / 100.0f)

			// normals
			normals[vertexPtr * 3] = 0.0f;
			normals[vertexPtr * 3 + 1] = 1.0f; //Pointing straight up
			normals[vertexPtr * 3 + 2] = 0.0f;

			texCoords[vertexPtr * 2] = fx / fedgeVerticesCount;
			texCoords[vertexPtr * 2 + 1] = fz / fedgeVerticesCount;

			vertexPtr++;
		}
	}

	int* indices = new int[6 * (edgeVerticesCount - 1) * (edgeVerticesCount - 1)];

	// map indices
	unsigned int indexPtr = 0;
	for (int z = 0; z < (int)edgeVerticesCount - 1; z++) {
		for (int x = 0; x < (int)edgeVerticesCount - 1; x++) {
			int topLeft = (z * edgeVerticesCount) + x;
			int topRight = topLeft + 1;
			int bottomLeft = ((z + 1) * edgeVerticesCount) + x;
			int bottomRight = bottomLeft + 1;

			indices[indexPtr++] = topLeft;
			indices[indexPtr++] = bottomLeft;
			indices[indexPtr++] = topRight;
			indices[indexPtr++] = topRight;
			indices[indexPtr++] = bottomLeft;
			indices[indexPtr++] = bottomRight;
		}
	}

	unsigned int verticesSize = area * 3 * sizeof(float);
	unsigned int indicesSize = 6 * (edgeVerticesCount - 1) * (edgeVerticesCount - 1) * sizeof(int);
	unsigned int texCoordsSize = area * 2 * sizeof(float);
	unsigned int normalsSize = area * 3 * sizeof(float);

	return loadToVAO(mapTexture, vertices, verticesSize, normals, normalsSize, texCoords, texCoordsSize, indices, indicesSize);
}

// Loads a cube model, takes the texture path and the size
TexturedModel* ModelLoader::loadCubeModel(const char* texturePath, float size) {
	float* cubeVertices = ModelBank::Vertices::generateCubeVertices(size);
	int* cubeIndices = ModelBank::Indices::CUBE_INDICES;
	float* cubeTexCoords = ModelBank::TextureCoords::CUBE_TEX_COORDS;
	float* cubeNormals = ModelBank::Normals::CUBE_NORMALS;

	unsigned int cubeVertSize = ModelBank::Vertices::CUBE_VERTICES_SIZE;
	unsigned int cubeIndicesSize = ModelBank::Indices::CUBE_INDICES_SIZE;
	unsigned int cubeTexCoordsSize = ModelBank::TextureCoords::CUBE_TEX_COORDS_SIZE;
	unsigned int cubeNormalsSize = ModelBank::Normals::CUBE_NORMALS_SIZE;

	return loadToVAO(texturePath, cubeVertices, cubeVertSize, cubeNormals, cubeNormalsSize, cubeTexCoords, cubeTexCoordsSize, cubeIndices, cubeIndicesSize, size);
}

TexturedModel* ModelLoader::loadFlatRectangleModel(const char* frecTex) {
	return loadMap(frecTex, 1, 6);
}

// For guis (a little buggyyy :/)
RawModel* ModelLoader::loadGUIToVAO(float* positions, unsigned int positionsSize, float* textureCoords, unsigned int textureCoordsSize) {
	unsigned int vaoID = generateVAO();
	// stores the model position
	storeDataInAttributeList(0, 3, positions, positionsSize);
	Logs::println("GUI model's positions stored.");
	storeDataInAttributeList(1, 2, textureCoords, textureCoordsSize);
	Logs::println("GUI model's texture coordinates stored.");
	// unbind the vao used for storing
	unbindVAO();
	// the number of vertices is simply the positions array size here
	// false means we do not use indices
	return new RawModel(vaoID, positionsSize / (3 * sizeof(float)), false);
}

TexturedModel* ModelLoader::loadGUISample(const char* texturePath, float width, float height) {
	float* positions = ModelBank::Vertices::generateRectangleVertices(width, height);
	unsigned int positionsSize = ModelBank::Vertices::REC_VERTICES_SIZE;
	float* textureCoords = ModelBank::TextureCoords::RECTANGLE_TEX_COORDS;
	unsigned int textureCoordsSize = ModelBank::TextureCoords::REC_TEX_COORDS_SIZE;
	
	RawModel* rawModel = loadGUIToVAO(positions, positionsSize, textureCoords, textureCoordsSize);
	Logs::println("GUI raw model loaded.");

	ModelTexture* modelTexture = TextureLoader::generateModelTexture(texturePath);
	TexturedModel* GUImodel = new TexturedModel(rawModel, modelTexture);
	Logs::println("GUI textured model loaded.");
	return GUImodel;
}
