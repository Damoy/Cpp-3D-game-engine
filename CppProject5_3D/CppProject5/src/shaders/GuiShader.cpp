#include "GUIShader.h"



const char* GUIShader::POSITION_VAR_NAME = "position";
const char* GUIShader::TEXTURE_COORDS_VAR_NAME = "textureCoords";
const char* GUIShader::VERTEX_SHADER_PATH = "res/shaders/GUIVertexShader.vs";
const char* GUIShader::FRAGMENT_SHADER_PATH = "res/shaders/GUIFragmentShader.fs";

GUIShader::GUIShader()
	: ShaderProgram(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH){

	bindAttributes();
	getAllUniformVariables();
}

GUIShader::~GUIShader(){

}

void GUIShader::bindAttributes() const {
	bindAttribute(0, POSITION_VAR_NAME);
	bindAttribute(1, TEXTURE_COORDS_VAR_NAME);
}

void GUIShader::getAllUniformVariables() {
	transformationMatrixlocation = ShaderProgram::getUniformLocation("transformationMatrix");
}

void GUIShader::loadTransformationMatrix(glm::mat4 matrix) const {
	ShaderProgram::loadMatrix4f(transformationMatrixlocation, matrix);
}

