# Конфигурайия для подключения ImGui
# На выжоде будет таргет imgui_target и флаг IMGUI_ENABLED для подклчюения зависимости
#TODO remove after testing
return()
if (NOT IMGUI_ENABLED AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(IMGUI_ENABLED 1)

    #Using OpenGL+GlfW
    set(IMGUI_LIB_SRCS "")
    if (EMSCRIPTEN)
        if (DONT_USE_FILE_SYSTEM) # Default value is 0. Set to 1 to enable file-system and include the misc/fonts/ folder as part of the build.
            string(APPEND CMAKE_CXX_FLAGS " -s NO_FILESYSTEM=1 -DIMGUI_DISABLE_FILE_FUNCTIONS")
        elseif(NOT DONT_USE_FILE_SYSTEM)
            string(APPEND CMAKE_CXX_FLAGS " --no-heap-copy")
            message(STATUS CMAKE_CXX_FLAGS " --no-heap-copy")
        endif ()
        string(APPEND CMAKE_CXX_FLAGS " -s ASSERTIONS=1")
        string(APPEND CMAKE_CXX_FLAGS " -s EXPORT_ALL=1")

        string(APPEND CMAKE_CXX_FLAGS " -Wall -Wformat  -I${CMAKE_SOURCE_DIR}/lib/imgui/ -DIMGUI_IMPL_OPENGL_LOADER_GLEW")
    else()
        list(APPEND IMGUI_LIB_SRCS
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_demo.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/examples/imgui_impl_glfw.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/examples/imgui_impl_opengl3.cpp
        )
        string(APPEND CMAKE_CXX_FLAGS " -Wall -Wformat -I${CMAKE_SOURCE_DIR}/lib/imgui/examples/ -I${CMAKE_SOURCE_DIR}/lib/imgui/ -DIMGUI_IMPL_OPENGL_LOADER_GLEW")
    endif()

    add_library(imgui_target SHARED ${IMGUI_LIB_SRCS})

else()
    return()
endif()