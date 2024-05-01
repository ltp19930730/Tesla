workspace "Tesla"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tesla/vendor/GLFW/include"

include "Tesla/vendor/GLFW"

project "Tesla"
    location "Tesla"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tlpch.h"
    pchsource "Tesla/src/tlpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows" 
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

    defines {
        "TL_PLATFORM_WINDOWS",
        "TL_BUILD_DLL"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        symbols "On"

    filter "configurations:Release"
    defines "TL_RELEASE"
    symbols "On"
        
    filter "configurations:Dist"
    defines "TL_DIST"
    symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Tesla/src"
    }

    links
    {
        "Tesla"
    }

    filter "system:windows" 
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

    defines {
        "TL_PLATFORM_WINDOWS",
    }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TL_RELEASE"
        symbols "On"
        
    filter "configurations:Dist"
        defines "TL_DIST"
        symbols "On"