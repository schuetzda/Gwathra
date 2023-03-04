#pragma once



#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>
#include "OBJMesh.h"


/*
Inspired by http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/
class OBJImporter
{
public:

	static void import_filetiny(std::string filepath, OBJMesh* mesh);
	static void import_file(const char* PATH, OBJMesh* mesh) {

		FILE* file;
		fopen_s(&file,PATH, "r");

		if (file == NULL) {
			std::cerr << "OBJImporter Could not read file";
			return;
		}

		char lineHeader[128] = { 0 };
		size_t len = 0;
		int matches = 0;

		int res = fscanf_s(file, "%s", lineHeader, static_cast<unsigned int>(sizeof(lineHeader)));
		while (res >= 1) {
			
			if (strcmp(lineHeader, "v") == 0) {
				const int vertexDims = 3;
				float currVertex[vertexDims];
				assert(fscanf_s(file, "%f %f %f\n", &currVertex[0], &currVertex[1], &currVertex[2]) == 3);
				mesh->vertices.insert(mesh->vertices.end(), currVertex, currVertex + vertexDims);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				float currUV[2];
				assert(fscanf_s(file, "%f %f\n", &currUV[0], &currUV[1]) == 2);
				mesh->uvs.insert(mesh->uvs.end(), currUV, currUV + 2);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				const int normalDims = 3;
				float currNormal[normalDims];
				assert(fscanf_s(file, "%f %f %f\n", &currNormal[0], &currNormal[1], &currNormal[2]) == 3);
				mesh->normals.insert(mesh->normals.end(), currNormal, currNormal + normalDims);
			}

			else if (strcmp(lineHeader, "f") == 0) {
				int vertexIndex[4], uvIndex[3], normalIndex[3];
				matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches == 9) {
					mesh->uvIndices.push_back(uvIndex[0]);
					mesh->uvIndices.push_back(uvIndex[1]);
					mesh->uvIndices.push_back(uvIndex[2]);
					mesh->normalIndices.push_back(normalIndex[0]);
					mesh->normalIndices.push_back(normalIndex[1]);
					mesh->normalIndices.push_back(normalIndex[2]);
				}
				else {
					//plus one match from the previous fscan
					matches = fscanf_s(file, "%d%d%d", &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]) + 1;

					if (matches < 3 || matches > 4) {
						std::cerr << "File can't be read by our simple parser : ( Try exporting with other options\n";
						return;
					}

					for (int i = 0; i < matches; ++i) {
						if (vertexIndex[i] < 0)
							// Static cast is not fixing the problem of downcasting. 
							// However vertices size should never overflow int anyway.
							vertexIndex[i] = static_cast<int>(mesh->vertices.size())/ 3 + vertexIndex[i];
					}
				}
			

				mesh->vertexIndices.push_back(vertexIndex[0]);
				mesh->vertexIndices.push_back(vertexIndex[1]);
				mesh->vertexIndices.push_back(vertexIndex[2]);
				if (matches == 4)
					mesh->vertexIndices.push_back(vertexIndex[3]);
				
			}

			res = fscanf_s(file, "%s", lineHeader, static_cast<unsigned int> (sizeof(lineHeader)));
		}
		mesh->setIndOffset(matches);
		fclose(file);
	}

private:
};

