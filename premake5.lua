workspace "Lidar_Lane_Separator_Detection"

	platforms { "x86", "x86_64" }

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Project Lidar_Lane_Separator_Detection
project "Lidar_Lane_Separator_Detection"
	location "Lidar_Lane_Separator_Detection"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLEW/include"
	} 
	
	links
	{
		"opengl32.lib",
		"glfw3.lib",
		"glew32s.lib"
	}
	
	libdirs
	{
		"%{prj.name}/vendor/GLFW/lib-vc2015",
		"%{prj.name}/vendor/GLEW/lib/Release/Win32"
	}
	--links "foo"

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{

		}

		postbuildcommands
		{
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/UnitTest"),
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/System")
		}

	filter "configurations:Debug"
		defines
		{
		"LSD_DEBUG",
		"GLEW_STATIC" -- Needed due to glew
		}
		symbols "On"
		staticruntime "Off" -- Needed due to glfw3

	filter "configurations:Release"
		defines
		{
		"LSD_RELEASE",
		"GLEW_STATIC" -- Needed due to glew
		}
		optimize "On"
		--buildoptions "/MD" -- Needed due to glfw3 (TODO: Remove)
		staticruntime "Off" -- Needed due to glfw3

	filter "configurations:Distribution"
		defines
		{
		"LSD_DISTRIBUTION",
		"GLEW_STATIC"  -- Needed due to glew
		}
		symbols "On"
		staticruntime "Off" -- Needed due to glfw3

