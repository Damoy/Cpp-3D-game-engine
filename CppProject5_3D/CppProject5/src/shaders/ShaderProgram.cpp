#include "ShaderProgram.h"
#include "utils\logs\Logs.h"


ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath){
	// get the shader files contents
	tmpVertexStr = loadShader(vertexShaderPath);
	tmpFragmentStr = loadShader(fragmentShaderPath);

	Logs::println();
	vertexShaderContent = tmpVertexStr->c_str();
	fragmentShaderContent = tmpFragmentStr->c_str();

	// compile the vertex shader
	compileShader(vertexShaderContent, GL_VERTEX_SHADER);
	Logs::println("Vertex shader compiled.");

	// compile the fragment shader content
	compileShader(fragmentShaderContent, GL_FRAGMENT_SHADER);
	Logs::println("Fragment shader compiled.");
	// links the shader
	linkShaders();
	Logs::println("Shaders linked.");

	// validate the shader program id
	validate();
	Logs::println("Shader program validated.");

	// detach the shaders
	detachShaders();
	Logs::println("Shaders detached.");
	// delete the shaders
	deleteShaders();
	Logs::println("Shaders deleted.");
	cleanTemporaryMemory();
	Logs::println("Shader program temporary memory cleaned.");
}

ShaderProgram::~ShaderProgram(){
	selfDelete();
}

void ShaderProgram::validate() const {
	glValidateProgram(programID);
}

const std::string* ShaderProgram::loadShader(const char* shaderPath) const {
	std::string shaderContent;
	std::ifstream shaderIFS;

	// ensure shaderIFS can throw exceptions
	shaderIFS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderIFS.open(shaderPath);

		std::stringstream shaderStream;
		shaderStream << shaderIFS.rdbuf();

		shaderIFS.close();

		shaderContent = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error while loading shader." << std::endl;
		throw std::runtime_error("Shader file content is null.");
	}

	Logs::print("Shader ", false);
	Logs::printG(shaderPath);
	Logs::println(" succesfully loaded.", false, true);

	return new std::string(shaderContent);
}

void ShaderProgram::compileShader(const char* shaderContent, unsigned int glType) {
	// checks the gl type
	Checker::isEqualToOneOf<unsigned int>(glType, GL_VERTEX_SHADER, GL_FRAGMENT_SHADER);
	// create the shader
	unsigned int shaderID = glCreateShader(glType);

	// set the corresponding type (vertex or fragment)
	setShaderID(shaderID, glType);

	// associate the shader content to the shaderID
	glShaderSource(shaderID, 1, &shaderContent, NULL);
	// compile it
	glCompileShader(shaderID);

	Checker::ShaderChecker::checkShaderCompileState(shaderID);
}

void ShaderProgram::setShaderID(unsigned int shaderID, unsigned int glType) {
	if (glType == GL_VERTEX_SHADER) {
		vertexShaderID = shaderID;
	} else {
		fragmentShaderID = shaderID;
	}
}

void ShaderProgram::linkShaders() {
	// create the program
	programID = glCreateProgram();

	// attacher the fragment and vertex shaders to it
	attachShader(vertexShaderID);
	attachShader(fragmentShaderID);

	// link the program
	glLinkProgram(programID);
	Checker::ShaderChecker::checkShaderLinkState(programID);
}

void ShaderProgram::attachShader(unsigned int shaderID) const {
	glAttachShader(programID, shaderID);
}

void ShaderProgram::start() const {
	glUseProgram(programID);
}

void ShaderProgram::stop() const {
	glUseProgram(0);
}

void ShaderProgram::cleanUp() const {
	stop();
	detachShaders();
	selfDelete();
}

void ShaderProgram::detachShaders() const {
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
}

void ShaderProgram::deleteShaders() const {
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void ShaderProgram::selfDelete() const {
	glDeleteProgram(programID);
	deleteShaders();
}

void ShaderProgram::cleanTemporaryMemory() {
	delete tmpVertexStr;
	delete tmpFragmentStr;
	tmpVertexStr = nullptr;
	tmpFragmentStr = nullptr;
}

// Below are basically wrapping methods to ease use in sub classes

void ShaderProgram::bindAttribute(unsigned int index, const char* variableName) const {
	glBindAttribLocation(programID, index, variableName);
}

unsigned int ShaderProgram::getUniformLocation(const char* str) const {
	return glGetUniformLocation(programID, str);
}

unsigned int ShaderProgram::getUniformLocation(const std::string& str) const {
	return glGetUniformLocation(programID, str.c_str());
}

void ShaderProgram::loadFloat(unsigned int location, float val) const {
	glUniform1f(location, val);
}

void ShaderProgram::loadVector2f(unsigned int location, float vx, float vy) const {
	glUniform2f(location, vx, vy);
}

void ShaderProgram::loadVector3f(unsigned int location, float vx, float vy, float vz) const {
	glUniform3f(location, vx, vy, vz);

}
void ShaderProgram::loadVector3f(unsigned int location, glm::vec3 vec3f) const {
	glUniform3f(location, vec3f.x, vec3f.y, vec3f.z);
}

void ShaderProgram::loadBool(unsigned int location, bool value) const {
	loadFloat(location, value ? 1.0f : 0.0f);
}

void ShaderProgram::loadMatrix4f(unsigned int location, glm::mat4 value) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::loadMatrix4f(unsigned int location, const float* value) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

