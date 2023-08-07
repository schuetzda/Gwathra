#define TINYOBJLOADER_IMPLEMENTATION
#include "externals/tinyobjloader/tiny_obj_loader.h"

#include "OBJImporter.h"
#include <iostream>
#include <fstream> 
#include "bvhtree.h"

namespace gwa {
	// TODO Memory leak
	bool OBJImporter::import_filetiny(std::string filepath, ObjMesh& mesh, BVHTree& bvhTree)
	{
		tinyobj::ObjReaderConfig reader_config;
		reader_config.mtl_search_path = "./"; // Path to material files


		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str());

		if (!err.empty()) {
			printf("err: %s\n", err.c_str());
			std::cerr << "err: : " << filepath << "/n";
		}

		if (!ret) {
			std::cerr<<"failed to load : " << filepath << "/n";
			return false;
		}

		if (shapes.size() == 0) {
			std::cerr << "err: # of shapes are zero.\n";
			return false;
		}

		mesh.vertices = std::move(attrib.vertices);

		std::vector<BVHNode> nodes;
		for (size_t s = 0; s < shapes.size(); s++) {
			size_t indexOffset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

				const size_t numFaceVertices = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);
				tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset];

				
				
				gwm::Vec3 boundMin = gwm::Vec3(
					mesh.vertices[3*size_t(idx.vertex_index) + 0],
					mesh.vertices[3*size_t(idx.vertex_index) + 1],
					mesh.vertices[3*size_t(idx.vertex_index) + 2]);

				gwm::Vec3 boundMax = boundMin;
				

				mesh.vertexIndices.push_back(static_cast<uint32_t>(idx.vertex_index));

				for (uint32_t v = 1; v < numFaceVertices; ++v) {
					idx = shapes[s].mesh.indices[indexOffset + v];

					if (boundMin.v[0] > mesh.vertices[3 * size_t(idx.vertex_index) + 0]) {
						boundMin.v[0] = mesh.vertices[3 * size_t(idx.vertex_index) + 0];
					}
					if (boundMin.v[1] > mesh.vertices[3 * size_t(idx.vertex_index) + 1]) {
						boundMin.v[1] = mesh.vertices[3 * size_t(idx.vertex_index) + 1];
					}
					if (boundMin.v[2] > mesh.vertices[3 * size_t(idx.vertex_index) + 2]) {
						boundMin.v[2] = mesh.vertices[3 * size_t(idx.vertex_index) + 2];
					}

					if (boundMax.v[0] < mesh.vertices[3 * size_t(idx.vertex_index) + 0]) {
						boundMax.v[0] = mesh.vertices[3 * size_t(idx.vertex_index) + 0];
					}
					if (boundMax.v[1] < mesh.vertices[3 * size_t(idx.vertex_index) + 1]) {
						boundMax.v[1] = mesh.vertices[3 * size_t(idx.vertex_index) + 1];
					}
					if (boundMax.v[2] < mesh.vertices[3 * size_t(idx.vertex_index) + 2]) {
						boundMax.v[2] = mesh.vertices[3 * size_t(idx.vertex_index) + 2];
					}
					mesh.vertexIndices.push_back(static_cast<uint32_t>(idx.vertex_index));
				}

				indexOffset += numFaceVertices;

			}
		}
		bvhTree = BVHTree(mesh.vertices, mesh.vertexIndices);
	}
}