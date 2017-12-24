#pragma once

#include "SampleShader.h"
#include "entities\graphics\Light.h"

/*
	The map shader, used for map rendering
*/
class MapShader : public SampleShader {
private:
	const static char* VERTEX_SHADER_PATH;
	const static char* FRAGMENT_SHADER_PATH;

public:
	MapShader();
	~MapShader();

	void bindAttributes() const;
	void getAllUniformVariables();
};

