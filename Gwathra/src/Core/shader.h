#pragma once
#include <glad\glad.h>
class Shader 
{
public:
	Shader() {}
	void create(const char* vertexShaderPath, const char* fragmentShaderPath);
	void create(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath);

	GLuint getUniformLocation(const char* name);
	void bind();

private:
	GLuint programID = 0;

	void loadProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);
};