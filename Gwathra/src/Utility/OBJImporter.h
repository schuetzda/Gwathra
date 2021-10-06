#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
class OBJImporter
{
public:
	static void import_file(const char* PATH) {
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

		FILE* fp = fopen(PATH, "r");

		if (fp == NULL) {
			std::cerr << "OBJImporter Could not read file";
			return;
		}

		char* line = NULL;
		size_t len = 0;

		
		while ((getline(&line, &len, fp)) != -1) {
			// using printf() in all tests for consistency
			printf("%s", line);
		}
	}

};

