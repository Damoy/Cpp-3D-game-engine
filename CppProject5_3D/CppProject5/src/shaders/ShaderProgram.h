#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GL\glew.h"
#include "GLM\glm.hpp"
#include "GLM\gtc\type_ptr.hpp"
#include "utils\checkers\Checker.h"

/*
	The abstract root Shader class.
	A shader is program / code that will be computed into
	the GPU instead of the CPU.
	A vertex shader is usually used to compute location-related vertex data
	and a fragment to compute color and lightning.
	Here, the shader contains the vertex and shader file paths and will be responsible
	to compile them to opengl for rendering use.
*/
class ShaderProgram{
private:
	// vertex and fragment shader string tmp content
	const std::string* tmpVertexStr;
	const std::string* tmpFragmentStr;

	// loads a shader file
	const std::string* loadShader(const char* shaderPath) const;

	// compiles a shader
	void compileShader(const char* shaderContent, unsigned int glType);

	// set one of the shaders id
	void setShaderID(unsigned int shaderID, unsigned int glType);
	// link the shaders to the program
	void linkShaders();
	// attach a shader to the program
	void attachShader(unsigned int shaderID) const;
	// validate the program
	void validate() const;

	// detach the shaders from the program
	void detachShaders() const;
	// delete the shaders
	void deleteShaders() const;
	// delete the program and the shaders
	void selfDelete() const;
	// deletes the files content
	void cleanTemporaryMemory();

protected:
	// vertex and fragment shader content
	const char* vertexShaderContent;
	const char* fragmentShaderContent;

	// the program and shaders IDs
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;

	// bind an attribute
	void bindAttribute(unsigned int index, const char* variableName) const;

	// get the uniform location of the given variable
	unsigned int getUniformLocation(const char* str) const;
	unsigned int getUniformLocation(const std::string& str) const;

	// load a float to a location
	void loadFloat(unsigned int location, float value) const;
	// load a vector2 float to a location
	void loadVector2f(unsigned int location, float vx, float vy) const;
	// load a vector3 float to a location
	void loadVector3f(unsigned int location, float vx, float vy, float vz) const;
	void loadVector3f(unsigned int location, glm::vec3 vec3f) const;
	// load a bool to a location
	void loadBool(unsigned int location, bool value) const;

	// load a matrix4 float to a location
	void loadMatrix4f(unsigned int location, glm::mat4 value) const;
	void loadMatrix4f(unsigned int location, const float* value) const;

	// get all the uniform variables locations
	virtual void getAllUniformVariables() = 0;
	// bind the shader attributes
	virtual void bindAttributes() const = 0;

public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	// Starts the shader program.
	void start() const;

	// Stops the shader program.
	void stop() const;

	// Cleans the shader program.
	void cleanUp() const;
};

