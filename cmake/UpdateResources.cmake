#------------------------------------------------------------------------------
#                       Global variables
#------------------------------------------------------------------------------
set(EXECUTABLE_TARGETS_LIST "" CACHE INTERNAL "EXECUTABLE_TARGETS_LIST")

function(RegisterTarget targetName targetCurrentSourceDir isRuntime)
    ### Set variable
    list(APPEND EXECUTABLE_TARGETS_LIST ${targetName})
    set(${targetName}_OPTIONS "")
#    set(${targetName}_RESOURCE "" CACHE INTERNAL "${targetName}_RESOURCE")
    if (EMSCRIPTEN)

        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            string(APPEND ${targetName}_OPTIONS
                    " -s LLD_REPORT_UNDEFINED" # For linking debugging
                    )
        endif ()
        # TODO change 'USE_WEBGL2=1' to legacy webgl emulator
        string(APPEND ${targetName}_OPTIONS
#                " -s ALLOW_MEMORY_GROWTH=1"
#                " -s TOTAL_MEMORY=67108864"
#                " -s DEMANGLE_SUPPORT=1"
                " -s DISABLE_EXCEPTION_CATCHING=2"
                " -s EXPORT_NAME='main'"
#                " -s MODULARIZE=1"

                " -s USE_SDL=2"
                " -s USE_SDL_IMAGE=2"
                " -s SDL2_IMAGE_FORMATS=[\"png\"]"
                " -s USE_FREETYPE=1"
                " -s USE_WEBGL2=1"
#                " -s WEBGL2_BACKWARDS_COMPATIBILITY_EMULATION=1"
#                " -s OFFSCREENCANVAS_SUPPORT=1"
                " -s WASM=1"
                )

        if(${isRuntime} STREQUAL "true")
            set_target_properties( ${targetName} PROPERTIES OUTPUT_NAME "main")
            string(APPEND ${targetName}_OPTIONS
                    " -s NO_EXIT_RUNTIME=1"
                    " -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\""
                    )
        endif()

        ### Output location
        set_target_properties( ${targetName}
                PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                )

        RegisterResources(${targetName} ${targetCurrentSourceDir})

#        set_target_properties(${targetName} PROPERTIES LINK_FLAGS "${${targetName}_OPTIONS} ") #TODO  <- old version
        set_property(TARGET ${targetName} APPEND PROPERTY LINK_FLAGS "${${targetName}_OPTIONS} ${${targetName}_RESOURCES} ")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_FREETYPE=1 -s USE_WEBGL2=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\" ")

        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ASSERTIONS=1 -s LLD_REPORT_UNDEFINED=1")
        endif()

    endif (EMSCRIPTEN)

    if (NOT EMSCRIPTEN)
        ### Output location
        set_target_properties( ${targetName}
                PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${targetName}"
                )

        RegisterResources(${targetName} ${targetCurrentSourceDir})
    endif ()

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
        set(${targetName}_DATA "" PARENT_SCOPE)
        string(APPEND ${targetName}_DATA
                " --closure 1"
                " --use-preload-plugins"
                )
        foreach (file ${assets_files})
            file(RELATIVE_PATH relative_file "${CMAKE_BINARY_DIR}/${targetName}/" ${file})
            string(APPEND ${targetName}_DATA
                    " --preload-file ${file}@/${relative_file}"
                    )
            message(STATUS "Load files for target ${targetName}:" " --preload-file ${file}@/${relative_file}")
        endforeach ()
        set(${targetName}_RESOURCES ${${targetName}_DATA} PARENT_SCOPE)

    endif (EMSCRIPTEN)

endfunction(RegisterResources)

function(RegisterMainPage)
if (EMSCRIPTEN)
    #TODO generate main page
endif (EMSCRIPTEN)
endfunction(RegisterMainPage)
