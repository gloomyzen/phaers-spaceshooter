#ifndef TOWERDEFENSE_GAME_COLLISIONDETECTION_H
#define TOWERDEFENSE_GAME_COLLISIONDETECTION_H

#include "SDL.h"

namespace TGEngine::core {

class CollisionDetection {
public:
  static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
    return rectA.x + rectA.w >= rectB.x &&
           rectB.x + rectB.w >= rectA.x &&
           rectA.y + rectA.h >= rectB.y &&
           rectB.y + rectB.h >= rectA.y;
  }
};

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_COLLISIONDETECTION_H
