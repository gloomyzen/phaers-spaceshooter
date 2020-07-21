#ifndef TGAME_GAME_H
#define TGAME_GAME_H

namespace TGEngine::core {

enum GameState {
  GAME_RUNNING,
  GAME_MENU,
  GAME_PAUSE,
  GAME_WIN,
  GAME_LOOSE,
};

class Game
{
public:
  GameState state;

  Game();
  ~Game();
};

}


#endif// TGAME_GAME_H
