#include <iostream>

#include "SampleShader.h"
#include "utils\logs\Logs.h"
#include "utils\maths\Maths.h"
#include "gameEngine\Configs.h"

const char* SampleShader::POSITION_VAR_NAME = "position";
const char* SampleShader::COLOR_VAR_NAME = "color";
const char* SampleShader::TEXTURE_COORDS_VAR_NAME = "textureCoords";
const char* SampleShader::NORMALS_VAR_NAME = "normal";

SampleShader::SampleShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	: ShaderProgram(vertexShaderPath, fragmentShaderPath) {
	// SO BAD THAT WE CANT CALL VIRTUAL PURE FUNCTION -___-
	bindAttributes();
	Logs::println("SampleShader attributes bound.");
	getAllUniformVariables();
	Logs::println("SampleShader transformation matrix variable get.");
	Logs::println("SampleShader program successfully loaded.");
}

SampleShader::~SampleShader() {
}

void SampleShader::getAllUniformVariables() {
	lightPositionLocation = ShaderProgram::getUniformLocation("lightPosition");
	lightColorLocation = ShaderProgram::getUniformLocation("lightColor");

	transformationMatrixLocation = getUniformLocation("transformationMatrix");
	projectionMatrixLocation = ShaderProgram::getUniformLocation("projectionMatrix");
	viewMatrixLocation = ShaderProgram::getUniformLocation("viewMatrix");
}

void SampleShader::loadTransformationMatrix(glm::mat4 matrix4f) const {
	loadMatrix4f(transformationMatrixLocation, matrix4f);
}

void SampleShader::bindAttributes() const {
	bindAttribute(0, POSITION_VAR_NAME);
	bindAttribute(1, TEXTURE_COORDS_VAR_NAME);
	bindAttribute(2, NORMALS_VAR_NAME);
}

void SampleShader::loadProjectionMatrix(const float* matrix4f) const {
	ShaderProgram::loadMatrix4f(projectionMatrixLocation, matrix4f);
}

// y, some copies, no problem
void SampleShader::loadProjectionMatrix(glm::mat4 projectionMatrix) const {
	ShaderProgram::loadMatrix4f(projectionMatrixLocation, glm::value_ptr(projectionMatrix));
}

void SampleShader::loadProjectionMatrix() const {
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(Configs::FOV), Configs::ASPECT_RATIO, Configs::NEAR_PLANE, Configs::FAR_PLANE);
	ShaderProgram::loadMatrix4f(projectionMatrixLocation, glm::value_ptr(projectionMatrix));
}

void SampleShader::loadViewMatrix(Camera* camera) const {
	glm::mat4 viewMatrix = camera->getViewMatrix();
	ShaderProgram::loadMatrix4f(viewMatrixLocation, glm::value_ptr(viewMatrix));
}

void SampleShader::loadLight(Light* light) const{
	if (light == nullptr) return;

	Color* lightColor = light->getColor();
	glm::vec3 lp = light->getPosition();

	ShaderProgram::loadVector3f(lightPositionLocation, lp);
	ShaderProgram::loadVector3f(lightColorLocation, lightColor->getR(), lightColor->getG(), lightColor->getB());
}