#include "GameApplication.h"
#include "Nodes/NodeManager.h"
#include "Game/StateModule/StateManager.h"
#if defined(IMGUI_ENABLED)
#include "Core/Debug/ImGui/ImGuiManager.h"
#endif

using namespace TGEngine::core;

GameApplication::GameApplication() : Application() {}

GameApplication::~GameApplication() {}

void GameApplication::Init() {
    GET_NODE()->init();
    GET_STATE_MANAGER().registerState(TGEngine::game::eStateType::MAIN_MENU, []() -> bool {
        auto testNode = new Node("testNode");
        testNode->loadProperty("testScene");
        GET_NODE()->addChild(testNode);
        return true;
    });
    GET_STATE_MANAGER().changeState(TGEngine::game::eStateType::MAIN_MENU);
}

void GameApplication::ProcessInput() {
    while (SDL_PollEvent(&getEvents())) {
        if (getEvents().type == SDL_QUIT) { state = stateExit; }
#if defined(IMGUI_ENABLED)
        if (getEvents().type == SDL_MOUSEWHEEL) {
            GET_IMGUI_MANAGER().setWheel(getEvents().wheel.y);
        }
#endif
#if defined(IMGUI_ENABLED)
        GET_IMGUI_MANAGER().processInput(&getEvents());
#endif
    }
}

void GameApplication::Update() {
    GET_NODE()->update();
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().update();
#endif
}

void GameApplication::Render() {
    GET_NODE()->render();
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().render();
#endif
}

void GameApplication::PostRender() {
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().postRender();
#endif
}