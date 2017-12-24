#include "GL\glew.h"

#include "GUIRenderer.h"
#include "models\ModelBank.h"
#include "utils\maths\Maths.h"
#include "loaders\ModelLoader.h"
#include "gameEngine\Configs.h"


GUIRenderer::GUIRenderer(GUIShader* shader)
	: Renderer(shader){

	// the guis shared model
	// assuming width >= height
	float width = 0.1f;
	float height = Configs::ASPECT_RATIO * width;

	// generates the gui quad model
	rawQuadModel = ModelLoader::getInstance()->loadGUIToVAO(ModelBank::Vertices::generateRectangleVertices(width, height), ModelBank::Vertices::REC_VERTICES_SIZE, ModelBank::TextureCoords::RECTANGLE_TEX_COORDS, ModelBank::TextureCoords::REC_TEX_COORDS_SIZE);

	// sample tower gui texture
	ModelTexture* texture = TextureLoader::generateModelTexture(ModelBank::Textures::SAMPLE_TOWER_TEXTURE_128x128);

	// sampler tower gui model
	sampleTowerGUI = TextureLoader::generateGUITexture(ModelBank::Textures::SAMPLE_TOWER_TEXTURE_128x128, glm::vec2(-0.030f, -0.95f), glm::vec2(0.25f, 0.25f));

	// intelligent tower gui model
	intelligentTowerGUI = TextureLoader::generateGUITexture(ModelBank::Textures::INTELLIGENT_TOWER_TEXTURE_128x128, glm::vec2(0.030f, -0.95f), glm::vec2(0.25f, 0.25f));

	// guis
	guis = new std::vector<GUITexture*>();
	guis->push_back(sampleTowerGUI);
	guis->push_back(intelligentTowerGUI);
}

GUIRenderer::~GUIRenderer(){
}

void GUIRenderer::prepare() const {

}

void GUIRenderer::render() const {
	// starts the shader
	shader->start();
	// prepare the rendering
	prepare();
	// render
	renderTextures(guis);
	// stops the shader
	shader->stop();
}

void GUIRenderer::renderTextures(std::vector<GUITexture*>* guis) const {
	// binding the quad model
	glBindVertexArray(rawQuadModel->getVaoID());
	// enabling positions
	glEnableVertexAttribArray(0);
	// enabling texture cords
	glEnableVertexAttribArray(1);

	// for alpha blending: https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glBlendFunc.xml
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// disabling to allow gui visibility
	glDisable(GL_DEPTH_TEST);

	// actual rendering
	std::vector<GUITexture*>::iterator guisIT;

	// for all the guis:
	// we activate the first texture unit,
	// bind the gui texture,
	// generate the gui transformation matrix and load it to the gui shader
	// and render the data
	for (guisIT = guis->begin(); guisIT != guis->end(); guisIT++) {
		GUITexture* gui = (*guisIT);
		// activate texture unit
		// actually, the texture atlas may be totally useless
		glActiveTexture(TextureLoader::getGUITextureAtlas()); 
		// bind the texture
		glBindTexture(GL_TEXTURE_2D, gui->getID());
		// generate the transformation matrix from 2D data
		glm::vec2 guiPos = gui->getPosition();
		glm::vec2 guiScale = gui->getScale();
		glm::mat4 transMatrix = Maths::generateTransformationMatrix4f(glm::vec3(guiPos.x, guiPos.y, 1.0f),
			0.0f, 0.0f, 0.0f, guiScale.x, guiScale.y , 0.0f);

		// load it
		((GUIShader*)shader)->loadTransformationMatrix(transMatrix);
		// render
		glDrawArrays(GL_TRIANGLE_STRIP, 0, rawQuadModel->getVerticesNumber());
	}

	// disable alpha blending
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	// disabling
	// enabling texture cords
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void GUIRenderer::cleanUp() const {
	shader->cleanUp();
}

