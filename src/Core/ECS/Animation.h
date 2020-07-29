#ifndef TOWERDEFENSE_GAME_ANIMATION_H
#define TOWERDEFENSE_GAME_ANIMATION_H

namespace TGEngine::core {

struct Animation {
  int index;
  int frames;
  int speed;

  Animation() {
    //
  }
  Animation(int _index, int _frames, int _speed) {
    index = _index;
    frames = _frames;
    speed = _speed;
  }
};

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_ANIMATION_H
