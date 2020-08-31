#include "Application.h"
#include "Debug/Logger.h"

#if defined(IMGUI_ENABLED)

#include "Debug/ImGui/ImGuiManager.h"

#endif

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
// TODO get device before set window size

	currentApplication = this;

	LOG_INFO("SDL initialisation");

	const int fullscreen_flag = 0; // for fullscreen SDL_WINDOW_FULLSCREEN
	const Uint32 render_flag = SDL_RENDERER_ACCELERATED;

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

		SDL_SetWindowResizable(window, static_cast<SDL_bool>(true));

		renderer = SDL_CreateRenderer(window, -1, render_flag);
		if (renderer != nullptr) {
			renderDrawColor();
			SDL_RenderClear(getRenderer());
			LOG_INFO("Renderer created");
		} else {
			LOG_ERROR("Application::Application Renderer couldn't created!");
		}

		state = State::stateReady;

		/***
		 * Change renderer scale for all devices
		 */
		auto[_w, _h, _dpi] = GetWindowResolution();
		SDL_RenderSetScale(getRenderer(), _dpi, _dpi);

#if defined(IMGUI_ENABLED)
		GET_IMGUI_MANAGER().initialize();
#endif

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
		renderDrawColor();
		SDL_RenderClear(getRenderer());
		Render();
		PostRender();
		SDL_RenderPresent(getRenderer());
		deltaTime = SDL_GetTicks() - frameStart;
		if (frameDelay > deltaTime) { SDL_Delay(frameDelay - deltaTime); }
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

#if defined(IMGUI_ENABLED)
	GET_IMGUI_MANAGER().deinitialize();
#endif

	SDL_DestroyRenderer(getRenderer());
	SDL_DestroyWindow(window);

#if defined(IMGUI_ENABLED)
	GET_IMGUI_MANAGER().destroyContext();
#endif

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
		auto[w, h, dpi] = GetWindowResolution();
		SDL_RenderSetScale(renderer, dpi, dpi);

#if defined(IMGUI_ENABLED)
		GET_IMGUI_MANAGER().changeDimension();
#endif

	}
}

[[maybe_unused]] int Application::getWidth() const { return width; }

[[maybe_unused]] int Application::getHeight() const { return height; }

[[maybe_unused]] float Application::getWindowRatio() const { return float(width) / float(height); }

[[maybe_unused]] bool Application::windowDimensionChanged() const { return dimensionChanged; }

//TODO test this
[[maybe_unused]] std::tuple<int, int, float> Application::GetWindowResolution() {

	int w, h;
	if (!isEmscripten() && SDL_GetRendererOutputSize(getRenderer(), &w, &h) == 0) {
//     Client window is high dpi device
		return std::make_tuple(w, h, static_cast<float>(std::abs(w / width)));
	}

//   Unable to get the actual area size in pixels, so the resolution is 1:1
	return std::make_tuple(width, height, 1);
}

bool Application::isEmscripten() {
	auto emsTemp = EMSCRIPTEN_FLAG;
	emscripten = emsTemp == 1;
	return emscripten;
}
