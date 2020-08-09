#ifndef TOWERDEFENSE_GAME_RESOURCEMANAGER_H
#define TOWERDEFENSE_GAME_RESOURCEMANAGER_H

#include "Core/moduleDefinitions.h"
#include <map>
#include <string>
#include "Loaders/TextureManager.h"
#include "Loaders/JsonLoader.h"

#define GET_RESOURCE_MANAGER() TGEngine::core::ResourceManager::getInstance()
#define GET_TEXTURE_MANAGER() TGEngine::core::ResourceManager::getInstance().getTextureManager()
#define GET_JSON_MANAGER() TGEngine::core::ResourceManager::getInstance().getJsonLoader()
#define GET_JSON(L) GET_JSON_MANAGER()->loadJson(L)
#define GET_JSON_PREF(L, K) GET_JSON_MANAGER()->loadJson(L, K)

namespace TGEngine::core {

    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();

        static ResourceManager &getInstance();

        TextureManager* getTextureManager();
        JsonLoader* getJsonLoader();

    private:
        TextureManager textureManagerInstance;
        JsonLoader jsonLoaderInstance;
    };

}


#endif //TOWERDEFENSE_GAME_RESOURCEMANAGER_H
