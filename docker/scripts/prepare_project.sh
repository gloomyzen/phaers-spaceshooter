#!/bin/sh

##
# Variables
##
WORK_DIR=/var/www
SOURCE_DIR=/src
PUBLIC_DIR=/resources/wasm
args=("$@")
command=''

#shell test
#command=`emcc ${str} --shell-file ${WORK_DIR}/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/index.html -s \
#    NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_test', '_string_test', '_int_test', '_float_test', '_main']" -s \
#    EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"`
#command=`emcc ${str} --shell-file ${WORK_DIR}/resources/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/wasm/index.wasm`

function prepare_dir() {
    #prepare_project clear - for clear all last builds
#    if [[ -d "${WORK_DIR}${PUBLIC_DIR}" ]]; then
#        rm -rf ${WORK_DIR}${PUBLIC_DIR}
#    fi
    if [[ ! -d "${WORK_DIR}${PUBLIC_DIR}" ]]; then
        mkdir ${WORK_DIR}${PUBLIC_DIR}
        chmod -R 777 ${WORK_DIR}${PUBLIC_DIR}
    fi
}

function parse_command() {
#prepare_project --output=canvas --file=canvas.c --file=canvas1.c --arg=WASM=1
    command=''
    for key in "${!args[@]}"; do
#        if [[ ${key} > 1 ]]; then
            echo ${args[key]}
            IN="--arg=WASM=1"
            arrIN=(${IN//=/ })
            echo ${arrIN[0]}
#            command="${command} ${args[key]}"
#        fi
    done
#    echo $command
}
#
#case "${args[0]}" in
#    --clear|clear)
#        #prepare_project clear - for clear all last builds
#        if [[ -d "${WORK_DIR}${PUBLIC_DIR}" ]]; then
#            rm -rf ${WORK_DIR}${PUBLIC_DIR}
#        fi
#        if [[ ! -d "${WORK_DIR}${PUBLIC_DIR}" ]]; then
#            mkdir ${WORK_DIR}${PUBLIC_DIR}
#            chmod -R 777 ${WORK_DIR}${PUBLIC_DIR}
#        fi
#        ;;
#    --target|target)
#        parse_command
#        #prepare_project target target_name dependency.cpp dependency2.cpp - for build target
##        str=""
##        for key in "${!args[@]}"; do
##            if [[ ${key} > 1 ]]; then
##                str="${str} ${WORK_DIR}/${args[key]}"
##            fi
##        done
##
##        echo $str;
##        IN="--arg=WASM=1"
##        arrIN=(${IN//=/ })
##        echo ${arrIN[0]}
#
##        command=`emcc ${str} --shell-file ${WORK_DIR}/resources/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/${args[1]}.wasm`
##        exec ${command}
#        ;;
#    *)
#        echo "Nothing caused.\n"
#        exit 1
#
#esac
