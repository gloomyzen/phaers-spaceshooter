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
        : state(stateReady), width(TGAME_WINDOW_WIDTH), height(TGAME_WINDOW_HEIGHT), title(TGAME_WINDOW_TITLE) {
    currentApplication = this;

//  std::cout << "[Info] SDL initialisation" << std::endl;
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
            std::cout << "[Warning] Vsync rendering not enabled!" << std::endl;
        }
        std::cout << "[Info] SDL initialized" << std::endl;

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  fullscreen_flag);
        if (window != nullptr) { std::cout << "[Info] Window created" << std::endl; }

        renderer = SDL_CreateRenderer(window, -1, render_flag);
        if (renderer != nullptr) {
            renderDrawColor();
            SDL_RenderClear(renderer);
            std::cout << "[Info] Renderer created" << std::endl;
        }
        //TODO    Application::camera = {0, 0, width, height};
        state = State::stateReady;
    } else {
        state = State::stateExit;
        std::cout << "[Error] Couldn't init SDL!" << std::endl;
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
        SDL_PollEvent(&getEvents());
        if (getEvents().type == SDL_QUIT) { state = stateExit; }

        ProcessInput();

        // update game state
        // -----------------
        Update();

        // render
        // ------
        SDL_RenderClear(renderer);

        Render();

        PostRender();

        SDL_RenderPresent(renderer);

        deltaTime = static_cast<int>(SDL_GetTicks() - frameStart);
        if (frameDelay > deltaTime) { SDL_Delay(static_cast<Uint32>(frameDelay - deltaTime)); }

    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop_iteration, 0, 1);
#else
    while (state == stateRun) { loop_iteration(); }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    std::cout << "[Info] Application stopped" << std::endl;
#endif
}

void Application::detectWindowDimensionChange() {
    int w, h;
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN)
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
