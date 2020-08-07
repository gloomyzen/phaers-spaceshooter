#include "GameApplication.h"

using namespace TGEngine::core;

GameApplication::GameApplication() : Application() {
#ifdef DEBUG1
    imGuiInstance = new ImGuiLoader(getWindow(), glslVersion);
#endif
}

GameApplication::~GameApplication() {}

void GameApplication::ProcessInput() {}

void GameApplication::Update() {
#ifdef DEBUG1
    imGuiInstance->Update(dt);
#endif
}

void GameApplication::Render() {
#ifdef DEBUG1
    imGuiInstance->Render();
#endif
}

void GameApplication::PostRender() {
#ifdef DEBUG1
    imGuiInstance->PostRender();
#endif
}