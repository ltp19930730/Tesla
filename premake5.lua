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
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines {
            "TL_PLATFORM_WINDOWS",
            "TL_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TL_RELEASE"
        runtime "Release"
        symbols "On"
        
    filter "configurations:Dist"
        defines "TL_DIST"
        runtime "Release"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "Tesla"
        "ImGui",
    }

    filter "system:windows" 
        cppdialect "C++17"
        systemversion "latest"

        defines {
            "TL_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TL_RELEASE"
        runtime "Release"
        symbols "On"
        
    filter "configurations:Dist"
        defines "TL_DIST"
        runtime "Release"
        symbols "On"