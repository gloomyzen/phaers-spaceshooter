#!/usr/bin/env bash
#/usr/bin/env bash

##Variables
if [ "${OS}" == "Windows_NT" ]; then
    OS_TYPE="windows";
    CMAKECMD="winpty cmake.exe"
elif [ "${OSTYPE}" == "linux-gnu" ]; then
    OS_TYPE="linux";
    CMAKECMD="cmake"
else
    OS_TYPE="macos";
    CMAKECMD="cmake"
fi
## Constants
GREEN_OUTPUT='\033[0;32m'
RED_OUTPUT='\033[0;31m'
YELLOW_OUTPUT='\033[1;33m'
CLEAR_OUTPUT='\033[0m'
## Colored output
pc() {
    RES=""
    case "$1" in
        green)
            RES="${GREEN_OUTPUT}$2${CLEAR_OUTPUT}"
            ;;

        red)
            RES="${RED_OUTPUT}$2${CLEAR_OUTPUT}"
            ;;

        yellow)
            RES="${YELLOW_OUTPUT}$2${CLEAR_OUTPUT}"
            ;;

        *)
            RES="${CLEAR_OUTPUT}$2${CLEAR_OUTPUT}"
            ;;

    esac

    printf "${RES}"
}

install_win32_libs() {
  if [ ! -d "lib/win32/SDL" ]; then
    cd lib/win32 && chmod +x install.sh && ./install.sh VC $1 && cd ../../
  fi
}

create() {

case "$1" in
    win32)
        install_win32_libs x86
        mkdir -p build && cd build
        eval ${CMAKECMD} "'-GVisual Studio 16 2019'" "'-AWin32'" -DCMAKE_BUILD_TYPE=Debug ../
        ;;
    win64)
        install_win32_libs x64
        mkdir -p build && cd build
        eval ${CMAKECMD} -G" Visual Studio 16 2019" "-AWin64" -DCMAKE_BUILD_TYPE=Debug ../
        ;;
    mac|macos)
        mkdir -p build && cd build
        eval ${CMAKECMD} -G Xcode ../
        ;;
    *)
        pc "red" "Platform '$1' not found.\n"
        pc "yellow" "Available platforms: win32 win64 mac.\n"
        exit 1
esac

}

# todo other platform
case "$1" in
    -create|-c|-auto)
        create $2 $3 $4
        ;;
    --help|-h)
#        general_help $2 $3
        ;;
    *)
        pc "yellow" "Nothing caused.\n"
#        help_legend
        exit 1

esac


