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
IncludeDir["GLFW"] = "Doge/vendor/GLFW/include"
IncludeDir["Glad"] = "Doge/vendor/Glad/include"
IncludeDir["spdlog"] = "Doge/vendor/spdlog/include"
IncludeDir["assimp"] = "Doge/vendor/assimp/include"
IncludeDir["glm"] = "Doge/vendor/glm"
IncludeDir["stb"] = "Doge/vendor/stb"

LibraryDir = {}
LibraryDir["assimp"] = "Doge/vendor/assimp/lib"

group "Dependencies"
	include "Doge/vendor/GLFW"
	include "Doge/vendor/Glad"

group ""

project "Doge"
	location "Doge"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Doge/src/pch.cpp"

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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Doge/src",
		"Doge/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"Doge"
	}

	filter "configurations:Debug"
		defines "DEBUG_ENABLED"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"