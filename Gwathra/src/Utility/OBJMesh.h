#pragma once
#include <vector>
class OBJMesh {
public:
	std::vector<float> vertices = std::vector<float>();
	std::vector<float> uvs = std::vector<float>();
	std::vector<float> normals = std::vector<float>();

	std::vector<unsigned int> vertexIndices = std::vector<unsigned int>();
	std::vector<unsigned int> uvIndices = std::vector<unsigned int>();
	std::vector<unsigned int> normalIndices = std::vector<unsigned int>();
	
private:
	int variables;
};