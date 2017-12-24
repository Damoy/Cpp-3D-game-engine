#pragma once

#include "shaders\SampleShader.h"

/*
	The main component renderer abstraction.
	(All renderers except the MainRenderer)
*/
class Renderer{
protected:
	// the shader program associated
	ShaderProgram* shader;

public:
	Renderer(ShaderProgram* shader);
	~Renderer();

	// A Renderer should have rendering work to do
	virtual void render() const = 0;
};

