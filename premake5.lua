workspace "Gwathra"
	architecture "x86_64"
	
	configurations
	{
		"Debug",
		"Dev",
		"Ship"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/Gwathra/externals/GLFW/include"
	IncludeDir["glad"] = "%{wks.location}/Gwathra/externals/glad/include"
	
	group "Dependencies"
		include "Gwathra/externals/GLFW"
		include "Gwathra/externals/glad"
	group ""
	
	include "SimpleCube"
	include "Gwathra"
	include "GwaMath"
	include "GwaRay"
