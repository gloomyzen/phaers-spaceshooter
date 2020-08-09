#include "Core/GameApplication.h"
#include "Game/StateModule/StateManager.h"

using namespace TGEngine::core;

int main() {
  GameApplication app;
  app.run();
  GET_STATE_MANAGER().registerState(TGEngine::game::eStateType::MAIN_MENU, []() -> bool {

      return false;
  });
  return 0;
}