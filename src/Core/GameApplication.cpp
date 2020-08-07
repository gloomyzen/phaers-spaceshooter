#include "GameApplication.h"
#include "Nodes/NodeManager.h"

using namespace TGEngine::core;

GameApplication::GameApplication() : Application() {
#ifdef DEBUG1
    imGuiInstance = new ImGuiLoader(getWindow(), glslVersion);
#endif
}

GameApplication::~GameApplication() {
    GET_NODE_MANAGER().init();
}

void GameApplication::ProcessInput() {}

void GameApplication::Update() {
#ifdef DEBUG1
    imGuiInstance->Update(dt);
#endif
    GET_NODE_MANAGER().update();
}

void GameApplication::Render() {
#ifdef DEBUG1
    imGuiInstance->Render();
#endif
    GET_NODE_MANAGER().render();
}

void GameApplication::PostRender() {
#ifdef DEBUG1
    imGuiInstance->PostRender();
#endif
}