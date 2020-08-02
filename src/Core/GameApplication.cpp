#include "GameApplication.h"
#include "Components/NodeManager.h"

using namespace TGEngine::core;

GameApplication::GameApplication() : Application()
{
#ifdef __DEBUG__1
  imGuiInstance = new ImGuiLoader(getWindow(), glslVersion);
#endif
}

GameApplication::~GameApplication() {}

void GameApplication::ProcessInput() {}

void GameApplication::Update() {
#ifdef __DEBUG__1
  imGuiInstance->Update(dt);
#endif
}
void GameApplication::Render() {
#ifdef __DEBUG__1
  imGuiInstance->Render();
#endif
}

void GameApplication::PostRender() {
#ifdef __DEBUG__1
  imGuiInstance->PostRender();
#endif
}