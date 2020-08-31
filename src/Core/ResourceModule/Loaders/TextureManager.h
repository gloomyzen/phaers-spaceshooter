#ifndef TOWERDEFENSE_GAME_TEXTUREMANAGER_H
#define TOWERDEFENSE_GAME_TEXTUREMANAGER_H

#include "Core/moduleDefinitions.h"
#include <map>
#include <string>

namespace TGEngine::core {

	class TextureManager {
	public:
		TextureManager();
		~TextureManager();

		SDL_Texture *LoadTexture(const char *filePath);

		void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);

		void DrawFlip(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle = 0.0,
					  SDL_RendererFlip flip = SDL_FLIP_NONE);

		bool hasLoadedTexture(std::string);

		void clearStorage();
	};

}//TGEngine::core


#endif //TOWERDEFENSE_GAME_TEXTUREMANAGER_H
