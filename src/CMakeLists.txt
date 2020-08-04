#TODO add library core and main target
add_executable(main
        main.cpp
        Core/moduleDefinitions.h
        Core/Application.cpp
        Core/Application.h
        Core/GameApplication.cpp
        Core/GameApplication.h
        Core/Loaders/TextureManager.cpp
        Core/Loaders/TextureManager.h
        Core/DataTypes/Vector2D.cpp
        Core/DataTypes/Vector2D.h
        #### Components ####
        Core/Components/Component.h
        Core/Components/AllComponentsHeaders.h
        Core/Components/TransformComponent.h
        Core/Components/SpriteComponent.h
#        Core/Components/CameraComponent.h
#        Core/Components/ColliderComponent.h
#        Core/Components/CollisionDetection.h
#        Core/Components/ECS.h
#        Core/Components/ECS.cpp
#        Core/Components/KeyboardController.h
#        Core/Components/TouchController.h
        #### Nodes ####
        Core/Nodes/Node.h
        Core/Nodes/NodeManager.h
        Core/Nodes/NodeManager.cpp)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

target_link_libraries(
        main PRIVATE project_options project_dependency project_warnings)

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