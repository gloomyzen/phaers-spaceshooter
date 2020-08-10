#include "ImGuiManager.h"
#if defined(IMGUI_ENABLED)
#include "imgui.h"
#include "imgui_internal.h"
#include "Core/Debug/ImGui/SDLImplements/imgui_sdl.h"
#include "Core/GameApplication.h"
#include "Core/Nodes/NodeManager.h"
#include "Core/Nodes/Node.h"
#endif

using namespace TGEngine::core;
using namespace TGEngine::core::debug;

ImGuiManager *imguiInstance = nullptr;

ImGuiManager &ImGuiManager::getInstance() {
    if (imguiInstance == nullptr) {
        imguiInstance = new ImGuiManager();
    }
    return *imguiInstance;
}

void ImGuiManager::Initialize() {
#if defined(IMGUI_ENABLED)
    ImGui::CreateContext();
    auto [width, height, dpi] = GET_APPLICATION().GetWindowResolution();
    ImGuiSDL::Initialize(GET_APPLICATION().getRenderer(), width, height);
#endif
}

void ImGuiManager::Deinitialize() {
#if defined(IMGUI_ENABLED)
    ImGuiSDL::Deinitialize();
#endif
}

void ImGuiManager::DestroyContext() {
#if defined(IMGUI_ENABLED)
    ImGui::DestroyContext();
#endif
}

void ImGuiManager::ChangeDimension() {
#if defined(IMGUI_ENABLED)
    ImGuiIO& changeIO = ImGui::GetIO();
    changeIO.DisplaySize.x = static_cast<float>(GET_APPLICATION().getEvents().window.data1);
    changeIO.DisplaySize.y = static_cast<float>(GET_APPLICATION().getEvents().window.data2);
#endif
}

void ImGuiManager::setWheel(int _wheel) {
    wheel = _wheel;
}

void ImGuiManager::ProcessInput() {
#if defined(IMGUI_ENABLED)
    ImGuiIO& io = ImGui::GetIO();
    int mouseX, mouseY;
    const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);

    // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

    io.DeltaTime = 1.0f / 60.0f;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseWheel = static_cast<float>(wheel);
#endif
}

ImRect RenderTree(std::vector<Node *> n);

void ImGuiManager::Render() {
#if defined(IMGUI_ENABLED)
    ImGui::NewFrame();

    RenderTree(GET_NODE_MANAGER().getChilds());

    ImGui::Begin("Options");
    if (ImGui::Button("Debug"))
    {

    }
    ImGui::End();
#endif
}

#if defined(IMGUI_ENABLED)
ImRect RenderTree(std::vector<Node *> n)
{
    const ImRect nodeRect = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    for (auto node : n) {
        const bool recurse = ImGui::TreeNode(node->getId().c_str());

//        ImDrawList* drawList = ImGui::GetWindowDrawList();
        if (recurse) {
            RenderTree(node->getChilds());
            ImGui::TreePop();
            ImGui::Separator();
        }
    }


    return nodeRect;
}
#endif

void ImGuiManager::PostRender() {
#if defined(IMGUI_ENABLED)
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
#endif
}
