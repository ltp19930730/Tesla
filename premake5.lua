workspace "Tesla"
    architecture "x64"
    startproject "Teslanut"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tesla/vendor/GLFW/include"
IncludeDir["Glad"] = "Tesla/vendor/Glad/include"
IncludeDir["ImGui"] = "Tesla/vendor/imgui"
IncludeDir["glm"] = "Tesla/vendor/glm"
IncludeDir["stb_image"] = "Tesla/vendor/stb_image"
IncludeDir["entt"] = "Tesla/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Tesla/vendor/yaml-cpp/include"

group "Dependencies"
    include "Tesla/vendor/GLFW"
    include "Tesla/vendor/GLAD"
    include "Tesla/vendor/imgui"
    include "Tesla/vendor/yaml-cpp"
group ""

project "Tesla"
    location "Tesla"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tlpch.h"
    pchsource "Tesla/src/tlpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE",
        "YAML_CPP_STATIC_DEFINE",
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib"
    }

    filter "system:windows" 
        systemversion "latest"

    filter "configurations:Debug"
        defines "TL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TL_RELEASE"
        runtime "Release"
        optimize  "on"
        
    filter "configurations:Dist"
        defines "TL_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Tesla/vendor/spdlog/include",
        "Tesla/src",
        "Tesla/vendor",
        "%{IncludeDir.glm}",
    }

    links
    {
        "Tesla",
    }

    filter "system:windows" 
        systemversion "latest"

    filter "configurations:Debug"
        defines "TL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TL_RELEASE"
        runtime "Release"
        optimize  "on"
        
    filter "configurations:Dist"
        defines "TL_DIST"
        runtime "Release"
        optimize  "on"

project "Teslanut"
	location "Teslanut"
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
		"Tesla/vendor/spdlog/include",
		"Tesla/src",
		"Tesla/vendor",
	    "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
	}

	links
	{
		"Tesla"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "TL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TL_DIST"
		runtime "Release"
		optimize "on"

