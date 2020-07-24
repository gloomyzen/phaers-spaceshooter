#!/bin/bash

#SDL libraries version
SDL_VERSION="2.0.12"
SDL_TTF_VERSION="2.0.15"
SDL_MIXER_VERSION="2.0.4"
SDL_IMAGE_VERSION="2.0.5"

function print() {
    echo -e " > \033[31m$1\033[0m"
}

# $1 VC or mingw
if [ "$1" != "VC" ] && [ "$1" != "mingw" ]; then
  print "Current compiller '$1' not found! Exit."
  exit 1;
fi

# $2 x64 or x86
if [ "$2" != "x64" ] && [ "$2" != "x86" ]; then
  print "Current platform '$1' not found! Exit."
  exit 1;
fi

CURRENT_PLATFORM="$2"

function dolib() {
    # $1 URL
    # $2 Name
    print "Downloading $1"
    curl -s -o $2.zip "$1"
    print "Extracting data into lib/win32/$2"
    unzip -o $2.zip -d temp/
    mkdir -p $2/$3
    cp -r temp/$4/* $2/$3
    mkdir -p ../../build/src/Debug
    cp -r $2/$3/lib/$CURRENT_PLATFORM/*.dll ../../build/src/Debug
    rm -rf temp && rm $2.zip || exit $?
}

rm -r SDL 2> /dev/null

dolib \
    "https://www.libsdl.org/release/SDL2-devel-$SDL_VERSION-$1.zip" \
    SDL SDL2 "SDL2-$SDL_VERSION"
dolib \
    "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-$SDL_TTF_VERSION-$1.zip" \
    SDL SDL2_ttf "SDL2_ttf-$SDL_TTF_VERSION"
dolib \
    "https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-$SDL_MIXER_VERSION-$1.zip" \
    SDL SDL2_mixer "SDL2_mixer-$SDL_MIXER_VERSION"
dolib \
    "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-$SDL_IMAGE_VERSION-$1.zip" \
    SDL SDL2_image "SDL2_image-$SDL_IMAGE_VERSION"

print "Dependencies installed"