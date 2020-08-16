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
    GET_NODE_MANAGER().init();
    GET_STATE_MANAGER().registerState(TGEngine::game::eStateType::MAIN_MENU, []() -> bool {
        auto testNode = new Node("testNode");
        testNode->loadProperty("testScene");
        GET_NODE_MANAGER().addChild(testNode);
        return true;
    });
    GET_STATE_MANAGER().changeState(TGEngine::game::eStateType::MAIN_MENU);
}

void GameApplication::ProcessInput() {
//    SDL_PollEvent(&getEvents());
//    if (getEvents().type == SDL_QUIT) { state = stateExit; }
//    else if (getEvents().type == SDL_MOUSEWHEEL)
//    {
//#if defined(IMGUI_ENABLED)
//        GET_IMGUI_MANAGER().setWheel(getEvents().wheel.y);
//#endif
//    }
//#if defined(IMGUI_ENABLED)
//    GET_IMGUI_MANAGER().processInput();
//#endif
    while (SDL_PollEvent(&getEvents())) {
        if (getEvents().type == SDL_QUIT) { state = stateExit; }
#if defined(IMGUI_ENABLED)
        if (getEvents().type == SDL_MOUSEWHEEL) {
            GET_IMGUI_MANAGER().setWheel(getEvents().wheel.y);
        }
#endif
    }
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().processInput();
#endif
}

void GameApplication::Update() {
    GET_NODE_MANAGER().update();
}

void GameApplication::Render() {
    GET_NODE_MANAGER().render();
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().render();
#endif
}

void GameApplication::PostRender() {
#if defined(IMGUI_ENABLED)
    GET_IMGUI_MANAGER().postRender();
#endif
}