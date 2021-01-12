#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

GLuint loadShader(const char* shaderPath, const GLuint shaderType, const char* shaderName);

void Shader::create(const char* vertexShaderPath, const char* fragmentShaderPath) {
	GLuint vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER, "VertexShader");
	GLuint fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER, "FragmentShader");

	loadProgram(vertexShader, fragmentShader);

}

void Shader::create(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath) {
	GLuint vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER, "VertexShader");
	GLuint fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER, "FragmentShader");
	GLuint geometryShader = loadShader(geometryShaderPath, GL_GEOMETRY_SHADER, "GeometryShader");
	loadProgram(vertexShader, fragmentShader, geometryShader);
}

void Shader::loadProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) {
	this->programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	if (geometryShader > 0) {
		glAttachShader(programID, geometryShader);
	}
	glLinkProgram(programID);

	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

	if (!linkStatus) {
		//Get the length of the error log
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

		std::cerr << "----------" << std::endl << "Error compiling Program: " << &infoLog[0] << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

void Shader::bind() {
	glUseProgram(programID);
}

GLuint Shader::getUniformLocation(const char* name) {
	return glGetUniformLocation(programID, name);
}


GLuint loadShader(const char* shaderPath, const GLuint shaderType, const char* shaderName) {
	std::ifstream shaderFileIn(shaderPath, std::ios::in | std::ios::binary);
	std::string shaderString;

	if (shaderFileIn)
	{
		shaderFileIn.seekg(0, std::ios::end);
		size_t size = shaderFileIn.tellg();
		if (size != -1)
		{
			shaderString.resize(size);
			shaderFileIn.seekg(0, std::ios::beg);
			shaderFileIn.read(&shaderString[0], size);
		}
		else
		{
			std::cerr<<"Could not read from file";
		}
	}
	else
	{
		std::cerr << "Could not open file";
	}
	
	const char* shaderCode = shaderString.c_str();
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, 0);
	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		//Get the length of the error log
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

		std::cerr << "----------" << std::endl << "Error compiling " << shaderName << ": " << &infoLog[0] << std::endl;
	}
	
	return shaderID;
}