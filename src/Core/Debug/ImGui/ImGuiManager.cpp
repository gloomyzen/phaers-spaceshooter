#if defined(IMGUI_ENABLED)

#include "ImGuiManager.h"

using namespace TGEngine::core;
using namespace TGEngine::core::debug;

ImGuiManager *imguiInstance = nullptr;

ImGuiManager &ImGuiManager::getInstance() {
    if (imguiInstance == nullptr) {
        imguiInstance = new ImGuiManager();
    }
    return *imguiInstance;
}

void ImGuiManager::initialize() {
    ImGui::CreateContext();
    auto [width, height, dpi] = GET_APPLICATION().GetWindowResolution();
    ImGuiSDL::Initialize(GET_APPLICATION().getRenderer(), width, height);
    ImGuiSDL::SetupImGuiStyle();
}

void ImGuiManager::deinitialize() {
    ImGuiSDL::Deinitialize();
}

void ImGuiManager::destroyContext() {
    ImGui::DestroyContext();
}

void ImGuiManager::changeDimension() {
    ImGuiIO& changeIO = ImGui::GetIO();
    changeIO.DisplaySize.x = static_cast<float>(GET_APPLICATION().getEvents().window.data1);
    changeIO.DisplaySize.y = static_cast<float>(GET_APPLICATION().getEvents().window.data2);
}

void ImGuiManager::setWheel(int _wheel) {
    wheel = _wheel;
}

void ImGuiManager::processInput() {
    ImGuiIO& io = ImGui::GetIO();
    int mouseX, mouseY;
    const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);
    // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)
    io.DeltaTime = 1.0f / 60.0f;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseWheel = static_cast<float>(wheel);
}

ImRect ImGuiManager::renderTree(std::vector<Node *> n)
{
    const ImRect nodeRect = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    for (auto node : n) {
        const bool recurse = ImGui::TreeNode(node->getId().c_str());

        if (recurse) {
            renderTree(node->getChilds());
            ImGui::TreePop();
            ImGui::Separator();
        }
    }


    return nodeRect;
}

void ImGuiManager::render() {
    ImGui::NewFrame();

    renderTree(GET_NODE_MANAGER().getChilds());

    ImGui::Begin("Options");
    if (ImGui::Button("Debug"))
    {

    }
    ImGui::End();
}

void ImGuiManager::postRender() {
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
}

#endif //IMGUI_ENABLED
