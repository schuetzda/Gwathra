#pragma once

#include <vector>
#include "bvhtree.h"

namespace gwa {
	// TODO Implement submeshes
	class ObjMesh {
	public:
		std::vector<float> vertices = std::vector<float>();
		std::vector<float> uvs = std::vector<float>();
		std::vector<float> normals = std::vector<float>();

		std::vector<uint32_t> vertexIndices = std::vector<uint32_t>();
		std::vector<uint32_t> normalIndices = std::vector<uint32_t>();
		std::vector<uint32_t> uvIndices = std::vector<uint32_t>();
	


		void setIndOffset(int indexOffset) { m_indexOffset = indexOffset; }
		int getIndOffset() { return m_indexOffset; }
	private:

		int m_indexOffset;
	};
}