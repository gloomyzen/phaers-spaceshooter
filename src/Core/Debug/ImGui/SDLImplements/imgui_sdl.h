#if defined(IMGUI_ENABLED) && !defined(TOWERDEFENSE_GAME_IMGUI_SDL_H)
#define TOWERDEFENSE_GAME_IMGUI_SDL_H

#include "Core/moduleDefinitions.h"

struct ImDrawData;
struct SDL_Renderer;

namespace ImGuiSDL
{
    // Call this to initialize the SDL renderer device that is internally used by the renderer.
    void Initialize(SDL_Renderer* renderer, int windowWidth, int windowHeight);

    void SetupImGuiStyle();
    // Call this before destroying your SDL renderer or ImGui to ensure that proper cleanup is done. This doesn't do anything critically important though,
    // so if you're fine with small memory leaks at the end of your application, you can even omit this.
    void Deinitialize();

    // Call this every frame after ImGui::Render with ImGui::GetDrawData(). This will use the SDL_Renderer provided to the interfrace with Initialize
    // to draw the contents of the draw data to the screen.
    void Render(ImDrawData* drawData);

    void InitSDL2Keymap();
}


#endif //defined(IMGUI_ENABLED) && TOWERDEFENSE_GAME_IMGUI_SDL_H
