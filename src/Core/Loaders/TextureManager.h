#ifndef TOWERDEFENSE_GAME_TEXTUREMANAGER_H
#define TOWERDEFENSE_GAME_TEXTUREMANAGER_H

#include "../moduleDefinitions.h"

namespace TGEngine::core::deprecated {

    class TextureManager {
    public:
        static SDL_Texture *LoadTexture(const char *fileName);

        static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);

        static void DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    };

}


#endif// TOWERDEFENSE_GAME_TEXTUREMANAGER_H
