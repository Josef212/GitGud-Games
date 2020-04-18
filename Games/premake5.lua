outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FlappyClone"
	location "FlappyClone"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"Common/src/**.h",
		"Common/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/GitGud/vendor/spdlog/include",
		"%{wks.location}/GitGud/src",
		"%{wks.location}/GitGud/vendor",
		"%{wks.location}/GitGud/vendor/glm",
		"Common/src"
	}

	links
	{
		"GitGud"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			--"GG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GG_DIST"
		runtime "Release"
		optimize "on"

-- -------------------------------------------------------------------------------------
-- -------------------------------------------------------------------------------------
-- -------------------------------------------------------------------------------------

project "R-Type"
	location "R-Type"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"Common/src/**.h",
		"Common/src/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/GitGud/vendor/spdlog/include",
		"%{wks.location}/GitGud/src",
		"%{wks.location}/GitGud/vendor",
		"%{wks.location}/GitGud/vendor/glm"
		"Common/src"
	}
	
	links
	{
		"GitGud"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			--"GG_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "GG_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "GG_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "GG_DIST"
		runtime "Release"
		optimize "on"