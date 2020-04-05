#!/bin/sh

WORK_DIR=/var/www
SOURCE_DIR=/src
PUBLIC_DIR=/public

argsArray=("$@")

str=""
for arg in "${argsArray[@]}"; do
   str="${str} ${WORK_DIR}${SOURCE_DIR}/${arg}"
done

source /var/emsdk/emsdk_env.sh
echo ${str}

command="emcc ${str} --shell-file ${WORK_DIR}/stub/shell_file.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/index.html"

exec ${command}