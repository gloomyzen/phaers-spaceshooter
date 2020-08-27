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
# 7. BuildExamples  FLAG_BUILD_EXAMPLES         //                              TODO <- not working
# 7. BuildTests     FLAG_BUILD_TESTS            //                              TODO <- not working
#------------------------------------------------------------------------------
#                       General Projects Settings
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11)
project(TGEngine
        LANGUAGES CXX
        )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROJECT_VERSION='0.1'")
add_definitions(-DPROJECT_VERSION='0.1') # <- new cast definition
include(cmake/StandardProjectSettings.cmake)

#------------------------------------------------------------------------------
#                         Dependencies and variables
#------------------------------------------------------------------------------
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
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED") #TODO remove after testing
        add_definitions(-DIMGUI_ENABLED) # <- new cast definition
        target_link_libraries(${PROJECT_NAME} PRIVATE imgui_target)
    endif()
elseif(FLAG_EXTERNAL_IMGUI)
    # Using external imgui_ext_target
    if(IMGUI_ENABLED)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED") #TODO remove after testing
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
    target_link_libraries(${PROJECT_NAME} PRIVATE rapidjson_target)
elseif(FLAG_EXTERNAL_RAPIDJSON)
    # Using external rapidjson_ext_target
    target_link_libraries(${PROJECT_NAME} PRIVATE rapidjson_target)
endif()

#------------------------------------------------------------------------------
#                                   SDL2
#------------------------------------------------------------------------------

if(EMSCRIPTEN)
    if (DEBUG)
        target_link_libraries(${PROJECT_NAME} PUBLIC "-s LLD_REPORT_UNDEFINED") # For linking debugging
    endif ()
    target_link_libraries(${PROJECT_NAME} PUBLIC "-O3 -flto -fno-rtti")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s WASM=1")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s BINARYEN_METHOD=native-wasm")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s TOTAL_MEMORY=256MB")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s DEMANGLE_SUPPORT=1")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s DISABLE_EXCEPTION_CATCHING=1")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_PTHREADS=0")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_SDL=2")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_SDL_IMAGE=2")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s SDL2_IMAGE_FORMATS=[\"png\", \"jpg\"]")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_FREETYPE=1")
    #TODO change to legacy webgl emulator
    target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_WEBGL2=1")

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
        # for Visual Studio
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


return()






include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2.cmake)

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

#    find_package(SDL2 REQUIRED)
#    find_package(SDL2_image REQUIRED)
#
#    include_directories(${SDL2_INCLUDE_DIR})
#    include_directories(${SDL2_IMAGE_INCLUDE_DIR})
#
#
#    target_link_libraries(project_dependency INTERFACE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

endif()

#TODO Need test for desktop version
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#
#include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${SDL2_IMAGE_INCLUDE_DIR})


#target_link_libraries(project_dependency INTERFACE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

#------------------------------------------------------------------------------
#                        ImGui, included for debugging only
#------------------------------------------------------------------------------
#if (NOT FLAG_EXTERNAL_IMGUI)
#    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp)
#        message(FATAL_ERROR "ImGui not found, download lib/imgui or use 'git submodules update'.")
#    endif()
#    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ImGui.cmake)
#    if(IMGUI_ENABLED)
##        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED")
#        add_definitions(-DIMGUI_ENABLED) # <- new cast definition
#        target_link_libraries(project_dependency INTERFACE imgui_target)
#    endif()
#elseif(FLAG_EXTERNAL_IMGUI)
#    # Using external imgui_ext_target
#    if(IMGUI_ENABLED)
##        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_ENABLED")
#        add_definitions(-DIMGUI_ENABLED) # <- new cast definition
#        target_link_libraries(project_dependency INTERFACE imgui_ext_target)
#    endif()
#endif()

#------------------------------------------------------------------------------
#                               Rapidjson
#------------------------------------------------------------------------------
#if (NOT FLAG_EXTERNAL_RAPIDJSON)
#    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson/include)
#        message(FATAL_ERROR "Rapidjson not found, download lib/rapidjson or use 'git submodules update'.")
#    endif()
#    add_library(rapidjson_target INTERFACE)
#    target_include_directories(rapidjson_target INTERFACE
#            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson/include>
#            )
#    target_link_libraries(project_dependency INTERFACE rapidjson_target)
#elseif(FLAG_EXTERNAL_RAPIDJSON)
#    # Using external rapidjson_ext_target
#    target_link_libraries(project_dependency INTERFACE rapidjson_target)
#endif()

#------------------------------------------------------------------------------
#                           Include src with modules
#------------------------------------------------------------------------------
add_subdirectory(src)
set(MODULES_SOURCES_LIST "")
if (NOT IS_DESKTOP)
    foreach(item ${CORE_MODULE_SOURCES_FILE} ${GAME_MODULE_SOURCES_FILE})
        list(APPEND MODULES_SOURCES_LIST "${CMAKE_SOURCE_DIR}/src/${item}")
    endforeach()
endif()

#------------------------------------------------------------------------------
#                          Compiler warnings target
# Set enabled maximum compilation warnings for project_warnings target
#------------------------------------------------------------------------------
#if (IS_DESKTOP)
#    include(cmake/CompilerWarnings.cmake)
#    add_library(project_warnings INTERFACE)
#    set_project_warnings(project_warnings)
#    target_link_libraries(project_warnings INTERFACE ${CORE_MODULE_NAME} ${GAME_MODULE_NAME})
#endif (IS_DESKTOP)

#------------------------------------------------------------------------------
#                               Export target
# Exported target tgengine included all modules from tgengine/src
#------------------------------------------------------------------------------
if (IS_DESKTOP)
add_library(${PROJECT_NAME} STATIC
        $<TARGET_OBJECTS:${CORE_MODULE_NAME}>
        $<TARGET_OBJECTS:${GAME_MODULE_NAME}>
        )
else()
    add_library(${PROJECT_NAME} INTERFACE)
endif()
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )
if (IS_DESKTOP)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_MODULE_NAME} ${GAME_MODULE_NAME} project_options project_dependency)
else()
    target_link_libraries(${PROJECT_NAME} INTERFACE project_options project_dependency)
endif()

#------------------------------------------------------------------------------
#                               Example targets
#------------------------------------------------------------------------------
# Example of simple drawing of objects
add_executable(example_simple_draw src/main.cpp ${MODULES_SOURCES_LIST})
#if(NOT IS_DESKTOP)
#    target_sources(example_simple_draw PRIVATE ${CORE_MODULE_SOURCES_FILE} ${GAME_MODULE_SOURCES_FILE})
#endif(NOT IS_DESKTOP)
target_compile_features(example_simple_draw PRIVATE cxx_std_17)
target_compile_options(example_simple_draw PRIVATE -Wall)
target_link_libraries(example_simple_draw PRIVATE ${PROJECT_NAME})
RegisterTarget(example_simple_draw ${CMAKE_CURRENT_SOURCE_DIR} true true)

#------------------------------------------------------------------------------
#                               Tests section
#------------------------------------------------------------------------------

if (NOT EMSCRIPTEN)
    enable_testing()
    add_subdirectory(tests)
endif ()