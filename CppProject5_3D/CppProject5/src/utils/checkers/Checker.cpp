#include <iostream>
#include "Checker.h"
#include "utils\logs\Logs.h"

namespace Checker {
	void checkWindowAlive(GLFWwindow* window) {
		assertFalse(window == nullptr, "The window does not exist !");
	}

	void assertTrue(bool check, const char* error) {
		if (!check) {
			Logs::println(error);
			throw std::invalid_argument(error);
		}
	}

	void assertFalse(bool check, const char* error) {
		assertTrue(!check, error);
	}

	void assertNotNull(void* ptr) {
		if (ptr == nullptr) {
			Logs::println("Pointer given is null !");
			throw std::runtime_error("Pointer given is null !");
		}
	}

	void assertNotNull(void* ptr, const char* error) {
		if (ptr == nullptr) {
			Logs::println(error);
			throw std::runtime_error(error);
		}
	}

	namespace ShaderChecker {
		void checkShaderCompileState(unsigned int shaderID) {
			const unsigned int logSize = 512;
			int state;
			char log[logSize];

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &state);

			if (state == GL_FALSE) {
				// get shader error info
				// has been really helpful through the development
				glGetShaderInfoLog(shaderID, logSize, NULL, log);

				Logs::print("Shader compilation failed, shader ID: ", true, false);
				Logs::printG(shaderID);
				Logs::println(true);
				Logs::println(log);

				throw std::runtime_error("Shader compilation unsatisfying state.");
			}
		}

		void checkShaderLinkState(unsigned int shaderID) {
			const unsigned int logSize = 512;
			int state;
			char log[logSize];

			glGetProgramiv(shaderID, GL_LINK_STATUS, &state);

			if (state == GL_FALSE) {
				glGetProgramInfoLog(shaderID, logSize, NULL, log);

				Logs::println("Shader linking failed : ", true, false);
				Logs::println(log, false, true);

				throw std::runtime_error("Shader linking unsatisfying state.");
			}
		}
	}

	namespace Loaders {
		void checkTextureLoadingState(const unsigned char* textureData) {
			if (textureData == GL_FALSE) {
				Logs::println("Failed to load texture.");
				throw std::runtime_error("Loaded texture is null.");
			}
		}
	}
}


