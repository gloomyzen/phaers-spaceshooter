if (EMSCRIPTEN)
    if (RELEASE)
        file(READ ${CMAKE_BINARY_DIR}/resources/_stub/index-analytics-section.html analytics)
    endif ()
    # Copy the general index.html file.
    configure_file(
            ${target_current_source_dir}/resources/_stub/index.html
            ${CMAKE_BINARY_DIR}/index.html
    )
    # Copy the style.css file.
    configure_file(
            ${target_current_source_dir}/resources/_stub/style.css
            ${CMAKE_BINARY_DIR}/style.css
    )
    # Copy the favicon.
    configure_file(
            ${target_current_source_dir}/resources/_stub/favicon.ico
            ${CMAKE_BINARY_DIR}/favicon.ico
    )
endif()

function(update_project_resources target_name target_current_source_dir)
    set_target_properties( ${target_name}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_name}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_name}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target_name}"
#            COMPILE_DEFINITIONS "RESOURCES_PATH='${target_name}'"
##            COMPILE_OPTIONS "-DRESOURCES_PATH=${CMAKE_BINARY_DIR}/${target_name}"
            )
#    target_compile_definitions(${target_name} PUBLIC
#            RESOURCES_PATH="${CMAKE_BINARY_DIR}/${target_name}")
#    target_compile_options(${target_name} PRIVATE ${BUILD_FLAGS})
    if (EMSCRIPTEN)
        # Enabling analytics.
        if (RELEASE)
            file(READ ${CMAKE_BINARY_DIR}/resources/_stub/index-analytics-section.html analytics)
        endif ()
        # Configure target.js file.
        file(RELATIVE_PATH "${CMAKE_BINARY_DIR}/${target_name}/${target_name}.js" jspath)
        # Copy the project index.html file.
        configure_file(
                ${target_current_source_dir}/resources/_stub/blank_index.html
                ${CMAKE_BINARY_DIR}/${target_name}/index.html
        )

        # Allow the resource directories to be fetched by the web browser.
        file(GLOB assets_files
                "${target_current_source_dir}/resources/${target_name}/sprites/*"
                "${target_current_source_dir}/resources/${target_name}/fonts/*.ttf"
                "${target_current_source_dir}/resources/${target_name}/data/*.json"
                )

        if (DEBUG AND EXISTS ${CMAKE_SOURCE_DIR}/lib/imgui/misc)
            list(APPEND assets_files "${CMAKE_SOURCE_DIR}/lib/imgui/misc/fonts/*.ttf")
        endif ()

        foreach (file ${assets_files})
            file(RELATIVE_PATH relative_file "${target_current_source_dir}/resources/" ${file})
            string(APPEND CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
            message(STATUS CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
        endforeach ()

    endif()# EMSCRIPTEN

    if (NOT EMSCRIPTEN)
        if(EXISTS ${target_current_source_dir}/resources/${target_name}/sprites)
        file(COPY "${target_current_source_dir}/resources/${target_name}/sprites/"
                DESTINATION ${CMAKE_BINARY_DIR}/${target_name}/sprites)
        endif()

        if(EXISTS ${target_current_source_dir}/resources/${target_name}/data)

        file(COPY "${target_current_source_dir}/resources/${target_name}/data/"
                DESTINATION ${CMAKE_BINARY_DIR}/${target_name}/data)
        endif()

        if(EXISTS ${target_current_source_dir}/resources/${target_name}/fonts)
            file(COPY "${target_current_source_dir}/resources/${target_name}/fonts/"
                    DESTINATION ${CMAKE_BINARY_DIR}/${target_name}/fonts)
        endif()

    endif()# NOT EMSCRIPTEN

endfunction()

function(update_project_target target_name)
    if (EMSCRIPTEN)
        set(CURRENT_TARGET_OPTION "")
        set_target_properties( ${target_name} PROPERTIES OUTPUT_NAME "${target_name}.js")

        list(APPEND CURRENT_TARGET_OPTION " -s DEMANGLE_SUPPORT=1")
        list(APPEND CURRENT_TARGET_OPTION " -s DISABLE_EXCEPTION_CATCHING=2")
        list(APPEND CURRENT_TARGET_OPTION " -s USE_SDL=2")
        list(APPEND CURRENT_TARGET_OPTION " -s USE_SDL_IMAGE=2")
        list(APPEND CURRENT_TARGET_OPTION " -s SDL2_IMAGE_FORMATS=[\"png\"]")
        list(APPEND CURRENT_TARGET_OPTION " -s WASM=1")
        list(APPEND CURRENT_TARGET_OPTION " -Wall")
        list(APPEND CURRENT_TARGET_OPTION " -s NO_EXIT_RUNTIME=1")

        #    list(APPEND CURRENT_TARGET_OPTION " -s EXPORTED_FUNCTIONS=\"['_main', '_window_resize']\"")
        list(APPEND CURRENT_TARGET_OPTION " -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\"")

        if (DEBUG)
            list(APPEND CURRENT_TARGET_OPTION " -s LLD_REPORT_UNDEFINED") # For linking debugging
        endif ()

        if (RELEASE)
            list(APPEND CURRENT_TARGET_OPTION " --closure 1")
            list(APPEND CURRENT_TARGET_OPTION " --js-opts 3")
            list(APPEND CURRENT_TARGET_OPTION " --llvm-lto 3")
            list(APPEND CURRENT_TARGET_OPTION " --llvm-opts 3")
            list(APPEND CURRENT_TARGET_OPTION " -O3")
        endif ()

        set_target_properties( ${target_name} PROPERTIES COMPILE_FLAGS ${CURRENT_TARGET_OPTION})

    endif()
endfunction()