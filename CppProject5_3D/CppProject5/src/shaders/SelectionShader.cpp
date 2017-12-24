#include "SelectionShader.h"
#include "renderEngine\WindowManager.h"

const char* SelectionShader::VERTEX_SHADER_PATH = "res/shaders/selectionVertexShader.vs";
const char* SelectionShader::FRAGMENT_SHADER_PATH = "res/shaders/selectionFragmentShader.fs";

SelectionShader::SelectionShader()
	: SampleShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {

}

SelectionShader::~SelectionShader() {
}

void SelectionShader::getAllUniformVariables() {
}

void SelectionShader::bindAttributes() const {
}
