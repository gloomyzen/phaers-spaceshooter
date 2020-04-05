#!/bin/sh

WORK_DIR=/var/www
SOURCE_DIR=/src
PUBLIC_DIR=/public
PUBLIC_DIR=/resources/temp

argsArray=("$@")

str=""
for arg in "${argsArray[@]}"; do
   str="${str} ${WORK_DIR}${SOURCE_DIR}/${arg}"
done

source /var/emsdk/emsdk_env.sh
echo ${str}

#shell test
#command=`emcc ${str} --shell-file ${WORK_DIR}/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/index.html -s \
#    NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_test', '_string_test', '_int_test', '_float_test', '_main']" -s \
#    EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"`
command=`emcc ${str} --shell-file ${WORK_DIR}/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/index.html`

exec ${command}