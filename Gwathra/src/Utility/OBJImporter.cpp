#define TINYOBJLOADER_IMPLEMENTATION
#include "externals/tinyobjloader/tiny_obj_loader.h"

#include "OBJImporter.h"
#include <iostream>
#include <fstream> 
#include "bvhtree.h"

namespace gwa {
	void vertex_cb(void* user_data, float x, float y, float z, float w)
	{
		ObjMesh* mesh = reinterpret_cast<ObjMesh*>(user_data);
		std::cout << "Vertex: " << x << " " << y << " " << z << " " << std::endl;
		mesh->vertices.push_back(x);
		mesh->vertices.push_back(y);
		mesh->vertices.push_back(z);
	}

	void normal_cb(void* user_data, float x, float y, float z)
	{
		ObjMesh* mesh = reinterpret_cast<ObjMesh*>(user_data);
		std::cout << "Normal: " << x << " " << y << " " << z << " " << std::endl;

		mesh->normals.push_back(x);
		mesh->normals.push_back(y);
		mesh->normals.push_back(z);
	}

	void texcoord_cb(void* user_data, float x, float y, float z)
	{
		std::cout << "UV: " << x << " " << y << " " << z << " " << std::endl;

		ObjMesh* mesh = reinterpret_cast<ObjMesh*>(user_data);
		mesh->uvs.push_back(x);
		mesh->uvs.push_back(y);
		mesh->uvs.push_back(z); std::cout << x << y << z;
	}

	void index_cb(void* user_data, tinyobj::index_t* indices, int num_indices)
	{
		ObjMesh* mesh = reinterpret_cast<ObjMesh*>(user_data);

		for (int i = 0; i < num_indices; i++) {
			tinyobj::index_t idx = indices[i];
			const size_t offset = num_indices + mesh->vertexIndices.size() / 4 * 4;

			if (idx.vertex_index != 0) {
				mesh->vertexIndices.push_back(idx.vertex_index + offset);
				std::cout << " " << idx.vertex_index + offset;

			}
			if (idx.normal_index != 0) {
				mesh->normalIndices.push_back(idx.normal_index);
			}
			if (idx.texcoord_index != 0) {
				mesh->uvIndices.push_back(idx.texcoord_index);
			}
		}
	}
	void group_cb(void* user_data, const char** names, int num_names) {
		// MyMesh *mesh = reinterpret_cast<MyMesh*>(user_data);


		for (int i = 0; i < num_names; i++) {
			std::cout << "Group: " << names[i] << std::endl;
		}
	}
	void object_cb(void* user_data, const char* name)
	{
		std::cout << "Object: " << name << std::endl;
	}


	// TODO Memory leak
	bool OBJImporter::import_filetiny(std::string filepath, ObjMesh* mesh)
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
		mesh->vertices;

		mesh->vertices = std::move(attrib.vertices);
		for (size_t s = 0; s < shapes.size(); s++) {
			size_t indexOffset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

				const size_t numFaceVertices = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);
				tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset];
				
				gwm::Vec3 boundMin = gwm::Vec3(
					mesh->vertices[3*size_t(idx.vertex_index) + 0],
					mesh->vertices[3*size_t(idx.vertex_index) + 1],
					mesh->vertices[3*size_t(idx.vertex_index) + 2]);

				gwm::Vec3 boundMax = boundMin;

				for (uint32_t v = 1; v < numFaceVertices; ++v) {
					idx = shapes[s].mesh.indices[indexOffset + v];

					if (boundMin.v[0] > mesh->vertices[3 * size_t(idx.vertex_index) + 0]) {
						boundMin.v[0] = mesh->vertices[3 * size_t(idx.vertex_index) + 0];
					}
					if (boundMin.v[1] > mesh->vertices[3 * size_t(idx.vertex_index) + 1]) {
						boundMin.v[1] = mesh->vertices[3 * size_t(idx.vertex_index) + 1];
					}
					if (boundMin.v[2] > mesh->vertices[3 * size_t(idx.vertex_index) + 2]) {
						boundMin.v[2] = mesh->vertices[3 * size_t(idx.vertex_index) + 2];
					}

					if (boundMax.v[0] < mesh->vertices[3 * size_t(idx.vertex_index) + 0]) {
						boundMax.v[0] = mesh->vertices[3 * size_t(idx.vertex_index) + 0];
					}
					if (boundMax.v[1] < mesh->vertices[3 * size_t(idx.vertex_index) + 1]) {
						boundMax.v[1] = mesh->vertices[3 * size_t(idx.vertex_index) + 1];
					}
					if (boundMax.v[2] < mesh->vertices[3 * size_t(idx.vertex_index) + 2]) {
						boundMax.v[2] = mesh->vertices[3 * size_t(idx.vertex_index) + 2];
					}
					
					
				}
				indexOffset += numFaceVertices;
			}
		}
	}
}
/*
void OBJImporter::import_filetiny(std::string filepath, OBJMesh* mesh)
{
	tinyobj::callback_t cb;
	cb.vertex_cb = vertex_cb;
	cb.normal_cb = normal_cb;
	cb.texcoord_cb = texcoord_cb;
	cb.index_cb = index_cb;
	cb.group_cb = group_cb;
	cb.object_cb = object_cb;

	std::string warn;
	std::string err;

	std::ifstream ifs(filepath.c_str(), std::ifstream::in);

	if (ifs.fail()) {
		std::cerr << "file not found." << std::endl;
		return;
	}

	bool ret = tinyobj::LoadObjWithCallback(ifs, cb, mesh, nullptr, &warn, &err);
	if (!warn.empty()) {
		std::cout << "WARN: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		std::cerr << "Failed to parse .obj" << std::endl;
		return;
	}
}*/
