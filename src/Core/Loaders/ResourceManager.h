#ifndef TOWERDEFENSE_GAME_RESOURCEMANAGER_H
#define TOWERDEFENSE_GAME_RESOURCEMANAGER_H

#include "../moduleDefinitions.h"
#include <map>
#include <string>

#define GET_RESOURCE_MANAGER() TGEngine::core::ResourceManager::getInstance()

namespace TGEngine::core {

    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();

        static ResourceManager &getInstance();

        bool hasLoadedTexture(const char *fileName);

        SDL_Texture *LoadTexture(const char *fileName);

        void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);

        void DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        std::map<const char *, SDL_Texture*> texturesMap{};
    };

}//TGEngine::core


#endif //TOWERDEFENSE_GAME_RESOURCEMANAGER_H
