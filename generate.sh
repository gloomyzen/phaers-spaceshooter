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

# todo other platform
case "$1" in
    --auto|-a)
        rm -rf build && mkdir build && cd build
#        eval ${CMAKECMD} -G "Visual Studio 16 2019" -A Win32 ../
        eval ${CMAKECMD} -G Xcode ../
        cd ../

        ;;
    --help|-h)
#        general_help $2 $3
        ;;
    *)
        pc "yellow" "Nothing caused.\n"
        help_legend
        exit 1

esac


