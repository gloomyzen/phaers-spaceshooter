#include "TextureManager.h"
#include "../../GameApplication.h"
#include "../../Debug/Logger.h"

using namespace TGEngine::core;

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
    clearStorage();
}

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    if (hasLoadedTexture(fileName)) {
        return texturesMap[fileName];
    }
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(GET_APPLICATION().getRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture == nullptr) {
        LOG_ERROR("ResourceManager::LoadTexture Texture '" + static_cast<std::string>(fileName) + "' not loaded!");
    }
    texturesMap.insert(std::pair(fileName, texture));

    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(GET_APPLICATION().getRenderer(), tex, &src, &dest);
}

void TextureManager::DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(GET_APPLICATION().getRenderer(), tex, &src, &dest, angle, nullptr, flip);
}

bool TextureManager::hasLoadedTexture(const char *fileName) {
    return texturesMap.find(fileName) != texturesMap.end();
}

void TextureManager::clearStorage() {
    texturesMap.clear();
}
