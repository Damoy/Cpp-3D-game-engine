#pragma once

#include "ShaderProgram.h"

/*
	The gui shader, used for gui rendering
*/
class GUIShader : public ShaderProgram {
private:
	const static char* POSITION_VAR_NAME;
	const static char* TEXTURE_COORDS_VAR_NAME;

	const static char* VERTEX_SHADER_PATH;
	const static char* FRAGMENT_SHADER_PATH;

	// shader paths
	const char* vertexShaderPath;
	const char* fragmentShaderPath;

	// uniforms
	unsigned int transformationMatrixlocation;

public:
	GUIShader();
	~GUIShader();

	void getAllUniformVariables();
	void bindAttributes() const;
	void loadTransformationMatrix(glm::mat4 matrix) const;
};

