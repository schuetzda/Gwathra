#include "vertexArray.h"

void VertexArray::create(const unsigned int numVertices) {
	this->numVertices = numVertices;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
}

void VertexArray::bind() {
	glBindVertexArray(vaoID);
}

void VertexArray::release() {
	glBindVertexArray(0);
}

void VertexArray::setArrayBuffer(GLuint id, GLenum type, const unsigned int dim, const unsigned int rowDim, const void* data, const GLsizeiptr sizeOfDataPoint, GLvoid* pointer, GLenum usage) {
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeOfDataPoint * numVertices * rowDim,
		data, usage);
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, dim, type, GL_FALSE, rowDim *sizeOfDataPoint, pointer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void VertexArray::setElementBuffer(GLuint id, const unsigned int numElements, const void* indices, const GLsizeiptr sizeOfData, GLenum usage) {
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glEnableVertexAttribArray(id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfData* numElements, indices, usage);
	
}