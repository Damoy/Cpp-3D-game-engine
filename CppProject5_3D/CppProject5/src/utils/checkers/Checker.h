#pragma once

#include <iostream>
#include "GL\glew.h"
#include "GLFW\glfw3.h"

/*
	The Checker is a tool used to check and trace errors.
*/
namespace Checker {
	// Checks if a window is alive
	void checkWindowAlive(GLFWwindow* window);
	// Checks the conditions is true, raises the error otherwise
	void assertTrue(bool check, const char* errorToRaise);
	// Checks the conditions is false, raises the error otherwise
	void assertFalse(bool check, const char* errorToRaise);
	// Checks the ptr is not null
	void assertNotNull(void* ptr);
	// Checks the ptr is not null, raises the error otherwise
	void assertNotNull(void* ptr, const char* error);

	// Assuming that T handles operator=
	template<typename T>
	void isEqualToOneOf(T elt, T check1, T check2) {
		if (elt != check1 && elt != check2) {
			Logs::println("ExceptionChecker::isEqualToOneOf error is from: ", true, false);
			Logs::printG(elt);
			Logs::printG(", ");
			Logs::printG(check1);
			Logs::printG(", ");
			Logs::printlnG(check2);
			throw std::invalid_argument("Element is neither equals to second argument nor third one.");
		}
	}

	namespace ShaderChecker {
		// Checks a shader compile state
		void checkShaderCompileState(unsigned int shaderID);
		// Checks a shader link state
		void checkShaderLinkState(unsigned int shaderID);
	}

	namespace Loaders {
		// Checks a texture loading state
		void checkTextureLoadingState(const unsigned char* textureData);
	}
	

}