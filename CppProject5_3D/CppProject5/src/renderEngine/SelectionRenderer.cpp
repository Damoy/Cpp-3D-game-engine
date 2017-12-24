#include "SelectionRenderer.h"
#include "utils\maths\Maths.h"
#include "input\MouseTransformer.h"


SelectionRenderer::SelectionRenderer(SelectionShader* s, World* wow, glm::mat4 proj, Camera* cam, Light* ligh)
	: Renderer(s), playerCamera(cam), projectionMatrix(proj), light(ligh), world(wow) {

	// references to pre-generated selection models
	baseSelectionModel = ModelBank::Models::tileSelectionModel;	
	sampleTowerSelectionModel = ModelBank::Models::sampleSelectionModel;
	intelligentTowerSelectionModel = ModelBank::Models::intelligentSelectionModel;
	currentModel = baseSelectionModel;

	// proj matrix load
	shader->start();
	((SelectionShader*)shader)->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

SelectionRenderer::~SelectionRenderer() {
}

void SelectionRenderer::prepare() const {
	// view matrix load
	((SampleShader*)shader)->loadViewMatrix(playerCamera);
}

// Get current model depending on the current player tower selection
TexturedModel* SelectionRenderer::getCurrentModel() const {
	TexturedModel* model = nullptr;
	GameMemory::TowerSelected towerSelected = GameMemory::getTowerSelected();
	if (towerSelected == GameMemory::SAMPLE) {
		model = sampleTowerSelectionModel;
	}
	else if (towerSelected == GameMemory::INTELLIGENT) {
		model = intelligentTowerSelectionModel;
	}
	else {
		model = baseSelectionModel;
	}

	return model;
}

void SelectionRenderer::render() const {
	shader->start();
	prepare();
	renderSelection();
	shader->stop();
}

void SelectionRenderer::renderSelection() const {
	Level* level = world->getCurrentLevel();
	// one of the two main uses of the collision point is the selection rendering
	glm::vec3 collisionPoint = MouseTransformer::getCollisionPointOnLevelMap(level, playerCamera, projectionMatrix);

	if (MouseTransformer::isNull(collisionPoint)) {
		return;
	}

	if (collisionPoint.x < level->getX() || collisionPoint.x > level->getX() + level->getWidth() || collisionPoint.z < level->getZ() || collisionPoint.z > level->getZ() + level->getWidth()) {
		return;
	}

	TexturedModel* model = getCurrentModel();

	RawModel* tRawModel = model->getRawModel();

	glBindVertexArray(tRawModel->getVaoID());
	// positions
	glEnableVertexAttribArray(0);
	// texture coords
	glEnableVertexAttribArray(1);
	// normals
	glEnableVertexAttribArray(2);

	float mx = collisionPoint.x;
	float my = collisionPoint.y + 0.01f;
	float mz = collisionPoint.z;

	glm::mat4 transfoMatrix = Maths::generateTransformationMatrix4f(mx, my, mz, 0.0f, 0.0f, 0.0f, 1.0f);

	((SampleShader*)shader)->loadLight(light);
	((SampleShader*)shader)->loadTransformationMatrix(transfoMatrix);

	// activate one GL texture
	// sampler2D uses this
	glActiveTexture(GL_TEXTURE0);
	// bind our texture to it
	glBindTexture(GL_TEXTURE_2D, model->getTextureID());

	if (tRawModel->indexed()) {
		glDrawElements(GL_TRIANGLES, tRawModel->getVerticesNumber(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, tRawModel->getVerticesNumber());
	}

	// disables vbos and and vao
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

