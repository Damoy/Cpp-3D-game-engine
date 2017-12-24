#pragma once

#include <map>
#include <vector>

#include "GL\glew.h"

#include "glut.h"

#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"
#include "GLM\gtc\matrix_transform.hpp"

#include "EntityRenderer.h"
#include "GuiRenderer.h"
#include "MapRenderer.h"
#include "SelectionRenderer.h"
#include "TextRenderer.h"

#include "entities\Entity.h"

#include "shaders\EntityShader.h"
#include "shaders\GuiShader.h"
#include "shaders\SelectionShader.h"
#include "shaders\MapShader.h"
#include "shaders\TextShader.h"

#include "world\Level1.h"
#include "world\World.h"

/*
	The MainRenderer should be the only renderer called by user code.
	It generates different renderers for different usages and call their render methods.
*/
class MainRenderer{
private:
	// window
	GLFWwindow* window;

	// renderers
	EntityRenderer* entityRenderer;
	MapRenderer* mapRenderer;
	// player tile selection
	SelectionRenderer* selectionRenderer;
	GUIRenderer* guiRenderer;

	// shaders
	EntityShader* entityRendererShader;
	MapShader* mapRendererShader;
	// player tile selection
	SelectionShader* selectionRendererShader;
	GUIShader* guiRendererShader;

	// world reference
	World* world;

	// game elements
	Map* map;
	// game entities reference
	std::map<TexturedModel*, std::vector<Entity*>*>* gameEntities;

	// the main light
	Light* mainLight;

	// player and its camera
	Player* mainPlayer;
	Camera* playerCamera;

	// projection matrix
	glm::mat4 projectionMatrix;

public:

	MainRenderer(GLFWwindow* window, World* world, Player* player, glm::mat4 projectionMatrix);
	~MainRenderer();

	// Prepares the rendering
	void prepare() const;
	// Renders to screen the computed graphical buffer
	void swapBuffers() const;
	// Renders everything
	void render() const;
	// Clean up the renderer
	void cleanUp() const;

};

