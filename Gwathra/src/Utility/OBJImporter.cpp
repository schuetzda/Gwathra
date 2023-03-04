#define TINYOBJLOADER_IMPLEMENTATION
#include "externals/tinyobjloader/tiny_obj_loader.h"

#include "OBJImporter.h"
#include <iostream>
#include <fstream> 


void vertex_cb(void* user_data, float x, float y, float z, float w)
{
	OBJMesh* mesh = reinterpret_cast<OBJMesh*>(user_data);
	printf("v[%ld] = %f, %f, %f (w %f)\n", mesh->vertices.size() / 3, x, y, z, w);

	mesh->vertices.push_back(x);
	mesh->vertices.push_back(y);
	mesh->vertices.push_back(z); std::cout << x << y << z;
}

void normal_cb(void* user_data, float x, float y, float z)
{
	std::cout << x << y << z;
}

void texcoord_cb(void* user_data, float x, float y, float z)
{
	std::cout << x << y << z;
}

void index_cb(void* user_data, tinyobj::index_t* indices, int num_indices)
{
	std::cout << num_indices;
}
void group_cb(void* user_data, const char** names, int num_names) {
	// MyMesh *mesh = reinterpret_cast<MyMesh*>(user_data);
	printf("group : name = \n");

	for (int i = 0; i < num_names; i++) {
		printf("  %s\n", names[i]);
	}
}
void object_cb(void* user_data, const char* name)
{
	printf("object : name = %s\n", name);
}

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
	OBJMesh mesh1;
	bool ret = tinyobj::LoadObjWithCallback(ifs, cb, &mesh1, nullptr, &warn, &err);

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
}
