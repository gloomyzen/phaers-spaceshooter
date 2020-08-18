#if defined(IMGUI_ENABLED)

#include "ImGuiManager.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Debug/Logger.h"

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
    windowWidth = width;
    windowHeight = height;
    windowDpi = dpi;
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
    auto [width, height, dpi] = GET_APPLICATION().GetWindowResolution();
    windowWidth = width;
    windowHeight = height;
    windowDpi = dpi;
}

void ImGuiManager::setWheel(int _wheel) {
    wheel = _wheel;
}

void ImGuiManager::processInput() {
    ImGuiIO& io = ImGui::GetIO();
    int mouseX, mouseY;
    const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);
    // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)
    io.DeltaTime = GET_APPLICATION().getFrameDelay();
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseWheel = static_cast<float>(wheel);
}

void ImGuiManager::render() {
    ImGui::NewFrame();

    static bool nodeEditorOpened = false;

    if (nodeEditorOpened) showNodeEditor(&nodeEditorOpened);

    ImGui::SetNextWindowSize(ImVec2(debugBtnW, debugBtnH));
    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(windowWidth) / windowDpi - static_cast<float>(debugBtnW) - 50, 50));
    ImGuiWindowFlags debugWindowFlags = ImGuiWindowFlags_NoTitleBar;
    debugWindowFlags |= ImGuiWindowFlags_NoResize;
    ImGui::Begin("Options", nullptr, debugWindowFlags);
    if (ImGui::Button("Debug"))
    {
        nodeEditorOpened = !nodeEditorOpened;
    }
    ImGui::End();
}

void ImGuiManager::showNodeEditor(bool* nodeEditorOpened) {
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(nodeEditorW), static_cast<float>(nodeEditorH)), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Property editor", reinterpret_cast<bool *>(nodeEditorOpened)))
    {
        ImGui::End();
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    ImGui::Columns(2);
    ImGui::Separator();

    renderTree(GET_NODE_MANAGER().getChilds());
    ImGui::NextColumn();
    renderPreferences(GET_NODE_MANAGER().findNode(lastTarget));

    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::PopStyleVar();
    ImGui::End();
};

ImRect ImGuiManager::renderTree(std::vector<Node *> n)
{
    const ImRect nodeRect = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    if (lastTarget == 0u) {
        lastTarget = n.front()->getChilds().front()->getUid();
    }
    for (auto &node : n) {
        ImGui::AlignTextToFramePadding();
        const std::string name = node->getId() + (node->isActive() ? "" : " #inactive");
        ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        if (lastTarget == node->getUid()) {
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        }
        if (!node->hasChilds()) {
            nodeFlags |= ImGuiTreeNodeFlags_Leaf;
        }
        bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)node->getUid(), nodeFlags, "%s", name.c_str());
        if (ImGui::IsItemClicked()) {
            //id of clicked element
            lastTarget = node->getUid();
        }
        if (nodeOpen) {
            ImGui::PushID(node->getUid());

            renderTree(node->getChilds());
            ImGui::PopID();
            ImGui::TreePop();
        }
    }


    return nodeRect;
}

ImRect ImGuiManager::renderPreferences(Node * node) {
    const ImRect prefRect = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    if (node == nullptr) {
        return prefRect;
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::CollapsingHeader("General info"))
    {
        ImGui::Text("Node Name(ID) %s", node->getId().c_str());
        ImGui::Text("Node GUI %u", node->getUid());
        auto &active = node->getActive();
        ImGui::Checkbox(" Is active", &active); ImGui::SameLine(150);
    }
    ImGui::Separator();

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::CollapsingHeader("Transform component"))
    {
        auto width = node->getComponent<TransformComponent>().getWidth();
        auto height = node->getComponent<TransformComponent>().getHeight();
        int vecWH[2] = {width, height};
        ImGui::DragInt2("Width/Height", vecWH, 1);
        if (vecWH[0] != width) {
            node->getComponent<TransformComponent>().setWidth(vecWH[0]);
        }
        if (vecWH[1] != height) {
            node->getComponent<TransformComponent>().setHeight(vecWH[1]);
        }
        auto position = node->getComponent<TransformComponent>().getPosition();
        auto xPos = position.getX();
        auto yPos = position.getY();
        float vecPos[2] = {xPos, yPos};
        ImGui::DragFloat2("X/Y position", vecPos, 1.f);
        if (vecPos[0] != xPos) {
            node->getComponent<TransformComponent>().setX(vecPos[0]);
        }
        if (vecPos[1] != yPos) {
            node->getComponent<TransformComponent>().setY(vecPos[1]);
        }
        auto scale = node->getComponent<TransformComponent>().getScale();
        auto tempScale = scale;
        ImGui::DragFloat("Scale", &scale, 0.1f);
        if (tempScale != scale) {
            node->getComponent<TransformComponent>().setScale(scale);
        }
    }
    ImGui::Separator();

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::CollapsingHeader("Sprite component"))
    {
        std::string image = "Image: " + node->getComponent<SpriteComponent>().getImagePath();
        ImGui::Text("%s", image.c_str());
    }
    ImGui::Separator();

    return prefRect;
}

void ImGuiManager::postRender() {
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
}

#endif //IMGUI_ENABLED
