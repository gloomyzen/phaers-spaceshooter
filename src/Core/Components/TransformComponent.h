#ifndef TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
#define TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H

#include "../moduleDefinitions.h"
#include "Component.h"
#include "../DataTypes/Vector2D.h"

// todo rotation
namespace TGEngine::core {

class TransformComponent : public Component
{
private:
  Vector2D position;
  int width = 32;
  int height = 32;
  int scale = 1;

public:
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

  void init() override {}

  void update() override {}

  void render() override {}

  Vector2D getPosition() { return position; }

  void setPosition(float _x, float _y)
  {
    position.setX(_x);
    position.setY(_y);
  }
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
