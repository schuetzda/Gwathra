#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>
#include "OBJMesh.h"


namespace gwa {

	class OBJImporter
	{
	public:

		static bool import_filetiny(std::string filepath, ObjMesh* mesh);

	private:
		
	};

}

