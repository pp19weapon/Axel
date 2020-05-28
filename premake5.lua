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

group "Dependencies"
    include "Axel/vendor/GLFW"
    include "Axel/vendor/Glad"
    include "Axel/vendor/imgui"
group ""

project "Axel"
    location "Axel"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{includeDir.ImGui}"
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

        defines
        {
              "AX_PLATFORM_WINDOWS",
              "AX_BUILD_DLL",
              "GLFW_INCLUDE_NONE"
		}

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")  
		}


    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AX_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "Axel/src"
    }

    links
    {
        "Axel"
	}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
              "AX_PLATFORM_WINDOWS"
		}


    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AX_DIST"
        runtime "Release"
        optimize "On"