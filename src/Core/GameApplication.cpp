#include "GameApplication.h"
#include "Nodes/NodeManager.h"
#include "Game/StateModule/StateManager.h"

using namespace TGEngine::core;

GameApplication::GameApplication() : Application() {}

GameApplication::~GameApplication() {}

void GameApplication::Init() {
    GET_NODE_MANAGER().init();
    GET_STATE_MANAGER().registerState(TGEngine::game::eStateType::MAIN_MENU, []() -> bool {
        auto testNode = new Node("testNode");
        testNode->loadProperty("testScene");
        GET_NODE_MANAGER().addChild(testNode);
        return true;
    });
    GET_STATE_MANAGER().changeState(TGEngine::game::eStateType::MAIN_MENU);
#ifdef DEBUG1
    imGuiInstance = new ImGuiLoader(getWindow(), glslVersion);
#endif
}

void GameApplication::ProcessInput() {
    SDL_PollEvent(&getEvents());
    if (getEvents().type == SDL_QUIT) { state = stateExit; }
}

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