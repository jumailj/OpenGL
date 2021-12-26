--premake.lua

workspace "OpenGL"
	architecture "x64"
	configurations{"Debug", "Release"}


	project "OpenGL"
		location "OpenGL" --location of the .vcxprj files to be placed
		kind "ConsoleApp"
		language "C++"

		files{ "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

		includedirs {"%{prj.name}/vendor/GLFW/include", "%{prj.name}/vendor/GLAD/include"} --include glfw, glad
		libdirs{"%{prj.name}/vendor/GLFW/lib"} --include additional lib dependencies
		links {"opengl32.lib", "glfw3.lib"} --inclding


		targetdir ("bin/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}") 
		objdir ("bin-int/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}")

		filter {"configurations:Debug"}
			defines {"DEBUG"}
			symbols "On"

		filter{"configurations:Release"}
			defines{"NDEBUG"}
			optimize "On"

