#------------------------------------------------------------------------------
#                       Global variables
#------------------------------------------------------------------------------
set(EXECUTABLE_TARGETS_LIST "" CACHE INTERNAL "EXECUTABLE_TARGETS_LIST")

function(RegisterTarget targetName targetCurrentSourceDir isRuntime linkSDL)
    ### Set variable
    list(APPEND EXECUTABLE_TARGETS_LIST ${targetName})
    set(${targetName}_OPTIONS "" CACHE INTERNAL "${targetName}_OPTIONS")
    if (EMSCRIPTEN)
        #TODO Update Debug version
        if (DEBUG)
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:-s LLD_REPORT_UNDEFINED" # For linking debugging
                    )
        endif ()
        list(APPEND ${targetName}_OPTIONS
                -O3 -flto -fno-rtti
                "SHELL:-s WASM=1"
                "SHELL:-s BINARYEN_METHOD=native-wasm"
                "SHELL:-s TOTAL_MEMORY=256MB"
                "SHELL:-s DEMANGLE_SUPPORT=1"
                "SHELL:-s DISABLE_EXCEPTION_CATCHING=1"
                "SHELL:-s USE_PTHREADS=0"
#                "SHELL:-s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\""
                )
        if(${isRuntime} STREQUAL "true")
            set_target_properties( ${targetName} PROPERTIES OUTPUT_NAME "main.js")
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:-s NO_EXIT_RUNTIME=1"
                    )
        endif()
        if(${isRuntime} STREQUAL "false")
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:-s SIDE_MODULE=1"
                    "SHELL:-s EXPORT_ALL=1"
                    )
        endif()
        if(${linkSDL} STREQUAL "true")
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:-s USE_SDL=2"
                    "SHELL:-s USE_SDL_IMAGE=2"
                    "SHELL:-s SDL2_IMAGE_FORMATS=[\"png\"]"
                    "SHELL:-s USE_FREETYPE=1"
#                    "SHELL:-s USE_WEBGL2=1"
                    )
        endif()
    endif (EMSCRIPTEN)

    ### Output location
    set_target_properties( ${targetName}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
            )

#    RegisterResources(${targetName} ${targetCurrentSourceDir})
    target_compile_options(${targetName} PUBLIC ${${targetName}_OPTIONS})

endfunction(RegisterTarget)

function(RegisterResources targetName targetCurrentSourceDir)
    ###TODO Full automaticly!
#    message(FATAL_ERROR ${EXECUTABLE_TARGETS_LIST})
    foreach(item ${${targetName}_OPTIONS})
        message(FATAL_ERROR ${item})
    endforeach()
endfunction(RegisterResources)

