local GLFW_DIR   = path.getabsolute("../../JEngine/ThirdParty/glfw-3.3.8/")
           
project "GLFW"
    kind "StaticLib"
    language "C"

    includedirs { 
        path.join(GLFW_DIR, "include"),
        path.join(GLFW_DIR, "src"),

    }
    files {
        path.join(GLFW_DIR, "src/glfw_config.h"),
        path.join(GLFW_DIR, "src/internal.h"),
        path.join(GLFW_DIR, "src/mappings.h"),
        path.join(GLFW_DIR, "src/context.c"),
        path.join(GLFW_DIR, "src/init.c"),
        path.join(GLFW_DIR, "src/input.c"),
        path.join(GLFW_DIR, "src/monitor.c"),
        path.join(GLFW_DIR, "src/vulkan.c"),
        path.join(GLFW_DIR, "src/window.c"),
    }

    configuration{"vs*"}
        defines {
            "VC_EXTRALEAN",
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
            "WIN32",
            "__WIN32__",
            -- "_GLFW_USE_CONFIG_H",
            -- "_GLFW_VULKAN_STATIC",
            "UNICODE",
            "_UNICODE",
        }
        files {
            path.join(GLFW_DIR, "src/win32_platform.h"),
            path.join(GLFW_DIR, "src/win32_joystick.h"),
            path.join(GLFW_DIR, "src/wgl_context.h"),
            path.join(GLFW_DIR, "src/egl_context.h"),
            path.join(GLFW_DIR, "src/ osmesa_context.h"),
            path.join(GLFW_DIR, "src/win32_init.c"),
            path.join(GLFW_DIR, "src/win32_joystick.c"),
            path.join(GLFW_DIR, "src/win32_monitor.c"), 
            path.join(GLFW_DIR, "src/win32_time.c"), 
            path.join(GLFW_DIR, "src/win32_thread.c"), 
            path.join(GLFW_DIR, "src/win32_window.c"),
            path.join(GLFW_DIR, "src/wgl_context.c"), 
            path.join(GLFW_DIR, "src/egl_context.c"), 
            path.join(GLFW_DIR, "src/osmesa_context.c"),
        }
        
        links { "user32", "gdi32", "winmm", "imm32", "ole32", "oleaut32", "version", "uuid", "CfgMgr32"}

    configuration{"linux-*"}
        files {
            path.join(GLFW_DIR, "src/core/windows/**"),
        }

    configuration{"macosx"}
        includedirs { path.join(GLFW_DIR, "src/video/khronos") }
        -- xcodebuildsettings {
        --     ["ALWAYS_SEARCH_USER_PATHS"] = "YES",
        -- }
        files {
            path.join(GLFW_DIR, "src/audio/coreaudio/**"),
            
        }
        defines {
        }
        buildoptions {"-fPIC"}

    configuration{"android*"}
        files {
            path.join(GLFW_DIR, "src/audio/android/**"),
            
        }

    configuration{"ios"}
        files
        {
            path.join(GLFW_DIR, "src/joystick/iphoneos/**"),
        }
    configuration{}
