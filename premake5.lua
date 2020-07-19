workspace "Lidar_Lane_Separator_Detection"
	architecture "x86"

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
		"%{prj.name}/vendor/spdlog/include"
	}

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

	filter "configurations:Release"
		defines "LSD_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "LSD_DISTRIBUTION"
		symbols "On"

