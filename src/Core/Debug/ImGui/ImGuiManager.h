#if defined(IMGUI_ENABLED) && !defined(TOWERDEFENSE_GAME_IMGUIMANAGER_H)
#define TOWERDEFENSE_GAME_IMGUIMANAGER_H

#include "imgui.h"
#include "imgui_internal.h"
#include "Core/Debug/ImGui/SDLImplements/imgui_sdl.h"
#include "Core/GameApplication.h"
#include "Core/Nodes/NodeManager.h"
#include "Core/Nodes/Node.h"

#define GET_IMGUI_MANAGER() TGEngine::core::debug::ImGuiManager::getInstance()

namespace TGEngine::core::debug {
    class ImGuiManager {
    public:
        static ImGuiManager &getInstance();
        void initialize();
        void deinitialize();
        void destroyContext();
        void changeDimension();
        void processInput();
        void render();
        void postRender();

        void setWheel(int _wheel);

    private:
        void showNodeEditor();
        ImRect renderTree(std::vector<Node *> n);

        int wheel = 0;
        bool nodeEditor = false;
    };
}

#endif //IMGUI_ENABLED TOWERDEFENSE_GAME_IMGUIMANAGER_H
