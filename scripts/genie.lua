--
-- Copyright 2010-2018 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-sdl",
	description = "Enable SDL entry.",
}

newoption {
	trigger = "with-glfw",
	description = "Enable GLFW entry.",
}

newoption {
	trigger = "with-profiler",
	description = "Enable build with intrusive profiler.",
}

newoption {
	trigger = "with-scintilla",
	description = "Enable building with Scintilla editor.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-examples",
	description = "Enable building examples.",
}

solution "application"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION == "xcode4" then
		platforms {
			"Universal",
		}
	else
		platforms {
			"x32",
			"x64",
--			"Xbox360",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "SandBox"

	
ROOT_DIR   = path.getabsolute("..")


local BUILD_DIR = path.join(ROOT_DIR, ".build")
local THIRD_PARTY_DIR = path.join(ROOT_DIR, "ThirdParty")

dofile (path.join(".", "toolchain.lua"))
if not toolchain(BUILD_DIR, "..") then
	return -- no action specified
end

function copyLib()
end


group "Engine"
project "Hazel"
	kind "SharedLib"

	libdirs{
		path.join(ROOT_DIR, "libs"),
	}
	includedirs {
		path.join(ROOT_DIR, "Hazel"),
		path.join(ROOT_DIR, "../JEngine/ThirdParty/spdlog/include")
	}

	files {
		path.join(ROOT_DIR, "Hazel/**.h"),
		path.join(ROOT_DIR, "Hazel/**.cpp"),
	}
	
	defines{
		"HAZEL_BUILD",
	}

	configuration { "linux-*" }
		--kind "ConsoleApp"
		flags {
			"NoImportLib",
		}

		buildoptions {
			"-fPIC",
		}
		targetextension ".so"
		linkoptions {
			"-shared",
		}
	configuration{"wasm*"}
		--kind "ConsoleApp"
		
		defines{
			"__EMSCRIPTEN__"
		}

		linkoptions{
			"-sUSE_SDL=2"
		}
	configuration { "linux or freebsd" }
		if _OPTIONS["with-wayland"]  then
			links {
				"wayland-egl",
			}
		end
	configuration {}


project "SandBox"
	kind "ConsoleApp"

	includedirs {
		path.join(ROOT_DIR, "Hazel"),
		path.join(ROOT_DIR, "../JEngine/ThirdParty/spdlog/include")
	}

	files {
		path.join(ROOT_DIR, "SandBox/**.h"),
		path.join(ROOT_DIR, "SandBox/**.cpp"),
	}
	
	links{
		"Hazel",
	}

	configuration{"vs* or linux-*"}
		links {
		}
	configuration{"vs*", "x64"}
		libdirs{
			path.join(ROOT_DIR, "lib/win64"),
		}
	
	configuration { "linux-*" }
		flags {
			"NoImportLib",
		}

		buildoptions {
			"-fPIC",
		}
	configuration{"wasm*"}
		kind "ConsoleApp"
		defines{
			"__EMSCRIPTEN__"
		}

		linkoptions{
			"-sUSE_SDL=2",
			"-sALLOW_MEMORY_GROWTH=1",
			"-sMAXIMUM_MEMORY=2gb",
			"--shell-file ../../../ThirdParty/emsdk/upstream/emscripten/src/shell_minimal.html"
		}
	configuration {}

group "test"
project "test_sdl_wasm"
	kind "ConsoleApp"

	includedirs {
		path.join(ROOT_DIR, "ThirdParty/SDL"),
	}

	files {
		path.join(ROOT_DIR, "test/test_sdl_wasm.cpp"),
	}
	libdirs{
		path.join(ROOT_DIR, "lib/win64"),
	}

	links{
	}
	configuration{"vs* or linux-*"}
		links {
		}
	configuration { "Debug" }
		defines {
		}
	
	configuration{"vs*", "x64"}
		libdirs{
			path.join(ROOT_DIR, "lib/win64"),
		}
	
	configuration { "linux-*" }
		flags {
			"NoImportLib",
		}

		buildoptions {
			"-fPIC",
		}
	configuration{"wasm*"}
		kind "ConsoleApp"
		defines{
			"__EMSCRIPTEN__"
		}

		linkoptions{
			"-sUSE_SDL=2",
			"-sALLOW_MEMORY_GROWTH=1",
			"-sMAXIMUM_MEMORY=1gb",
			"--shell-file ../../../ThirdParty/emsdk/upstream/emscripten/src/shell_minimal.html"
		}
	configuration {}
