workspace "Axel"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
includeDir = {}
includeDir["GLFW"] = "Axel/vendor/GLFW/include"
includeDir["Glad"] = "Axel/vendor/Glad/include"
includeDir["ImGui"] = "Axel/vendor/imgui"
includeDir["glm"] = "Axel/vendor/glm"

group "Dependencies"
    include "Axel/vendor/GLFW"
    include "Axel/vendor/Glad"
    include "Axel/vendor/imgui"
group ""

project "Axel"
    location "Axel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "axpch.h"
    pchsource "Axel/src/axpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{includeDir.GLFW}",
        "%{includeDir.Glad}",
        "%{includeDir.ImGui}",
        "%{includeDir.glm}"
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

        defines
        {
              "AX_PLATFORM_WINDOWS",
              "AX_BUILD_DLL",
              "GLFW_INCLUDE_NONE"
		}

    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AX_DIST"
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
        "Axel/vendor/spdlog/include",
        "Axel/src",
        "Axel/vendor",
        "%{includeDir.glm}"
    }

    links
    {
        "Axel"
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
              "AX_PLATFORM_WINDOWS"
		}


    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AX_DIST"
        runtime "Release"
        optimize "on"
