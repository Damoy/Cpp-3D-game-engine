#include "EntityShader.h"
#include "renderEngine\MainRenderer.h"
#include "utils\logs\Logs.h"


// paths
const char* EntityShader::VERTEX_SHADER_PATH = "res/shaders/entityVertexShader.vs";
const char* EntityShader::FRAGMENT_SHADER_PATH = "res/shaders/entityFragmentShader.fs";

EntityShader::EntityShader()
	: SampleShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {

	// I find this very weird, 
	// I can call an inherited virtual method here which does nothing
	// but my father already did call the same one, which did something,
	// so if you don't know you inherit from SampleShader you can think
	// the below methods are local private ones...
	getAllUniformVariables();
	bindAttributes();
	Logs::println("EntityShader successfully loaded.");
	Logs::println();
}

EntityShader::~EntityShader() {
}

void EntityShader::bindAttributes() const {
}

void EntityShader::getAllUniformVariables() {
}



