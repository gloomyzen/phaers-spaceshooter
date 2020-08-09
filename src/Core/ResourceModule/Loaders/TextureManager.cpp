#include "TextureManager.h"
#include "Core/GameApplication.h"
#include "Core/Debug/Logger.h"

using namespace TGEngine::core;

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
    clearStorage();
}

SDL_Texture *TextureManager::LoadTexture(const char *filePath) {
    std::string fullPath = "resources/sprites/";
    fullPath += filePath;
    if (hasLoadedTexture(fullPath.c_str())) {
        return texturesMap[fullPath.c_str()];
    }
    SDL_Surface *tempSurface = IMG_Load(fullPath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(GET_APPLICATION().getRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture == nullptr) {
        LOG_ERROR("ResourceManager::LoadTexture Texture '" + fullPath + "' not loaded!");
    }
    texturesMap.insert(std::pair(fullPath.c_str(), texture));

    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(GET_APPLICATION().getRenderer(), tex, &src, &dest);
}

void TextureManager::DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(GET_APPLICATION().getRenderer(), tex, &src, &dest, angle, nullptr, flip);
}

bool TextureManager::hasLoadedTexture(const char *filePath) {
    return texturesMap.find(filePath) != texturesMap.end();
}

void TextureManager::clearStorage() {
    texturesMap.clear();
}
