#TODO add library core and main target
add_executable(main
        Core/moduleDefinitions.h
        Core/Application.cpp
        Core/Application.h
        Core/GameApplication.cpp
        Core/GameApplication.h
        Core/GlError.cpp
        Core/GlError.h
        Core/Debug/ImGuiLoader.cpp
        Core/Debug/ImGuiLoader.h
        main.cpp
        Core/IApplication.h Core/Game.cpp Core/Game.h Core/Shader.cpp Core/Shader.h Core/Texture2D.cpp Core/Texture2D.h)

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
    string(APPEND CMAKE_CXX_FLAGS " -s SDL2_IMAGE_FORMATS=[\"png\"]") #TODO change go jpg
    string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")
    string(APPEND CMAKE_CXX_FLAGS " -s NO_EXIT_RUNTIME=1")

    #TODO remove unused window_resize form project
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