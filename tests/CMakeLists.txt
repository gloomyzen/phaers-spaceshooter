include(AddGoogleTest)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    target_compile_features(${ARG_TARGET} PRIVATE cxx_std_17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    add_gtest(${ARG_TARGET})
endfunction()

function(ADD_DEPS_TO_TEST ARG_TARGET)
    target_link_libraries(
            ${ARG_TARGET} PRIVATE ${ARGN} project_dependency)
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
update_project_resources(TestNodeSystem "${CMAKE_CURRENT_SOURCE_DIR}/..")
