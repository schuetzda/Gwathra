#pragma once
#include <glad\glad.h>
class Shader 
{
public:
	Shader() {}
	void create(const char* vertexShaderPath, const char* fragmentShaderPath);
	void create(const char* computeShaderPath);
	void create(const char* vertexShaderPath,  const char* fragmentShaderPath, const char* geometryShaderPath);
	void create(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath, const char* computeShaderPath);

	GLuint getUniformLocation(const char* name);
	void bind();

private:
	GLuint programID = 0;

	void loadProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0, GLuint computeShader = 0);
};