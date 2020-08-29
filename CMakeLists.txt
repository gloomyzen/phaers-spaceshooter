#------------------------------------------------------------------------------
# External dependencies and external project flags:
#------------------------------------------------------------------------------
# ID NAME           FLAG FOR EXTERNAL USE       TARGET NAME FOR EXTERNAL PACKAGE
# 1. ImGui          FLAG_EXTERNAL_IMGUI         imgui_ext_target
# 2. RapidJson      FLAG_EXTERNAL_RAPIDJSON     rapidjson_ext_target
# 3. BuildExamples  FLAG_BUILD_EXAMPLES         @ flag for build examples
# 4. BuildTests     FLAG_BUILD_TESTS            @ flag for build tests
#------------------------------------------------------------------------------
#                       General Projects Settings
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11)
project(TGEngine
        LANGUAGES CXX
        )
add_definitions(-DPROJECT_VERSION="0.1")
include(cmake/StandardProjectSettings.cmake)

#------------------------------------------------------------------------------
#                         Dependencies and variables
#------------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} Debug)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
else ()
    add_definitions(-DRELEASE=1)
endif ()
if (EMSCRIPTEN)
    add_definitions(-DEMSCRIPTEN=1)
endif()
if (APPLE OR MAC)
    add_definitions(-DAPPLE=1)
    set(CMAKE_MACOSX_RPATH 1)
endif()

#------------------------------------------------------------------------------
#                         CMake modules and options
#------------------------------------------------------------------------------

include(ExternalProject)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UpdateResources.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

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

#------------------------------------------------------------------------------
#                              General library
#------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC
        src/Core/moduleDefinitions.h
        #### DEBUG ####
        src/Core/Debug/Logger.cpp src/Core/Debug/Logger.h
        src/Core/Debug/ImGui/SDLImplements/imgui_sdl.cpp src/Core/Debug/ImGui/SDLImplements/imgui_sdl.h
        src/Core/Debug/ImGui/ImGuiManager.cpp src/Core/Debug/ImGui/ImGuiManager.h
        #### APPLICATION ####
        src/Core/Application.cpp src/Core/Application.h
        src/Core/GameApplication.cpp src/Core/GameApplication.h
        src/Core/DataTypes/Vector2D.cpp src/Core/DataTypes/Vector2D.h
        #### Components ####
        src/Core/Components/Component.h
        src/Core/Components/AllComponentsHeaders.h
        src/Core/Components/TransformComponent.h
        src/Core/Components/SpriteComponent.h
#        src/Core/Components/CameraComponent.h
#        src/Core/Components/ColliderComponent.h
#        src/Core/Components/CollisionDetection.h
#        src/Core/Components/KeyboardController.h
#        src/Core/Components/TouchController.h
        #### Nodes ####
        src/Core/Nodes/Node.h src/Core/Nodes/Node.cpp
        src/Core/Nodes/NodeManager.h src/Core/Nodes/NodeManager.cpp
        src/Core/Nodes/NodeFactory.h src/Core/Nodes/NodeFactory.cpp
        #### Resources managers ####
        src/Core/ResourceModule/ResourceManager.cpp src/Core/ResourceModule/ResourceManager.h
        src/Core/ResourceModule/Loaders/TextureManager.cpp src/Core/ResourceModule/Loaders/TextureManager.h
        src/Core/ResourceModule/Loaders/JsonLoader.cpp src/Core/ResourceModule/Loaders/JsonLoader.h

        #### Game Module ####
        src/Game/Interface/InterfaceModule.cpp src/Game/Interface/InterfaceModule.h
        src/Game/StateModule/StateManager.cpp src/Game/StateModule/StateManager.h
        )

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

# Add as many warning as possible:
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which
    # is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(${PROJECT_NAME} PRIVATE <vector> <array> <string> <map> <utility> <memory> <algorithm> <bitset>)
endif ()

#------------------------------------------------------------------------------
#                        ImGui, included for debugging only
#------------------------------------------------------------------------------
if (NOT FLAG_EXTERNAL_IMGUI)
    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp)
        message(FATAL_ERROR "ImGui not found, download lib/imgui or use 'git submodules update'.")
    endif()
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ImGui.cmake)
    if(IMGUI_ENABLED)
        add_definitions(-DIMGUI_ENABLED) # <- new cast definition
        target_link_libraries(${PROJECT_NAME} PRIVATE imgui_target)
    endif()
elseif(FLAG_EXTERNAL_IMGUI)
    # Using external imgui_ext_target
    if(IMGUI_ENABLED)
        add_definitions(-DIMGUI_ENABLED) # <- new cast definition
        target_link_libraries(${PROJECT_NAME} PRIVATE imgui_ext_target)
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
    target_link_libraries(${PROJECT_NAME} PUBLIC rapidjson_target)
elseif(FLAG_EXTERNAL_RAPIDJSON)
    # Using external rapidjson_ext_target
    target_link_libraries(${PROJECT_NAME} PUBLIC rapidjson_target)
endif()

#------------------------------------------------------------------------------
#                                   SDL2
#------------------------------------------------------------------------------

if(EMSCRIPTEN)

    #TODO add debug and release flags
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX "_emscripten.bc")

    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 ")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ASSERTIONS=1 -s LLD_REPORT_UNDEFINED=1")
    endif()

else()

    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2.cmake)

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
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL_LIBRARY})

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
        # TODO need test with Visual Studio
#        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2MAIN_LIBRARY})
#        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
#        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_LIBRARIES})

    endif()

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)

    include_directories(${SDL2_INCLUDE_DIR})
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})


    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()


#------------------------------------------------------------------------------
#                               Example targets
#------------------------------------------------------------------------------
if (NOT FLAG_BUILD_EXAMPLES)
    set(BUILD_EXAMPLES "true")
elseif(FLAG_BUILD_EXAMPLES STREQUAL "1")
    set(BUILD_EXAMPLES "true")
else()
    set(BUILD_EXAMPLES "false")
endif ()
if (BUILD_EXAMPLES STREQUAL "true")
#    add_subdirectory(games)
endif ()
# TODO move to examples file
# Example of simple drawing of objects
add_executable(example_simple_draw src/main.cpp)
target_compile_features(example_simple_draw PRIVATE cxx_std_17)
target_compile_options(example_simple_draw PRIVATE -Wall)
target_link_libraries(example_simple_draw PRIVATE ${PROJECT_NAME})
RegisterTarget(example_simple_draw ${CMAKE_CURRENT_SOURCE_DIR} true true)

#------------------------------------------------------------------------------
#                               Tests section
#------------------------------------------------------------------------------
if (NOT FLAG_BUILD_TESTS)
    if (NOT EMSCRIPTEN)
        set(BUILD_TESTS "true")
    endif ()
elseif(FLAG_BUILD_TESTS STREQUAL "1")
    set(BUILD_TESTS "true")
else()
    if (NOT EMSCRIPTEN)
        set(BUILD_TESTS "true")
    endif ()
endif ()
if (BUILD_TESTS STREQUAL "true")
    enable_testing()
    add_subdirectory(tests)
endif ()