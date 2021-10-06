project "Gwathra"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.cpp",
	}
	
	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{wks.location}/GwaMath/src",
		"%{IncludeDir.glad}"
	}
	
	links
	{
		"GLFW",
		"glad",
		"opengl32.lib"
		"GwaMath"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines 
		{
			"GWA_PLATFORM_WINDOWS",
			"GWA_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "GWA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Dev"
		defines "GWA_DEV"
		runtime "Release"
		optimize "on"

	filter "configurations:Ship"
		defines "GWA_SHIP"
		runtime "Release"
		optimize "on"
		