#include "Application.h"
#include "Debug/Logger.h"

using namespace TGEngine::core;

std::function<void()> registered_loop;

void loop_iteration() { registered_loop(); }

Application *currentApplication = nullptr;

Application &Application::getInstance() {
    if (currentApplication != nullptr) { return *currentApplication; }
    throw std::runtime_error("There is no current Application");
}

Application::Application()
        : width(TGAME_WINDOW_WIDTH), height(TGAME_WINDOW_HEIGHT), title(TGAME_WINDOW_TITLE), state(stateReady) {
    currentApplication = this;

    LOG_INFO("SDL initialisation");

    const int fullscreen_flag = 0; // for fullscreen SDL_WINDOW_FULLSCREEN
    const Uint32 render_flag = SDL_RENDERER_ACCELERATED;

    auto emsTemp = EMSCRIPTEN_FLAG;
    emscripten = emsTemp == 0;

#ifdef WIN32
    SDL_SetMainReady();
#endif
    if ((isEmscripten() && SDL_Init(SDL_INIT_VIDEO) == 0) || (!isEmscripten() && SDL_Init(SDL_INIT_EVERYTHING) == 0)) {
        if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) {
            LOG_WARNING("Application::Application Vsync rendering not enabled!");
        }
        LOG_INFO("SDL initialized");

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  fullscreen_flag);
        if (window != nullptr) {
            LOG_INFO("Window created");
        }

        renderer = SDL_CreateRenderer(window, -1, render_flag);
        if (getRenderer() != nullptr) {
            renderDrawColor();
            SDL_RenderClear(getRenderer());
            LOG_INFO("Renderer created");
        }
        //TODO    Application::camera = {0, 0, width, height};
        state = State::stateReady;
    } else {
        state = State::stateExit;
        LOG_ERROR("Application::Application Couldn't init SDL!");
    }
}

void Application::renderDrawColor() { SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); }

SDL_Window *Application::getWindow() { return window; }

SDL_Renderer *Application::getRenderer() { return renderer; }

SDL_Event &Application::getEvents() { return event; }

void Application::exit() { state = stateExit; }

/// Данные в милисекундах
int Application::getFrameDeltaTime() const { return deltaTime; }

void Application::run() {
    state = stateRun;

    registered_loop = [&]() {
        // compute new time and delta time
        frameStart = SDL_GetTicks();
        // Detect window related changes
        detectWindowDimensionChange();
        // ------- execute the frame code -------
        // 1. manage user input
        // -----------------
        ProcessInput();
        // update game state
        // -----------------
        Update();
        // render
        // ------
        SDL_RenderClear(getRenderer());
        Render();
        PostRender();
        SDL_RenderPresent(getRenderer());
        deltaTime = static_cast<int>(SDL_GetTicks() - frameStart);
        if (frameDelay > deltaTime) { SDL_Delay(static_cast<Uint32>(frameDelay - deltaTime)); }
    };

    /***
     * Main loop
     */
    Init();

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(loop_iteration, 0, 1);
#else
    while (state == stateRun) {
        loop_iteration();
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(getRenderer());
    IMG_Quit();
    SDL_Quit();
    LOG_INFO("Application stopped");
#endif
}

void Application::detectWindowDimensionChange() {
    int w, h;
#if defined(EMSCRIPTEN)
    emscripten_get_canvas_element_size("canvas", &w, &h);
#else
    SDL_GetWindowSize(getWindow(), &w, &h);
#endif

    dimensionChanged = (w != width || h != height);
    if (dimensionChanged) {
        width = w;
        height = h;
        SDL_SetWindowSize(getWindow(), width, height);
        // TODO reinit game or camera ?
    }
}

[[maybe_unused]] int Application::getWidth() const { return width; }

[[maybe_unused]] int Application::getHeight() const { return height; }

[[maybe_unused]] float Application::getWindowRatio() const { return float(width) / float(height); }

[[maybe_unused]] bool Application::windowDimensionChanged() const { return dimensionChanged; }

//TODO test this
//[[maybe_unused]] std::tuple<int, int, float> Application::GetWindowResolution()
//{
//
//  int w, h;
//  if (!isEmscripten() && SDL_GetRendererOutputSize(getRenderer(), &w, &h) == 0) {
//     Client window is high dpi device
//    return std::make_tuple(w, h, static_cast<float>(std::abs(w / width)));
//  }
//
//   Unable to get the actual area size in pixels, so the resolution is 1:1
//  return std::make_tuple(width, height, 1);
//}

bool Application::isEmscripten() const { return false; }
