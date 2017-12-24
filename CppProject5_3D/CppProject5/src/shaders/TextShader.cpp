#include "TextShader.h"
#include "renderEngine\WindowManager.h"

const char* TextShader::VERTEX_SHADER_PATH = "res/shaders/textVertexShader.vs";
const char* TextShader::FRAGMENT_SHADER_PATH = "res/shaders/textFragmentShader.fs";

const char* TextShader::POSITION_VAR_NAME = "position";
const char* TextShader::TEXTURE_COORDS_VAR_NAME = "textureCoords";

TextShader::TextShader()
	: ShaderProgram(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {
	bindAttributes();
	getAllUniformVariables();

	// loads initial window size
	ShaderProgram::loadVector2f(windowSizeLocation,
		static_cast<float>(Configs::WIDTH), static_cast<float>(Configs::HEIGHT));
}

TextShader::~TextShader() {
}

void TextShader::getAllUniformVariables() {
	windowSizeLocation = ShaderProgram::getUniformLocation("windowSize");
}

void TextShader::bindAttributes() const {
	bindAttribute(0, POSITION_VAR_NAME);
	bindAttribute(1, TEXTURE_COORDS_VAR_NAME);
}

void TextShader::loadWindowSize(float width, float height) const {
	ShaderProgram::loadVector2f(windowSizeLocation, width, height);
}

