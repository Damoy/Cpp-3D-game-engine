#pragma once

#include "SampleShader.h"

/*
	The selection shader, used for tile selected rendering
*/
class SelectionShader : public SampleShader {
private:
	const static char* VERTEX_SHADER_PATH;
	const static char* FRAGMENT_SHADER_PATH;

public:
	SelectionShader();
	~SelectionShader();

	void getAllUniformVariables();
	void bindAttributes() const;
};

