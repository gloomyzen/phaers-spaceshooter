#------------------------------------------------------------------------------
# General Projects Settings
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11)
project(towerdefense-game
        LANGUAGES CXX
        )
include(cmake/StandardProjectSettings.cmake)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
target_compile_options(project_options INTERFACE -Wall)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} Debug)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__DEBUG__")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__RELEASE__")
endif ()

include(ExternalProject)

#------------------------------------------------------------------------------
# General dependencies.
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

add_library(project_dependency INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which
    # is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif ()

#------------------------------------------------------------------------------
# Detect emscripten is used.
#------------------------------------------------------------------------------
if (EMSCRIPTEN)
# TODO move this to cmake/platform/emscripten
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__EMSCRIPTEN__")

    # Enabling debug bar.
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        file(READ ${CMAKE_CURRENT_SOURCE_DIR}/resources/stub/index-debug-section.html debug-bar)
    endif ()

    # Copy the index.html file.
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/stub/index.html
            ${CMAKE_CURRENT_BINARY_DIR}/index.html
    )
    # Copy the style.css file.
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/stub/style.css
            ${CMAKE_CURRENT_BINARY_DIR}/style.css
    )
    # Copy the favicon.
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/stub/favicon.ico
            ${CMAKE_CURRENT_BINARY_DIR}/favicon.ico
    )

    # Allow the resource directories to be fetched by the web browser.
    file(GLOB assets_files
            "${CMAKE_SOURCE_DIR}/resources/sprites/*"
            "${CMAKE_SOURCE_DIR}/resources/font/*.ttf"
            "${CMAKE_SOURCE_DIR}/resources/data/*.json"
            )

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        list(APPEND assets_files "${CMAKE_SOURCE_DIR}/lib/imgui/misc/fonts*.ttf")
    endif ()

    foreach (file ${assets_files})
        file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
        string(APPEND CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
        message(STATUS CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
    endforeach ()

else () # Not Web

    file(COPY "${CMAKE_SOURCE_DIR}/resources/sprites/"
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/sprites)
    file(COPY "${CMAKE_SOURCE_DIR}/resources/data/"
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/data)

    # sdl
    if (APPLE OR MAC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__APPLE__")
        set(CMAKE_MACOSX_RPATH 1)
        if (NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/macOS/SDL2.framework")
            message("Downloading SDL2 frameworks")
            execute_process(
                    COMMAND "chmod +x ${CMAKE_SOURCE_DIR}/lib/macOS/install.sh"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/macOS")
            execute_process(
                    COMMAND "${CMAKE_SOURCE_DIR}/lib/macOS/install.sh"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/macOS")
        endif ()
        set(SDL_INCLUDE_DIR "")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -F ${CMAKE_SOURCE_DIR}/lib/macOS")
        #TODO for future static linking
        #set(CMAKE_EXE_LINKER_FLAGS "-Wl,-F${CMAKE_SOURCE_DIR}/lib/macOS -Wl,-rpath ${CMAKE_SOURCE_DIR}/lib/macOS -framework Cocoa")
        #set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
        set(SDL_LIBRARY
                "-framework SDL2"
                "-framework SDL2_ttf"
                "-framework SDL2_mixer"
                "-framework SDL2_image"
                )
        set(SDL_EXPORT_LIBRARIES
                "${CMAKE_SOURCE_DIR}/lib/macOS/SDL2.framework"
                "${CMAKE_SOURCE_DIR}/lib/macOS/SDL2_ttf.framework"
                "${CMAKE_SOURCE_DIR}/lib/macOS/SDL2_mixer.framework"
                "${CMAKE_SOURCE_DIR}/lib/macOS/SDL2_image.framework"
                )
        mark_as_advanced(SDL_INCLUDE_DIR SDL_LIBRARY)
        target_link_libraries(project_dependency INTERFACE ${SDL_LIBRARY})

        include_directories(${SDL_INCLUDE_DIR})

    endif()
    if(WIN32)

        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/win32/SDL2")
            message("Downloading SDL2 frameworks")
            execute_process(
                    COMMAND "chmod +x ${CMAKE_SOURCE_DIR}/lib/win32/install.sh"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/win32")
            execute_process(
                    COMMAND "${CMAKE_SOURCE_DIR}/lib/win32/install.sh VC"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/win32")
        endif()

        set(SDL2_LIBRARY "${CMAKE_SOURCE_DIR}/lib/win32/SDL/SDL2/lib/x86/SDL2.lib")
        set(SDL2MAIN_LIBRARY "${CMAKE_SOURCE_DIR}/lib/win32/SDL/SDL2/lib/x86/SDL2main.lib")
        set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/win32/SDL/SDL2/include")
        set(SDL2_IMAGE_LIBRARY "${CMAKE_SOURCE_DIR}/lib/win32/SDL/SDL2_image/lib/x86/SDL2_image.lib")
        set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/win32/SDL/SDL2_image/include")
        # for Visual Studio
#        target_link_libraries(project_dependency INTERFACE ${SDL2MAIN_LIBRARY})
#        target_link_libraries(project_dependency INTERFACE ${SDL2_LIBRARIES})
#        target_link_libraries(project_dependency INTERFACE ${SDL2_IMAGE_LIBRARIES})

    endif()

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)

    include_directories(${SDL2_INCLUDE_DIR})
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    

    target_link_libraries(project_dependency INTERFACE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

endif()

# Rapidjson
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson/include
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ImGui.cmake)
if(IMGUI_ENABLED)
    target_link_libraries(imgui_target PUBLIC project_dependency)
    target_link_libraries(project_dependency INTERFACE imgui_target)
endif()

add_subdirectory(src)

#------------------------------------------------------------------------------
# Tests section
#------------------------------------------------------------------------------

if (NOT EMSCRIPTEN)
    enable_testing()
    add_subdirectory(tests)
endif ()