#ifndef TOWERDEFENSE_GAME_CAMERACOMPONENT_H
#define TOWERDEFENSE_GAME_CAMERACOMPONENT_H

#include "Core/moduleDefinitions.h"
#include "AllComponentsHeaders.h"

namespace TGEngine::core {

//TODO class incomplete!

    class CameraComponent : public Component {
        TransformComponent *position;
        TransformComponent *target;

        CameraComponent();

        void init() override {
            //Setup variables
        }

        void update() override {
            //change coordinates, like this
        }

        void render() override {}
    };

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_CAMERACOMPONENT_H
