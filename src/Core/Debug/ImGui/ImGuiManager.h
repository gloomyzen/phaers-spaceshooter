#ifndef TOWERDEFENSE_GAME_IMGUIMANAGER_H
#define TOWERDEFENSE_GAME_IMGUIMANAGER_H

#define GET_IMGUI_MANAGER() TGEngine::core::debug::ImGuiManager::getInstance()

namespace TGEngine::core::debug {
    class ImGuiManager {
    public:
        [[maybe_unused]] static ImGuiManager &getInstance();
        [[maybe_unused]] void Initialize();
        [[maybe_unused]] void Deinitialize();
        [[maybe_unused]] void DestroyContext();
        [[maybe_unused]] void ChangeDimension();
        [[maybe_unused]] void ProcessInput();
        [[maybe_unused]] void Render();
        [[maybe_unused]] void PostRender();

        [[maybe_unused]] void setWheel(int _wheel);

    private:
        int wheel = 0;
    };
}

#endif //TOWERDEFENSE_GAME_IMGUIMANAGER_H
