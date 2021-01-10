project "SimpleCube"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/Gwathra/src",
		"%{IncludeDir.glad}"
	}

	links 
	{
		"Gwathra",
		"glad"
	}
		
	filter "system:windows"
		systemversion "latest"
	
		defines 
		{
			"GWA_PLATFORM_WINDOWS"
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