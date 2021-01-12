#pragma once
#include <glad\glad.h>
class VertexArray
{
public:
	VertexArray() {};
	void create(const unsigned int numVertices);
	void bind();
	void release();
	void setArrayBuffer(GLuint id, GLenum type, const unsigned int dim, const unsigned int rowDim, const void* data, const GLsizeiptr sizeOfDataPoint, GLvoid* pointer = (void*)0, GLenum usage = GL_STATIC_DRAW);
	void setElementBuffer(GLuint id, const unsigned int numElements, const void* indices, const GLsizeiptr sizeOfData, GLenum usage);
private:
	GLuint vboID = 0, vaoID = 0,eboID = 0;
	unsigned int numVertices = 0;
};

