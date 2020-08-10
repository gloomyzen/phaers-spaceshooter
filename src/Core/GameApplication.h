#ifndef TOWERDEFENSE_GAME_GAMEAPPLICATION_H
#define TOWERDEFENSE_GAME_GAMEAPPLICATION_H

#include "Application.h"

#define GET_APPLICATION() TGEngine::core::GameApplication::getInstance()

namespace TGEngine::core {

    class GameApplication : public Application {
    public:
        GameApplication();

        ~GameApplication();

        void Init();

        void ProcessInput();

        void Update();

        void Render();

        void PostRender();
    };

}


#endif// TOWERDEFENSE_GAME_GAMEAPPLICATION_H
