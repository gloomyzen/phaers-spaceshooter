include(AddGoogleTest)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    set_property(TARGET ${ARG_TARGET} PROPERTY CXX_STANDARD 17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    add_gtest(${ARG_TARGET})
endfunction()

function(ADD_DEPS_TO_TEST ARG_TARGET)
    target_link_libraries(
            ${ARG_TARGET} PRIVATE ${ARGN})
endfunction()

################### General tests ###################
init_test(TestJsonDeps ./TestJsonDeps.cpp ../src/Core/Loaders/JsonLoader.h ../src/Core/Loaders/JsonLoader.cpp)

#################### Core Module ####################
init_test(TestVector2D ./TestVector2D.cpp ../src/Core/DataTypes/Vector2D.cpp ../src/Core/DataTypes/Vector2D.h)
add_deps_to_test(TestVector2D project_dependency)
#################### Node System ####################
init_test(TestNodeSystem ./TestNodeSystem.cpp
        ../src/Core/Nodes/Node.h
        ../src/Core/Nodes/Node.cpp
        ../src/Core/Nodes/NodeManager.h
        ../src/Core/Nodes/NodeManager.cpp
        ../src/Core/Components/TransformComponent.h
        ../src/Core/DataTypes/Vector2D.cpp
        ../src/Core/DataTypes/Vector2D.h
        ../src/Core/Components/SpriteComponent.h
        ../src/Core/Loaders/TextureManager.cpp
        ../src/Core/Loaders/TextureManager.h
        ../src/Core/moduleDefinitions.h
        ../src/Core/Application.cpp
        ../src/Core/Application.h
        ../src/Core/GameApplication.cpp
        ../src/Core/GameApplication.h
        ../src/Core/Loaders/JsonLoader.h ../src/Core/Loaders/JsonLoader.cpp
        ../src/Core/Nodes/NodeFactory.h ../src/Core/Nodes/NodeFactory.cpp
        )
add_deps_to_test(TestNodeSystem project_dependency)

#init_test(TestLevelLoad ./TestLevelLoad.cpp ../src/Classes/Utilities/LoadManager.cpp ../src/Classes/Utilities/JsonLoadManager.cpp)