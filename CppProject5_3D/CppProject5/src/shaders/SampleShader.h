#pragma once
#include "ShaderProgram.h"
#include "entities\graphics\Camera.h"
#include "entities\graphics\Light.h"

#include "GLM\glm.hpp"
#include "GLM\gtc\matrix_transform.hpp"

/*
	The main shader !
	Used by most of the code.
	It contains the mesh position, texture, normal and the 
	transformation matrix, projection matrix, view matrix, light position, light color uniforms locations.
*/
class SampleShader : public ShaderProgram {
private:

protected:
	const static char* POSITION_VAR_NAME;
	const static char* COLOR_VAR_NAME;
	const static char* TEXTURE_COORDS_VAR_NAME;
	const static char* NORMALS_VAR_NAME;

	// shader paths
	const char* vertexShaderPath;
	const char* fragmentShaderPath;

	// uniform variables
	unsigned int transformationMatrixLocation;
	unsigned int projectionMatrixLocation;
	unsigned int viewMatrixLocation;

	unsigned int lightPositionLocation;
	unsigned int lightColorLocation;

public:
	SampleShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~SampleShader();

	// Get the uniform variables shader locations
	virtual void getAllUniformVariables();
	// bind used data attributes
	virtual void bindAttributes() const;

	// load the transformation matrix
	void loadTransformationMatrix(glm::mat4 matrix4f) const;
	// load the projection matrix
	void loadProjectionMatrix(const float* matrix4f) const;
	void loadProjectionMatrix(glm::mat4 projectionMatrix) const;
	void loadProjectionMatrix() const;
	// load the view matrix
	void loadViewMatrix(Camera* camera) const;
	// loads the light
	void loadLight(Light* light) const;
};

