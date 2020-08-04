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
  int width;
  int height;
  float scale;

public:
  TransformComponent() {
    position.Zero();
    width = height = 0;
    scale = 1.f;
  }

  TransformComponent(float _x, float _y)
  {
    position.setX(_x);
    position.setY(_y);
    width = height = 0;
    scale = 1.f;
  }

  TransformComponent(float _x, float _y, int _width, int _height, float _scale)
  {
    position.setX(_x);
    position.setY(_y);
    width = _width;
    height = _height;
    scale = _scale;
  }

  void setWidth(int _width) {
    if (_width >= 0) {
      width = _width;
    } else {
      //TODO Add here Log_error and do nothing!
    }
  }
  void setHeight(int _height) {
    if (_height >=0) {
      height = _height;
    } else {
      //TODO Add here Log_error and do nothing!
    }
  }
  int getWidth() { return width; }
  int getHeight() { return height; }
  float getScale() { return scale; }
  void setScale(float _scale) {
    if (_scale >= 0 && _scale <= 10) {
      scale = _scale;
    } else {
      //TODO Add here Log_error and do nothing!
    }
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
