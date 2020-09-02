#ifndef TGENGINE_DBNODE_H
#define TGENGINE_DBNODE_H

#include <dragonBones/DragonBonesHeaders.h>
#include "Core/Components/Component.h"
#include "Core/DataTypes/Vector2D.h"

namespace TGEngine::core::dragonBonesModule {
	using namespace dragonBones;

	class SFMLNode : public IComponent {
	protected:
		Vector2D _transform;
		bool _visible = true;

		int _zOffset = 0;

	public:
		SFMLNode() = default;

		virtual ~SFMLNode() = default;

		void setZOffset(int zOffset) { _zOffset = zOffset; }

		int getZOffset() const { return _zOffset; }

		void setMatrix(const Matrix &matrix, const Vector2D &offset, float scaleX, float scaleY) {
			_transform = sf::Transform(
					matrix.a * scaleX,
					matrix.c * scaleY,
					offset.getX(),
					matrix.b * scaleX,
					matrix.d * scaleY,
					offset.getY(),
					0.f,
					0.f,
					1.f
			);
		}

		virtual void setVisible(bool visible) { _visible = visible; }

		virtual void setColor(const sf::Color &color) = 0;

		virtual sf::FloatRect getBoundingBox() const = 0;
	};
}

#endif //TGENGINE_DBNODE_H
