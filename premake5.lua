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
		"%{prj.name}/vendor/GLFW/include"
	}
	
	links
	{
		"opengl32.lib",
		"glfw3.lib"
	}
	
	libdirs "%{prj.name}/vendor/GLFW/lib-vc2015"
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
		defines "LSD_DEBUG"
		symbols "On"
		staticruntime "Off" -- Needed due to glfw3

	filter "configurations:Release"
		defines "LSD_RELEASE"
		optimize "On"
		--buildoptions "/MD" -- Needed due to glfw3
		staticruntime "Off" -- Needed due to glfw3

	filter "configurations:Distribution"
		defines "LSD_DISTRIBUTION"
		symbols "On"
		staticruntime "Off" -- Needed due to glfw3
