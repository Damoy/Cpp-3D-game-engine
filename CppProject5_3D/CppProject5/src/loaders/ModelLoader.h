#pragma once

#include <iostream>
#include <vector>
#include "models\TexturedModel.h"
#include "loaders\TextureLoader.h"
#include "utils\checkers\Checker.h"
#include "utils\logs\Logs.h"

/*
	The project main model loader.
	The loader will, from meshes (vertices, indices, texture coordinates, normals...)
	generate models.
	As I did not have the time to make a .obj file loader (to add complexes models),
	I used cubic ones everywhere on the game.
	The loader uses openGL methods to store data, activate textures, bind vertex array buffers (vaos)... 
*/
class ModelLoader{
private:

	// storage
	// unused
	std::vector<unsigned int>* vaos;
	std::vector<unsigned int>* vbos;
	std::vector<unsigned int>* textures;

	ModelLoader();
	~ModelLoader();

	// the loader singleton
	static ModelLoader* instance;

private:

	/*
	Generates a new VAO,
	adds it to the vao memory,
	binds it and returns it.
	*/
	unsigned int generateVAO();

	/*
	Generates a new VBO if given buffer type is either
	GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER,
	(if not, throws a runtime error),
	adds it to the vbo memory,
	binds it and returns it.
	*/
	unsigned int generateVBO(unsigned int GL_BUFFER_TYPE);

	/*
	Binds a model indices buffer.
	Indices buffer are used to __potentially__ reduce the
	memory size used by the program.
	*/
	void bindIndicesBuffer(int* indices, unsigned int indicesSize);

	/*
	Stores some data into an attribute list
	of the VAO currently bound.
	@attrIndex is the attribute list index,
	@dimension is the dimension value of the data,
	@data is the data we want to store,
	@dataSize is the size of the data.
	*/
	void storeDataInAttributeList(unsigned int attrIndex, int dimension, float* data, unsigned int dataSize);

	RawModel* loadIndexedRawModel(float* positions, unsigned int posSize, int* indices, unsigned int indicesSize, unsigned int dimension);


	/* Unbinds the currently bound VAO. */
	void unbindVAO() const;

	/*
	Unbinds the currently bound VBO of GL_BUFFER_TYPE GL type.
	Yes, if GL implements GL_BUFFER_TYPE, the program does not
	longer compile.
	*/
	void unbindVBO(unsigned int GL_BUFFER_TYPE) const;

	/* Disables the VBO data of index @index of the currently bound VAO. */
	void disableVertexAttribArray(int index) const;

public:

	static ModelLoader* getInstance();
	static ModelLoader* getInstance(const char* loadingMsg);
	static bool deleteInstance();

	/*
	Loads model data to a model object.
	Generates a new RawModel object.
	positions corresponds to the model vertices,
	positionSize is the size, in bytes, of the positions buffer,
	texCoords correponds to the model texture coordinates (to establish the model's texture),
	texCoordsSize is the size, in bytes, of the texCoords buffer,
	indices corresponds to the model indices buffer, which is used to improve rendering performance,
	indicesSize is the size, in bytes, of the indices buffer;
	All size parameters can be obtained using sizeof(buffer) (before enter in the method body).
	*/
	RawModel* loadToVAO(float* positions, unsigned int positionsSize, float* normals, unsigned int normalsSize,
						float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize);


	/*
	--- [MEMORY USING]---
	Loads model data to a model object.
	Generates a new TexturedModel object.
	@textureFilePath is the texture file relative to project directory path.
	See RawModel @loadToVAO for more information.
	*/
	TexturedModel* loadToVAO(const char* textureFilePath, float* positions, unsigned int positionsSize, float* normals, unsigned int normalsSize,
						float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize);

	TexturedModel* loadToVAO(const char* textureFilePath, float* positions, unsigned int positionsSize,
		float* normals, unsigned int normalsSize, float* texCoords, unsigned int texCoordsSize, int* indices, unsigned int indicesSize, float size);

	TexturedModel* loadRectangleModel(const char* texturePath, float width, float height);

	TexturedModel* loadCubeModel(const char* cubeTexture, float size);

	RawModel* load2DNoIndicNormToVAO(float* positions, unsigned int positionsSize, float* texCoords, unsigned int texCoordsSize);

	// GUI
	TexturedModel* loadFlatRectangleModel(const char* frecTex);

	TexturedModel* loadMap(const char* mapTexture, unsigned int size, unsigned int verticesCount);

	RawModel* loadGUIToVAO(float* positions, unsigned int positionsSize, float* textureCoords, unsigned int textureCoordsSize);

	TexturedModel* loadGUISample(const char* texturePath, float width, float height);
};

