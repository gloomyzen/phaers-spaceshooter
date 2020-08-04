#ifndef TOWERDEFENSE_GAME_SPRITECOMPONENT_H
#define TOWERDEFENSE_GAME_SPRITECOMPONENT_H

#include "AllComponentsHeaders.h"
#include "SDL.h"
#include "../Loaders/TextureManager.h"
#include <map>
#include "../moduleDefinitions.h"

namespace TGEngine::core {

struct sAnimation {
  int index;
  int frames;
  int speed;

  sAnimation() {
    index = 0;
    frames = 0;
    speed = 0;
  }

  sAnimation(int _index, int _frames, int _speed) {
    index = _index;
    frames = _frames;
    speed = _speed;
  }
};

class SpriteComponent : public Component {
private:
  TransformComponent *transform{};
  SDL_Texture *texture{};
  SDL_Rect srcRect{}, destRect{};

  bool mAnimated = false;
  int frames = 0;
  int speed = 100;
  int animIndex = 0;
  std::map<std::string, sAnimation> animations;
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

public:
  SpriteComponent() = default;
  explicit SpriteComponent(const char* path/*, int width, int height*/)
  {
    setTexture(path);
  }

  explicit SpriteComponent(const char* path, bool _isAnimated)
  {
    mAnimated = _isAnimated;

    if (isAnimated()) {
      //TODO need methods for install animations
      sAnimation idle = sAnimation(0, 8, 150);
      sAnimation walk = sAnimation(2, 6, 150);
      animations.emplace("Idle", idle);
      animations.emplace("Walk", walk);

      play("Idle");
    }

    setTexture(path);
  }
  ~SpriteComponent() {
    SDL_DestroyTexture(texture);
  }

  void init() override
  {
    if (!getNode().hasComponent<TransformComponent>()) {
      getNode().addComponent<TransformComponent>();
    }

    transform = &getNode().getComponent<TransformComponent>();
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = transform->getWidth();
    srcRect.h = transform->getHeight();
    destRect.w = static_cast<int>(static_cast<float>(transform->getWidth()) * transform->getScale());
    destRect.h = static_cast<int>(static_cast<float>(transform->getHeight()) * transform->getScale());
  }

  void update() override
  {
    if(isAnimated()) {
      srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / static_cast<unsigned int>(speed)) % static_cast<unsigned int>(frames));
    }
    srcRect.y = animIndex * transform->getHeight();

    destRect.x = static_cast<int>(transform->getPosition().getX());
    destRect.y = static_cast<int>(transform->getPosition().getY());
    destRect.w = static_cast<int>(static_cast<float>(transform->getWidth()) * transform->getScale());
    destRect.h = static_cast<int>(static_cast<float>(transform->getHeight()) * transform->getScale());
  }

  void render() override
  {
    TextureManager::DrawFlip(texture, srcRect, destRect, spriteFlip);
  }

  void setTexture(const char* path)
  {
    texture = TextureManager::LoadTexture(path);
  }

  bool textureIsInited() {
    return texture != nullptr;
  }

  bool isAnimated() { return mAnimated; }
  void setAnimated(bool value) { mAnimated = value; }

  void play(const std::string &animationName) {
    //todo test wrong key
    frames = animations[animationName].frames;
    animIndex = animations[animationName].index;
    speed = animations[animationName].speed;
  }

  //TODO get one animation
  //sAnimation getAnimation(std::string animName) {
  //  //
  //}

  void addAnimation(const std::string &animName, int _index, int _frames, int _speed) {
    animations.emplace(animName, sAnimation(_index, _frames, _speed));
  }

  void addAnimation(const std::string &animName, sAnimation animation) {
    animations.emplace(animName, animation);
  }

  std::map<std::string, sAnimation>& getAnimations() {
    return animations;
  }
};

}

#endif// TOWERDEFENSE_GAME_SPRITECOMPONENT_H
