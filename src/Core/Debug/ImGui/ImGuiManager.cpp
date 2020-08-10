#include "ImGuiManager.h"
#if defined(IMGUI_ENABLED)
#include "imgui.h"
#include "Core/Debug/ImGui/SDLImplements/imgui_sdl.h"
#include "Core/GameApplication.h"
#endif

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

void ImGuiManager::Render() {
#if defined(IMGUI_ENABLED)
    ImGui::NewFrame();

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", static_cast<double>(1000.0f / ImGui::GetIO().Framerate),
                static_cast<double>(ImGui::GetIO().Framerate));
    ImGui::End();
#endif
}

void ImGuiManager::PostRender() {
#if defined(IMGUI_ENABLED)
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
#endif
}
