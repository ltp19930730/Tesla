project "Tesla"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tlpch.h"
    pchsource "src/tlpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE",
        "YAML_CPP_STATIC_DEFINE",
	}

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib"
    }

    filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

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