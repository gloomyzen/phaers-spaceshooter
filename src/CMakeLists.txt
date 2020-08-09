#------------------------------------------------------------------------------
#                       All modules and submodules
#------------------------------------------------------------------------------
set(CORE_MODULE_NAME CoreModule CACHE INTERNAL "")
set(GAME_MODULE_NAME GameModule CACHE INTERNAL "")

#------------------------------------------------------------------------------
#                          All modules sources
#------------------------------------------------------------------------------
add_library(${CORE_MODULE_NAME} STATIC
        Core/moduleDefinitions.h
        #### DEBUG ####
        Core/Debug/Logger.cpp
        Core/Debug/Logger.h
        #### APPLICATION ####
        Core/Application.cpp Core/Application.h
        Core/GameApplication.cpp Core/GameApplication.h
        Core/DataTypes/Vector2D.cpp Core/DataTypes/Vector2D.h
        #### Components ####
        Core/Components/Component.h
        Core/Components/AllComponentsHeaders.h
        Core/Components/TransformComponent.h
        Core/Components/SpriteComponent.h
#        Core/Components/CameraComponent.h
#        Core/Components/ColliderComponent.h
#        Core/Components/CollisionDetection.h
#        Core/Components/KeyboardController.h
#        Core/Components/TouchController.h
        #### Nodes ####
        Core/Nodes/Node.h Core/Nodes/Node.cpp
        Core/Nodes/NodeManager.h Core/Nodes/NodeManager.cpp
        Core/Nodes/NodeFactory.h Core/Nodes/NodeFactory.cpp
        #### Resources managers ####
        Core/ResourceModule/ResourceManager.cpp Core/ResourceModule/ResourceManager.h
        Core/ResourceModule/Loaders/TextureManager.cpp Core/ResourceModule/Loaders/TextureManager.h
        Core/ResourceModule/Loaders/JsonLoader.cpp Core/ResourceModule/Loaders/JsonLoader.h
        )


add_library(${GAME_MODULE_NAME} STATIC
        #### Game Module ####
        Game/Interface/InterfaceModule.cpp Game/Interface/InterfaceModule.h
        Game/StateModule/StateManager.cpp Game/StateModule/StateManager.h)

#------------------------------------------------------------------------------
#                           Target interfaces
#------------------------------------------------------------------------------

target_include_directories(${CORE_MODULE_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>

        )
target_include_directories(${GAME_MODULE_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        )

#------------------------------------------------------------------------------
#                           Modules output dirs
#------------------------------------------------------------------------------
set_target_properties(${CORE_MODULE_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${GAME_MODULE_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#------------------------------------------------------------------------------
#                            Modules dependency
#------------------------------------------------------------------------------
target_link_libraries(${CORE_MODULE_NAME} PRIVATE ${GAME_MODULE_NAME} project_options project_dependency project_warnings)
target_link_libraries(${GAME_MODULE_NAME} PRIVATE ${CORE_MODULE_NAME} project_options project_dependency project_warnings)

#TODO move this in toolchain
if (EMSCRIPTEN)
    set_target_properties(main PROPERTIES OUTPUT_NAME "main.js")

    string(APPEND CMAKE_CXX_FLAGS " -s DEMANGLE_SUPPORT=1")
    string(APPEND CMAKE_CXX_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
    string(APPEND CMAKE_CXX_FLAGS " -s USE_SDL=2")
    string(APPEND CMAKE_CXX_FLAGS " -s USE_SDL_IMAGE=2")
    string(APPEND CMAKE_CXX_FLAGS " -s SDL2_IMAGE_FORMATS=[\"png\"]")
    string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")
    string(APPEND CMAKE_CXX_FLAGS " -s NO_EXIT_RUNTIME=1")

#    string(APPEND CMAKE_CXX_FLAGS " -s EXPORTED_FUNCTIONS=\"['_main', '_window_resize']\"")
    string(APPEND CMAKE_CXX_FLAGS " -s LLD_REPORT_UNDEFINED") # For linking debugging
    string(APPEND CMAKE_CXX_FLAGS " -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\"")

    #TODO add Release and Debug mode with some flags
#    string(APPEND CMAKE_CXX_FLAGS " --closure 1")
#    string(APPEND CMAKE_CXX_FLAGS " --js-opts 3")
#    string(APPEND CMAKE_CXX_FLAGS " --llvm-lto 3")
#    string(APPEND CMAKE_CXX_FLAGS " --llvm-opts 3")
#    string(APPEND CMAKE_CXX_FLAGS " -O3")

endif()