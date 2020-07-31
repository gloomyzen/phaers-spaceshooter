#ifndef TOWERDEFENSE_GAME_TOUCHCONTROLLER_H
#define TOWERDEFENSE_GAME_TOUCHCONTROLLER_H

#include "../moduleDefinitions.h"
#include "AllComponentsHeaders.h"
#include "SDL.h"

namespace TGEngine::core {

class TouchController : public Component {
public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  float touchX;
  float touchY;
  float motionX;
  float motionY;

  TouchController() = default;

  void init() override {
    //TODO remove this
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    if (!entity->hasComponent<SpriteComponent>()) {
      entity->addComponent<SpriteComponent>();
    }
    sprite = &entity->getComponent<SpriteComponent>();
  }

  void update() override {
    //TODO need try to use Game::event.tfinger.dx|dy
    // event.tfinger.dx|dy contain the distance moved in the x-axis, normalized (-1...1)
    /*if (Game::event.type == SDL_FINGERDOWN) {
      touchX = Game::event.tfinger.x;
      touchY = Game::event.tfinger.y;
    }
    if (Game::event.type == SDL_FINGERMOTION) {
      motionX = Game::event.tfinger.x;
      motionY = Game::event.tfinger.y;
      if (abs(touchX - motionX) > 0.01f && touchX < motionX) {
        transform->velocity.x = 1;
        motionY = Game::event.tfinger.y;
        sprite->play("Walk");
        sprite->spriteFlip = SDL_FLIP_NONE;
      } else if (abs(touchX - motionX) > 0.01f && touchX > motionX) {
        transform->velocity.x = -1;
        motionY = Game::event.tfinger.y;
        sprite->play("Walk");
        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
      } else {
        transform->velocity.x = 0;
      }
      if (abs(touchY - motionY) > 0.01f && touchY < motionY) {
        transform->velocity.y = 1;
        motionX = Game::event.tfinger.x;
        sprite->play("Walk");
      } else if (abs(touchY - motionY) > 0.01f && touchY > motionY) {
        transform->velocity.y = -1;
        motionX = Game::event.tfinger.x;
        sprite->play("Walk");
      } else {
        transform->velocity.y = 0;
      }
    }
    if (Game::event.type == SDL_FINGERUP) {
      transform->velocity.x = 0;
      transform->velocity.y = 0;
      sprite->play("Idle");
    }*/
  }

  void render() override {}
};

}

#endif// TOWERDEFENSE_GAME_TOUCHCONTROLLER_H
