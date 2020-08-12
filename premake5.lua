workspace "RendererFramework"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sandbox/vendor/GLFW/include"
IncludeDir["Glad"] = "Sandbox/vendor/Glad/include"
IncludeDir["spdlog"] = "Sandbox/vendor/spdlog/include"
IncludeDir["assimp"] = "Sandbox/vendor/assimp/include"
IncludeDir["glm"] = "Sandbox/vendor/glm"
IncludeDir["stb"] = "Sandbox/vendor/stb"

LibraryDir = {}
LibraryDir["assimp"] = "Sandbox/vendor/assimp/bin"

group "Dependencies"
	include "Sandbox/vendor/GLFW"
	include "Sandbox/vendor/Glad"

group ""

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Sandbox/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",

		"%{prj.name}/vendor/assimp/**.h",
		"%{prj.name}/vendor/assimp/**.hpp",
		"%{prj.name}/vendor/assimp/**.inl",

		"%{prj.name}/tests/**.h",
		"%{prj.name}/tests/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}

	libdirs
	{
		"%{LibraryDir.assimp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"assimp-vc142-mt.lib"
	}

	filter "configurations:Debug"
		defines "DEBUG_ENABLED"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"