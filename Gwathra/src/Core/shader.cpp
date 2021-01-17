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

void Shader::create(const char* computeShaderPath) {
	GLuint computeShader = loadShader(computeShaderPath, GL_COMPUTE_SHADER, "Compute Shader");
	loadProgram(0,0,0, computeShader);
}

void Shader::create(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) {
	GLuint vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER, "VertexShader");
	GLuint fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER, "FragmentShader");
	GLuint geometryShader = loadShader(geometryShaderPath, GL_GEOMETRY_SHADER, "GeometryShader");
	loadProgram(vertexShader, fragmentShader, geometryShader);
}

void Shader::create(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = "\0", const char* computeShaderPath="\0") {
	GLuint vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER, "VertexShader");
	GLuint fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER, "FragmentShader");

	GLuint geometryShader = 0, computerShader = 0;
	if (geometryShaderPath == "\0") {
		geometryShader = loadShader(geometryShaderPath, GL_GEOMETRY_SHADER, "GeometryShader");
	}

	if (computeShaderPath == "\0") {
		computerShader = loadShader(computeShaderPath, GL_COMPUTE_SHADER, "ComputeShader");
	}
	loadProgram(vertexShader, fragmentShader, geometryShader);
}

void Shader::loadProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader, GLuint computeShader) {
	this->programID = glCreateProgram();
	if (vertexShader) {
		glAttachShader(programID, vertexShader);
	}
	if (fragmentShader) {
		glAttachShader(programID, fragmentShader);
	}
	if (geometryShader) {
		glAttachShader(programID, geometryShader);
	}
	if (computeShader) {
		glAttachShader(programID, computeShader);
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
	glDeleteShader(computeShader);
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