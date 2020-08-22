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
#                "SHELL:-s ERROR_ON_UNDEFINED_SYMBOLS=0"
                "SHELL:-s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\""
                )
        if(${isRuntime} STREQUAL "true")
#            set_target_properties( ${targetName} PROPERTIES OUTPUT_NAME "main")
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:-s NO_EXIT_RUNTIME=1"
                    "SHELL:-s EXPORT_NAME='main' -s MODULARIZE=1"
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
                    "SHELL:-s USE_WEBGL2=1"
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
    target_compile_options(${targetName} PRIVATE ${${targetName}_OPTIONS})

endfunction(RegisterTarget)

function(RegisterResources targetName targetCurrentSourceDir)
    if (EMSCRIPTEN)
        # Enabling analytics.
        if (RELEASE)
            file(READ ${CMAKE_BINARY_DIR}/resources/_stub/index-analytics-section.html analytics)
        endif ()
        # Set directory path
        set(targetDir "/${targetName}/") # <- this variable will be read in "configure_file"
        # Copy the project index.html file.
        configure_file(
                ${targetCurrentSourceDir}/resources/_stub/blank_index.html
                ${CMAKE_BINARY_DIR}/${targetName}/index.html
        )

    endif (EMSCRIPTEN)

    file(GLOB assets_files)
    if(EXISTS ${targetCurrentSourceDir}/resources/${targetName}/sprites)
        file(COPY "${targetCurrentSourceDir}/resources/${targetName}/sprites/"
                DESTINATION ${CMAKE_BINARY_DIR}/${targetName}/sprites)
        list(APPEND assets_files "${CMAKE_BINARY_DIR}/${targetName}/sprites")
    endif()

    if(EXISTS ${targetCurrentSourceDir}/resources/${targetName}/data)
        file(COPY "${targetCurrentSourceDir}/resources/${targetName}/data/"
                DESTINATION ${CMAKE_BINARY_DIR}/${targetName}/data)
        list(APPEND assets_files "${CMAKE_BINARY_DIR}/${targetName}/data")
    endif()

    if(EXISTS ${targetCurrentSourceDir}/resources/${targetName}/fonts)
        file(COPY "${targetCurrentSourceDir}/resources/${targetName}/fonts/"
                DESTINATION ${CMAKE_BINARY_DIR}/${targetName}/fonts)
        list(APPEND assets_files "${CMAKE_BINARY_DIR}/${targetName}/fonts")
    endif()

    if (DEBUG AND EMSCRIPTEN AND EXISTS ${CMAKE_SOURCE_DIR}/lib/imgui/misc)
        list(APPEND assets_files "${CMAKE_SOURCE_DIR}/lib/imgui/misc/fonts/*.ttf")
    endif ()

    if (EMSCRIPTEN)
        list(APPEND ${targetName}_OPTIONS
                --closure 1
                --use-preload-plugins
                )
        foreach (file ${assets_files})
            file(RELATIVE_PATH relative_file "${CMAKE_BINARY_DIR}/${targetName}/" ${file})
            list(APPEND ${targetName}_OPTIONS
                    "SHELL:--preload-file ${file}@/${relative_file}"
                    )
            message(STATUS "Load files for target ${targetName}:" " --preload-file ${file}@/${relative_file}")
        endforeach ()
    endif (EMSCRIPTEN)

endfunction(RegisterResources)

function(RegisterMainPage)
if (EMSCRIPTEN)
    #TODO generate main page
endif (EMSCRIPTEN)
endfunction(RegisterMainPage)
