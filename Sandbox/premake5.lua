project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
		"src/**.h",
		"src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Tesla/vendor/spdlog/include",
		"%{wks.location}/Tesla/src",
		"%{wks.location}/Tesla/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
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
