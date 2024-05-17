workspace "Tesla"
    architecture "x64"
    startproject "Sandbox"

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

group "Dependencies"
    include "Tesla/vendor/GLFW"
    include "Tesla/vendor/GLAD"
    include "Tesla/vendor/imgui"
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
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows" 
        systemversion "latest"

        defines {
            "TL_PLATFORM_WINDOWS",
            "TL_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

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

        defines {
            "TL_PLATFORM_WINDOWS",
        }

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