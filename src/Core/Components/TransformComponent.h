#ifndef TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
#define TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H

#include "AllComponentsHeaders.h"
#include "../DataTypes/Vector2D.h"

// todo rotation
namespace TGEngine::core {

class TransformComponent : public Component
{
private:
  Vector2D position;

public:
//  Vector2D position;
//  Vector2D velocity;
//  Vector2D movement;

  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  double deltaTime = 0;

  const float deltaSpeed = 1.0f;
  const float maxSpeed = 3.0f;

  int width = 32;
  int height = 32;
  int scale = 1;

  TransformComponent() { position.Zero(); }

  TransformComponent(float _x, float _y)
  {
    position.setX(_x);
    position.setY(_y);
  }

  TransformComponent(float _x, float _y, int _width, int _height, int _scale)
  {
    position.setX(_x);
    position.setY(_y);
    width = _width;
    height = _height;
    scale = _scale;
  }

  void init() override
  {
    //
  }

  void update() override
  {
    /*LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

    position.x += movement.x = getMovement(&velocity.x, &movement.x, &deltaTime);
    position.y += movement.y = getMovement(&velocity.y, &movement.y, &deltaTime);*/
  }

  void render() override {}

  Vector2D getPosition() { return position; }

  void setPosition(float _x, float _y)
  {
    position.setX(_x);
    position.setY(_y);
  }

private:
  //TODO Выпилить отсюда
  /*float getMovement(const float *pVelocity, float *pMovement, const double *pDeltaTime)
  {
    if (abs(*pVelocity) > 0 && ((*pVelocity > 0 && *pMovement >= 0) || (*pVelocity < 0 && *pMovement <= 0))) {
      if (abs(*pMovement + (deltaSpeed / *pDeltaTime)) <= maxSpeed) {
        *pMovement = *pMovement + (deltaSpeed / *pDeltaTime) * *pVelocity;
      } else {
        *pMovement = maxSpeed * *pVelocity;
      }
    } else {
      if (*pMovement > 0) {
        *pMovement = *pMovement - (deltaSpeed / *pDeltaTime * 2);
        *pMovement = abs(*pMovement) > 0.1f ? *pMovement : 0;
      } else if (*pMovement < 0) {
        *pMovement = *pMovement + (deltaSpeed / *pDeltaTime * 2);
        *pMovement = abs(*pMovement) > 0.1f ? *pMovement : 0;
      } else {
        *pMovement = 0;
      }
    }
    return *pMovement;
  }*/
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
