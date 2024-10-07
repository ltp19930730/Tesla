include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Tesla"
    architecture "x64"
    startproject "Teslanut"

    solution_items
	{
		".editorconfig"
	}

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Tesla/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Tesla/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Tesla/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Tesla/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Tesla/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Tesla/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Tesla/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Tesla/vendor/ImGuizmo"

group "Dependencies"
    include "vendor/premake"
    include "Tesla/vendor/GLFW"
    include "Tesla/vendor/GLAD"
    include "Tesla/vendor/imgui"
    include "Tesla/vendor/yaml-cpp"
group ""

include "Tesla"
include "Sandbox"
include "Teslanut"