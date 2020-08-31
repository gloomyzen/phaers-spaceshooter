#ifndef TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
#define TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H

#include "Core/moduleDefinitions.h"
#include "Component.h"
#include "Core/DataTypes/Vector2D.h"
#include "Core/Debug/Logger.h"

// TODO need rotation and anchor!
namespace TGEngine::core {

	class TransformComponent : public Component {
	private:
		Vector2D position;
		int width;
		int height;
		float scale;

	public:
		TransformComponent() {
			position.Zero();
			width = height = 0;
			scale = 1.f;
		}

		TransformComponent(float _x, float _y) {
			position.setX(_x);
			position.setY(_y);
			width = height = 0;
			scale = 1.f;
		}

		TransformComponent(float _x, float _y, int _width, int _height, float _scale) {
			position.setX(_x);
			position.setY(_y);
			width = _width;
			height = _height;
			scale = _scale;
		}

		void setWidth(int _width) {
			if (_width >= 0) {
				width = _width;
			} else {
				LOG_ERROR("TransformComponent::setWidth Trying add to width value '" + std::to_string(_width) + "'!");
			}
		}

		void setHeight(int _height) {
			if (_height >= 0) {
				height = _height;
			} else {
				LOG_ERROR(
						"TransformComponent::setHeight Trying add to height value '" + std::to_string(_height) + "'!");
			}
		}

		int getWidth() { return width; }

		int getHeight() { return height; }

		float getScale() { return scale; }

		void setScale(float _scale) {
			if (_scale >= 0 && _scale <= 10) {
				scale = _scale;
			} else {
				LOG_ERROR("TransformComponent::setScale Trying add to scale value '" + std::to_string(_scale) + "'!");
			}
		}

		void init() override {}

		void update() override {}

		void render() override {}

		Vector2D getPosition() { return position; }

		void setPosition(float _x, float _y) {
			position.setX(_x);
			position.setY(_y);
		}

		void setX(float _x) {
			position.setX(_x);
		}

		void setY(float _y) {
			position.setY(_y);
		}

		float getGlobalX() {
			float renderX = getPosition().getX();
			for (auto child : getNode().getParentsMap()) {
				if (child.second->hasComponent<TransformComponent>()) {
					renderX += child.second->getComponent<TransformComponent>().getPosition().getX();
				}
			}
			return renderX;
		}

		float getGlobalY() {
			float renderY = getPosition().getY();
			for (auto child : getNode().getParentsMap()) {
				if (child.second->hasComponent<TransformComponent>()) {
					renderY += child.second->getComponent<TransformComponent>().getPosition().getY();
				}
			}
			return renderY;
		}
	};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_TRANSFORMCOMPONENT_H
