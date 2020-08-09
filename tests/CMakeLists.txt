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
init_test(TestJsonDeps ./TestJsonDeps.cpp)
add_deps_to_test(TestJsonDeps ${CORE_MODULE_NAME} ${GAME_MODULE_NAME})

#################### Core Module ####################
init_test(TestVector2D ./TestVector2D.cpp ../src/Core/DataTypes/Vector2D.cpp ../src/Core/DataTypes/Vector2D.h)
add_deps_to_test(TestVector2D ${CORE_MODULE_NAME} ${GAME_MODULE_NAME})

#################### Node System ####################
init_test(TestNodeSystem ./TestNodeSystem.cpp)
add_deps_to_test(TestNodeSystem ${CORE_MODULE_NAME} ${GAME_MODULE_NAME})
