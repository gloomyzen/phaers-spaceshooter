#ifndef TOWERDEFENSE_GAME_COLLIDERCOMPONENT_H
#define TOWERDEFENSE_GAME_COLLIDERCOMPONENT_H

#include <string>
#include "SDL.h"
#include "AllComponentsHeaders.h"
#include "../DataTypes/Vector2D.h"
#include "CollisionDetection.h"

namespace TGEngine::core {

class ColliderComponent : public Component {

public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent* transform;

  ColliderComponent(const char* name) {
    tag = name;
  }

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();
  }

  void update() override {
    collider.x = static_cast<int>(transform->position.getX());
    collider.y = static_cast<int>(transform->position.getY());
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }

  void render() override {}
};

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_COLLIDERCOMPONENT_H
