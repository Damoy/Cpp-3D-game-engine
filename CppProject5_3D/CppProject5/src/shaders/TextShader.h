#pragma once

#include "ShaderProgram.h"

/*
	The text shader, unused.
*/
class TextShader : public ShaderProgram {
private:
	const static char* VERTEX_SHADER_PATH;
	const static char* FRAGMENT_SHADER_PATH;
	const static char* POSITION_VAR_NAME;
	const static char* TEXTURE_COORDS_VAR_NAME;

	// uniform variables used in the shader code
	unsigned int windowSizeLocation;

public:
	TextShader();
	~TextShader();

	virtual void getAllUniformVariables();
	virtual void bindAttributes() const;
	void loadWindowSize(float width, float height) const;
};

