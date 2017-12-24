#include "MapShader.h"
#include "utils\logs\Logs.h"

const char* MapShader::VERTEX_SHADER_PATH = "res/shaders/mapVertexShader.vs";
const char* MapShader::FRAGMENT_SHADER_PATH = "res/shaders/mapFragmentShader.fs";

MapShader::MapShader()
	: SampleShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {

	getAllUniformVariables();
	bindAttributes();
	Logs::println("EntityShader successfully loaded.");
	Logs::println();
}

MapShader::~MapShader() {
}

void MapShader::bindAttributes() const {
}

void MapShader::getAllUniformVariables() {
}

