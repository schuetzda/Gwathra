#pragma once

#include <vector>
#include "bvhtree.h"

namespace gwa {
	class ObjMesh {
	public:
		std::vector<float> vertices = std::vector<float>();
		std::vector<float> uvs = std::vector<float>();
		std::vector<float> normals = std::vector<float>();

		std::vector<size_t> vertexIndices = std::vector<size_t>();
		std::vector<size_t> normalIndices = std::vector<size_t>();
		std::vector<size_t> uvIndices = std::vector<size_t>();


		void setIndOffset(int indexOffset) { m_indexOffset = indexOffset; }
		int getIndOffset() { return m_indexOffset; }
	private:

		int m_indexOffset;
	};
}