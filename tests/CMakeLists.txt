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

#################### Core Module ####################
init_test(TestVector2D ./TestVector2D.cpp ../src/Core/DataTypes/Vector2D.cpp ../src/Core/DataTypes/Vector2D.h)
add_deps_to_test(TestVector2D project_dependency)

#init_test(TestLevelLoad ./TestLevelLoad.cpp ../src/Classes/Utilities/LoadManager.cpp ../src/Classes/Utilities/JsonLoadManager.cpp)