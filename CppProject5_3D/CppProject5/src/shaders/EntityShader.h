#pragma once

#include "SampleShader.h"
#include "entities\graphics\Camera.h"
#include "entities\graphics\Light.h"

/*
	The Entity Shader is a SampleShader.
*/
class EntityShader : public SampleShader {
private:
	const static char* VERTEX_SHADER_PATH;
	const static char* FRAGMENT_SHADER_PATH;

public:
	EntityShader();
	~EntityShader();

	void bindAttributes() const;
	void getAllUniformVariables();
};

