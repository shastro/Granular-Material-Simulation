--premake5.lua
workspace "Gransim"
	configurations{"Debug", "Release"}


project "GranularSimulation"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin/"
	includedirs {"../include/generator", "../include/rapidjson", "../include/utils"}
	links {"sfml-graphics", "sfml-window" , "sfml-system", "m"}

	files {"../src/engine/*.cpp"}

	configuration "Debug"
	symbols "On"

	filter "configurations.Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations.Release"
		defines {"NDEBUG"}
		optimize "On"


	

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

