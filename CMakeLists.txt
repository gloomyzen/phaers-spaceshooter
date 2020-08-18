#------------------------------------------------------------------------------
# External dependencies and external project flags:
#------------------------------------------------------------------------------
# ID NAME           FLAG FOR EXTERNAL USE       TARGET NAME FOR EXTERNAL PACKAGE
# 1. ImGui          FLAG_EXTERNAL_IMGUI         imgui_ext_target                TODO <- ready
# 2. RapidJson      FLAG_EXTERNAL_RAPIDJSON     rapidjson_ext_target            TODO <- ready
# 3. SDL2           FLAG_EXTERNAL_SDL2          //                              TODO <- not working
# 4. SDL2_ttf       FLAG_EXTERNAL_SDL2TTF       //                              TODO <- not working
# 5. SDL2_mixer     FLAG_EXTERNAL_SDL2MIXER     //                              TODO <- not working
# 6. SDL2_image     FLAG_EXTERNAL_SDL2IMAGE     //                              TODO <- not working
#------------------------------------------------------------------------------
#                       General Projects Settings
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11)
project(tgengine
        LANGUAGES CXX
        )
include(cmake/StandardProjectSettings.cmake)

#------------------------------------------------------------------------------
#                         Dependencies and variables
#------------------------------------------------------------------------------
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
target_compile_options(project_options INTERFACE -Wall)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} Debug)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRELEASE")
endif ()
if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN")
endif()
if (APPLE OR MAC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPPLE")
    set(CMAKE_MACOSX_RPATH 1)
endif()

include(ExternalProject)

#------------------------------------------------------------------------------
#                           General options.
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_library(project_dependency INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

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
    target_precompile_headers(project_options INTERFACE <vector> <array> <string> <map> <utility> <memory> <algorithm> <bitset>)
endif ()

#------------------------------------------------------------------------------
#                              UpdateResources
#------------------------------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UpdateResources.cmake)

#------------------------------------------------------------------------------
#                                   SDL2
#------------------------------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2.cmake)
#target_link_libraries(project_dependency INTERFACE imgui_target)

if (NOT EMSCRIPTEN)
    # sdl
    if (APPLE)
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

#------------------------------------------------------------------------------
#                        ImGui, included for debugging only
#------------------------------------------------------------------------------
if (NOT FLAG_EXTERNAL_IMGUI)
    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp)
        message(FATAL_ERROR "ImGui not found, download lib/imgui or use 'git submodules update'.")
    endif()
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ImGui.cmake)
    if(IMGUI_ENABLED)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED")
        target_link_libraries(project_dependency INTERFACE imgui_target)
    endif()
elseif(FLAG_EXTERNAL_IMGUI)
    # Using external imgui_ext_target
    if(IMGUI_ENABLED)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED")
        target_link_libraries(project_dependency INTERFACE imgui_ext_target)
    endif()
endif()

#------------------------------------------------------------------------------
#                               Rapidjson
#------------------------------------------------------------------------------
if (NOT FLAG_EXTERNAL_RAPIDJSON)
    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson/include)
        message(FATAL_ERROR "Rapidjson not found, download lib/rapidjson or use 'git submodules update'.")
    endif()
    add_library(rapidjson_target INTERFACE)
    target_include_directories(rapidjson_target INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson/include>
            )
    target_link_libraries(project_dependency INTERFACE rapidjson_target)
elseif(FLAG_EXTERNAL_RAPIDJSON)
    # Using external rapidjson_ext_target
    target_link_libraries(project_dependency INTERFACE rapidjson_target)
endif()

#------------------------------------------------------------------------------
#                           Include src with modules
#------------------------------------------------------------------------------
add_subdirectory(src)

#------------------------------------------------------------------------------
#                          Compiler warnings target
# Set enabled maximum compilation warnings for project_warnings target
#------------------------------------------------------------------------------
include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)
target_link_libraries(project_warnings INTERFACE ${CORE_MODULE_NAME} ${GAME_MODULE_NAME})

#------------------------------------------------------------------------------
#                               Export target
# Exported target tgengine included all modules from tgengine/src
#------------------------------------------------------------------------------
add_library(${PROJECT_NAME} SHARED
        $<TARGET_OBJECTS:${CORE_MODULE_NAME}>
        $<TARGET_OBJECTS:${GAME_MODULE_NAME}>
        )
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )
target_link_libraries(${PROJECT_NAME} PUBLIC ${CORE_MODULE_NAME} ${GAME_MODULE_NAME} project_options project_dependency)

#------------------------------------------------------------------------------
#                               Example targets
#------------------------------------------------------------------------------
# Example of simple drawing of objects
add_executable(example_simple_draw src/main.cpp)
target_compile_features(example_simple_draw PRIVATE cxx_std_17)
target_compile_options(example_simple_draw PRIVATE -Wall)
target_link_libraries(example_simple_draw PRIVATE ${PROJECT_NAME})
update_project_resources(example_simple_draw ${CMAKE_CURRENT_SOURCE_DIR})
update_project_target(example_simple_draw)

#------------------------------------------------------------------------------
#                               Tests section
#------------------------------------------------------------------------------

if (NOT EMSCRIPTEN)
    enable_testing()
    add_subdirectory(tests)
endif ()