#include "MainRenderer.h"
#include "renderEngine\WindowManager.h"
#include "models\ModelBank.h"

#include "gameEngine\GameEngine.h"


MainRenderer::MainRenderer(GLFWwindow* win, World* gameWorld, Player* player, glm::mat4 proj)
	: window(win), world(gameWorld), mainPlayer(player), playerCamera(player->getCamera()){

	glm::mat4 projectionMatrix = proj;

	// create the renderers shaders
	entityRendererShader = new EntityShader();
	mapRendererShader = new MapShader();
	// textRendererShader = new TextShader();
	selectionRendererShader = new SelectionShader();
	guiRendererShader = new GUIShader();

	// get a reference to the main light: the sun
	mainLight = &Configs::SUN;

	// get a reference to the current level
	Level* currentLevel = world->getCurrentLevel();
	if (currentLevel == nullptr)
		throw std::runtime_error("Level cannot be null !");

	// get a reference to the current level's map
	Map* map = currentLevel->getMap();

	// get a reference to the level entities
	std::map<TexturedModel*, std::vector<Entity*>*>* texTowersMap = currentLevel->getTexTowerMap();
	std::map<TexturedModel*, std::vector<Entity*>*>* texEnemiesMap = currentLevel->getTexEnemiesMap();
	std::map<TexturedModel*, std::vector<Entity*>*>* texProjectilesMap = currentLevel->getTexProjectilesMap();

	// creates the renderers
	entityRenderer = new EntityRenderer(entityRendererShader, projectionMatrix, playerCamera, mainLight);
	mapRenderer = new MapRenderer(mapRendererShader, projectionMatrix, playerCamera, map, mainLight);
	selectionRenderer = new SelectionRenderer(selectionRendererShader, world, projectionMatrix, playerCamera, mainLight);
	// textRenderer = new TextRenderer(textRendererShader, playerCamera);
	guiRenderer = new GUIRenderer(guiRendererShader);

}

MainRenderer::~MainRenderer(){
	// delete shaders
	delete entityRendererShader;
	delete mapRendererShader;
	// delete textRendererShader;
	delete selectionRendererShader;
	delete guiRendererShader;

	// delete renderers
	delete entityRenderer;
	delete mapRenderer;
	// delete textRenderer;
	delete selectionRenderer;
	delete guiRenderer;

}

void MainRenderer::prepare() const {
	// clear the screen by the 'sky color'
	// a skybox would have been awesome but not the timee !
	glClearColor(Configs::SKY_RED_COMP, Configs::SKY_GREEN_COMP, Configs::SKY_BLUE_COMP, Configs::SKY_ALPHA_COMP);
	// to avoid invisible vertices rendering
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// depth
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainRenderer::swapBuffers() const {
	glfwSwapBuffers(window);
}

void MainRenderer::render() const {
	prepare();

	// all renderers activities
	mapRenderer->render();
	entityRenderer->render();
	selectionRenderer->render();
	// textRenderer->render();
	guiRenderer->render();

	swapBuffers();
}

void MainRenderer::cleanUp() const{
	mapRendererShader->cleanUp();
	entityRendererShader->cleanUp();
	selectionRendererShader->cleanUp();
	// textRendererShader->cleanUp();
	guiRendererShader->cleanUp();
}



