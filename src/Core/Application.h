#ifndef TOWERDEFENSE_GAME_APPLICATION_H
#define TOWERDEFENSE_GAME_APPLICATION_H

#include "moduleDefinitions.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <tuple>

namespace TGEngine::core {

    class Application {
    public:
        Application();

        virtual ~Application() {};

        virtual void Init() {};

        virtual void ProcessInput() {};

        virtual void Update() {};

        virtual void Render() {};

        virtual void PostRender() {};


        static Application &getInstance();

        // get the window
        SDL_Window *getWindow();

        // get the renderer
        SDL_Renderer *getRenderer();

        // get the input events
        SDL_Event &getEvents();

        // window control
        void exit();

        // application run
        void run();

        // Application informations
        [[maybe_unused]] int getWidth() const;

        [[maybe_unused]] int getHeight() const;

        [[maybe_unused]] float getWindowRatio() const;

        [[maybe_unused]] bool windowDimensionChanged() const;

        [[maybe_unused]] std::tuple<int, int, float> GetWindowResolution();

        bool isEmscripten() const;

        float getDeltaTime() {
            return deltaTime;
        }

        void changeFps(int _fps) {
            FPS = _fps;
            frameDelay = 1000.f / static_cast<float>(FPS);
        }

        void changeFrameDelay(float _frameDelay) {
            frameDelay = _frameDelay;
        }

        int &getFps() { return FPS; }

        float &getFrameDelay() { return frameDelay; }

    private:
        Application &operator=(const Application &) { return *this; }

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Event event;

        void renderDrawColor();

        // Time:
        int FPS = 60;
        float frameDelay = 1000.f / static_cast<float>(FPS);
        Uint32 frameStart;
        float deltaTime;

        // Dimensions:
        int width;
        int height;
        bool dimensionChanged;

        void detectWindowDimensionChange();

        // Runtime env
        bool emscripten;

    protected:
        Application(const Application &) {};

        std::string title;

        enum State {
            stateReady, stateRun, stateExit
        };

        State state;
    };

}


#endif// TOWERDEFENSE_GAME_APPLICATION_H
