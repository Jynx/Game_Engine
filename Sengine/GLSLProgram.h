#pragma once
#include <string>
#include <GL/glew.h>
#include "Errors.h"

namespace Sengine {

    class GLSLProgram {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void CompileShaders(const std::string& vertexShaderFilePath,
            const std::string& fragmentShaderFilePath);
        void LinkShaders();
        void AddAttribute(const std::string& attributeName);
        void Bind();
        void UnBind();
        GLint GetUniformVarLocation(const std::string& name);
    private:
        int _numAttributes;
        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

        void CompileShader(const std::string& filePath, GLuint& shaderID);
    };

}