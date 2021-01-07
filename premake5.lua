workspace "Gwathra"
	architecture "x86_64"
	startproject "SimpleCube"
	
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
		
	include "Gwathra"
	include "GwaMath"
	include "SimpleCube"