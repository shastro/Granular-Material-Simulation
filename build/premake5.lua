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
	files {"../src/engine/*.cpp"}

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

	files {"../src/renderer/*.cpp"}

	configuration "Debug"
	symbols "On"

	filter "configurations.Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations.Release"
		defines {"NDEBUG"}
		optimize "On"

