#ifndef TOWERDEFENSE_GAME_TEXTUREMANAGER_H
#define TOWERDEFENSE_GAME_TEXTUREMANAGER_H

#include "../../moduleDefinitions.h"
#include <map>
#include <string>

namespace TGEngine::core {

    class TextureManager {
    public:
        TextureManager();
        ~TextureManager();

        bool hasLoadedTexture(const char *filePath);

        SDL_Texture *LoadTexture(const char *filePath);

        void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);

        void DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void clearStorage();

    private:
        std::map<const char *, SDL_Texture*> texturesMap{};
    };

}//TGEngine::core


#endif //TOWERDEFENSE_GAME_TEXTUREMANAGER_H
