--premake5.lua
workspace "Gransim"
	configurations{"Debug", "Release"}


project "GranularSimulation"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin/"
	includedirs {"../include/engine", "../include/rapidjson", "../include/utils"}
	links {"sfml-graphics", "sfml-window" , "sfml-system", "m"}
	buildoptions{"-O3"}
	files {"../src/engine/*.cpp", "../src/utils/*.cpp"}

	-- configuration "Debug"
	-- symbols "On"


	filter "configurations.Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations.Release"
		defines {"NDEBUG"}
		buildoptions{"-O3"}
		optimize "Speed"


	

project "ParticleRenderer"

	kind "ConsoleApp"
	language "C++"
	targetdir "../bin/"
	includedirs {"../include/renderer", "../include/rapidjson", "../include/utils"}
	links {"sfml-graphics", "sfml-window" , "sfml-system"}
	buildoptions{"-O3"}
	files {"../src/renderer/*.cpp", "../src/utils/*.cpp"}


	filter "configurations.Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations.Release"
		defines {"NDEBUG"}
		buildoptions{"-O3"}
		optimize "Speed"

