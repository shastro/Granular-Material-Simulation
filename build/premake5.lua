--premake5.lua
workspace "Gransim"
	configurations{"Debug", "Release"}


project "GranularSimulation"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin/"
	includedirs {"../include/"}
	links {"sfml-graphics", "sfml-window" , "sfml-system" , "m"}

	files {"../src/*.cpp"}

	filter "configurations.Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations.Release"
		defines {"NDEBUG"}
		optimize "On"