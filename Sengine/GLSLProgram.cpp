#include "GLSLProgram.h"
#include <fstream>
#include <vector>
#include <string>
#include "Errors.h"

namespace Sengine {
	GLSLProgram::GLSLProgram()
		: _numAttributes(0),
		_programID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0) {}

	GLSLProgram::~GLSLProgram() {}

	void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath,
		const std::string& fragmentShaderFilePath) {

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (!_vertexShaderID) {
			FatalError("Vertex Shader failed to load");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (!_fragmentShaderID) {
			FatalError("Fragment Shader failed to load");
		}

		CompileShader(vertexShaderFilePath, _vertexShaderID);
		CompileShader(fragmentShaderFilePath, _fragmentShaderID);
	}

	void GLSLProgram::CompileShader(const std::string& filePath, GLuint& shaderID) {
		std::ifstream shaderFile(filePath);
		if (shaderFile.fail()) {
			perror(filePath.c_str());
			FatalError("shader file" + filePath + "could not be opened");
		}

		std::string fileContents = "";
		std::string line;
		while (std::getline(shaderFile, line)) {
			fileContents += line + "\n";
		}
		shaderFile.close();

		const char* fileContentsPtr = fileContents.c_str();
		// shader ID, # of elements in string, ptr to array of c ptrs,
		// ptr to length of each string, so nullptr works?
		glShaderSource(shaderID, 1, &fileContentsPtr, nullptr);
		glCompileShader(shaderID);

		GLint result = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shaderID);  // Don't leak the shader.

			std::printf("%s\n", &(errorLog[0]));
			FatalError("Shader: " + filePath + "Failed during compilation");
			return;
		}
	}

	void GLSLProgram::LinkShaders() {

		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			// Use the infoLog as you see fit.

			std::printf("%s\n", &(infoLog[0]));
			FatalError("Shaders failed to link ");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::AddAttribute(const std::string& attributeName) {
		// based on shader file indicies. Each vec3 or vec is an index.
		glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
		_numAttributes++;
	}

	void GLSLProgram::Bind() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::UnBind() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	GLint GLSLProgram::GetUniformVarLocation(const std::string& name) {
		//call to OpenGL to get uniform location
		//1: program ID, 2: name return: an ID.
		GLint loc = glGetUniformLocation(_programID, name.c_str());
		if (loc == GL_INVALID_INDEX) {
			FatalError("Get Uniform Location failed with name: " + name);
		}
		return loc;
	}
}