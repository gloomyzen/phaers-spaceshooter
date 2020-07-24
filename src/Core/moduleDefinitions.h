#ifndef TOWERDEFENSE_GAME_MODULEDEFINITIONS_H
#define TOWERDEFENSE_GAME_MODULEDEFINITIONS_H

#include <iostream>
#ifdef WIN32
#define SDL_MAIN_HANDLED //Do not delete this!
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#if defined(__APPLE__) || defined(APPLE)
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif //__APPLE__ || APPLE
#endif
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN)
#include <emscripten.h>
#define EMSCRIPTEN_FLAG 0;
#else
#define EMSCRIPTEN_FLAG 1;
#endif //__EMSCRIPTEN__

#if defined(__DEBUG__) || defined(DEBUG)
const bool debugMode = true;
#else
const bool debugMode = false;
#endif


#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#define TGAME_WINDOW_WIDTH 800

#define TGAME_WINDOW_HEIGHT 600

#define TGAME_WINDOW_TITLE "TGame title"

#endif// TOWERDEFENSE_GAME_MODULEDEFINITIONS_H
