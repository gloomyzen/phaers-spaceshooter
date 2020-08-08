#include "ResourceManager.h"
#include "../GameApplication.h"
#include "../Debug/Logger.h"

using namespace TGEngine::core;

ResourceManager *currentResourceManager = nullptr;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager &ResourceManager::getInstance() {
    if (currentResourceManager == nullptr) {
        currentResourceManager =  new ResourceManager();
    }
    return *currentResourceManager;
}

TextureManager *ResourceManager::getTextureManager() {
    return &textureManagerInstance;
}

JsonLoader *ResourceManager::getJsonLoader() {
    return &jsonLoaderInstance;
}
