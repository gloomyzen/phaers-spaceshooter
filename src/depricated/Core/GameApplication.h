#ifndef TGAME_GAMEAPPLICATION
#define TGAME_GAMEAPPLICATION

#include "Application.h"
#ifdef __DEBUG__
#include "Debug/ImGuiLoader.h"
#endif

namespace TGEngine::core {

class GameApplication : public Application
{
public:
  GameApplication();
  ~GameApplication();
  void ProcessInput(float);
  void Update(float);
  void Render();
  void PostRender();

private:
#ifdef __DEBUG__1
  ImGuiLoader *imGuiInstance = nullptr;
#endif
};

}

#endif// TGAME_GAMEAPPLICATION
