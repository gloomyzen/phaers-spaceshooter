#ifndef TOWERDEFENSE_GAME_KEYBOARDCONTROLLER_H
#define TOWERDEFENSE_GAME_KEYBOARDCONTROLLER_H

#include "../moduleDefinitions.h"
#include "AllComponentsHeaders.h"
#include "SDL.h"

namespace TGEngine::core {

class KeyboardController : public Component {
public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  KeyboardController() = default;

  void init() override {
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
    //TODO register all actions
    //TODO try to use and create TouchController Game::event.tfinger

    /*if (Game::event.type == SDL_KEYDOWN) {
      switch (Game::event.key.keysym.sym) {
      case SDLK_w:
//        transform->velocity.y = -1;
//        sprite->play("Walk");
        break;
      case SDLK_s:
//        transform->velocity.y = 1;
//        sprite->play("Walk");
        break;
      case SDLK_a:
//        transform->velocity.x = -1;
//        sprite->play("Walk");
//        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        break;
      case SDLK_d:
//        transform->velocity.x = 1;
//        sprite->play("Walk");
//        sprite->spriteFlip = SDL_FLIP_NONE;
        break;
      default:
        break;
      }
    }

    if (Game::event.type == SDL_KEYUP) {
      switch (Game::event.key.keysym.sym) {
      case SDLK_w:
//        transform->velocity.y = 0;
//        if (transform->velocity.x == 0) sprite->play("Idle");
        break;
      case SDLK_s:
//        transform->velocity.y = 0;
//        if (transform->velocity.x == 0) sprite->play("Idle");
        break;
      case SDLK_a:
//        transform->velocity.x = 0;
//        if (transform->velocity.y == 0) sprite->play("Idle");
        break;
      case SDLK_d:
//        transform->velocity.x = 0;
//        if (transform->velocity.y == 0) sprite->play("Idle");
        break;
      default:
        break;
      }
    }*/
  }

  void render() override {}
};

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_KEYBOARDCONTROLLER_H
