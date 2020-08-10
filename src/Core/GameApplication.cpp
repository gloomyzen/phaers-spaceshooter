#include "GameApplication.h"
#include "Nodes/NodeManager.h"
#include "Game/StateModule/StateManager.h"
#include "imgui.h"
#include "Debug/imgui_sdl.h"

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
    ImGuiIO& io = ImGui::GetIO();
    SDL_PollEvent(&getEvents());
    if (getEvents().type == SDL_QUIT) { state = stateExit; }
    else if (getEvents().type == SDL_WINDOWEVENT)
    {
        if (getEvents().window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            io.DisplaySize.x = static_cast<float>(getEvents().window.data1);
            io.DisplaySize.y = static_cast<float>(getEvents().window.data2);
        }
    }
    else if (getEvents().type == SDL_MOUSEWHEEL)
    {
        wheel = getEvents().wheel.y;
    }
    while (SDL_PollEvent(&getEvents()))
    {
        if (getEvents().type == SDL_QUIT) { state = stateExit; }
        else if (getEvents().type == SDL_WINDOWEVENT)
        {
            if (getEvents().window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                io.DisplaySize.x = static_cast<float>(getEvents().window.data1);
                io.DisplaySize.y = static_cast<float>(getEvents().window.data2);
            }
        }
        else if (getEvents().type == SDL_MOUSEWHEEL)
        {
            wheel = getEvents().wheel.y;
        }
    }
    int mouseX, mouseY;
    const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);

    // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

    io.DeltaTime = 1.0f / 60.0f;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseWheel = static_cast<float>(wheel);
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
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

}

void GameApplication::PostRender() {
#ifdef DEBUG1
    imGuiInstance->PostRender();
#endif
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

}