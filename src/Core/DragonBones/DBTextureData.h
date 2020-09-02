#ifndef TGENGINE_DBTEXTUREDATA_H
#define TGENGINE_DBTEXTUREDATA_H

#include <memory>
#include <Core/moduleDefinitions.h>
#include <dragonBones/DragonBonesHeaders.h>

namespace TGEngine::core::dragonBonesModule {
	using namespace dragonBones;

	class DBTextureData : public TextureData {
	BIND_CLASS_TYPE_B(DBTextureData);

	public:
		SDL_Texture *texture;

	public:
		DBTextureData() {
			_onClear();
		}

		virtual ~DBTextureData() {
			_onClear();
		}

		void _onClear() override {
			texture = nullptr;

			TextureData::_onClear();
		}

		void setTexture(SDL_Texture *_texture, SDL_Rect rect) {
			region.x = 0.f;
			region.y = 0.f;
			region.width = static_cast<float>(rect.x);
			region.height = static_cast<float>(rect.y);

			texture = _texture;
		}
	};
}


#endif //TGENGINE_DBTEXTUREDATA_H
