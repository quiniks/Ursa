workspace "Ursa"
	architecture "x64"
	startproject "Ursa-Editor"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (sln directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Ursa/vendor/GLFW/include"
IncludeDir["Glad"] = "Ursa/vendor/Glad/include"
IncludeDir["ImGui"] = "Ursa/vendor/imgui"
IncludeDir["glm"] = "Ursa/vendor/glm"
IncludeDir["stb_image"] = "Ursa/vendor/stb_image"
IncludeDir["entt"] = "Ursa/vendor/entt/include"
IncludeDir["yaml"] = "Ursa/vendor/yaml/include"
IncludeDir["imguizmo"] = "Ursa/vendor/imguizmo"
IncludeDir["spdlog"] = "Ursa/vendor/spdlog/include"
IncludeDir["fontawe"] = "Ursa/vendor/fontawesome"

group "Dependencies"
	include "Ursa/vendor/GLFW"
	include "Ursa/vendor/Glad"
	include "Ursa/vendor/ImGui"
	include "Ursa/vendor/yaml"
group ""

project "Ursa"
	location "Ursa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ursapch.h"
	pchsource "Ursa/src/ursapch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm//**.hpp",
		"%{prj.name}/vendor/glm//**.inl",
		"%{prj.name}/vendor/imguizmo/ImGuizmo.h",
		"%{prj.name}/vendor/imguizmo/ImGuizmo.cpp",
		"%{prj.name}/vendor/fontawesome/FontAwesome5.h"
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml}",
		"%{IncludeDir.imguizmo}",
		"%{IncludeDir.fontawe}"
	}

	links {
		"GLFW",
		"Glad",
		"opengl32.lib",
		"yaml-cpp",
		"ImGui"
	}

	filter "files:Ursa/vendor/imguizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "URSA_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "URSA_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "URSA_DIST"
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

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Ursa/vendor/spdlog/include",
		"Ursa/src",
		"Ursa/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links {
		"Ursa"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines "URSA_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "URSA_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "URSA_DIST"
			runtime "Release"
			optimize "on"

project "Ursa-Editor"
	location "Ursa-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Ursa/vendor/spdlog/include",
		"Ursa/src",
		"Ursa/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links {
		"Ursa"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines "URSA_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "URSA_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "URSA_DIST"
			runtime "Release"
			optimize "on"