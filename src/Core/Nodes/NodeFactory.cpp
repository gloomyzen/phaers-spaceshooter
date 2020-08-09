#include "NodeFactory.h"
#include "Core/Debug/Logger.h"

using namespace TGEngine::core;

std::map<std::string, eNodeFactory> componentsMap = {
        {"TransformComponent",  eNodeFactory::TRANSFORM_COMPONENT},
        {"SpriteComponent",     eNodeFactory::SPRITE_COMPONENT},
        {"AnimspriteComponent", eNodeFactory::ANIMSPRITE_COMPONENT},
};

void NodeFactory::getComponents(Node *node, const std::string &componentName, const rapidjson::GenericValue<rapidjson::UTF8<char>>::Object &object) {
    if (node == nullptr)
        return;

    if (!hasRegisteredComponent(componentName)) {
        LOG_ERROR("NodeFactory::getComponents Component '" + componentName + "' was not found!");
        return;
    }

    eNodeFactory needle = componentsMap[componentName];

    switch (needle) {
        case TRANSFORM_COMPONENT: {
            node->addComponent<TransformComponent>();
            auto &transform = node->getComponent<TransformComponent>();
            if (object.HasMember("position")) {
                auto positions = object["position"].GetArray();
                if (positions.Size() == 2) {
                    transform.setPosition(positions[0].GetFloat(), positions[1].GetFloat());
                } else {
                    LOG_ERROR("NodeFactory::getComponents Component '" + componentName + "' has '" + std::to_string(positions.Size()) + "' position keys!");
                }
            }
            if (object.HasMember("size")) {
                auto size = object["size"].GetArray();
                if (size.Size() == 2) {
                    transform.setWidth(size[0].GetInt());
                    transform.setHeight(size[1].GetInt());
                } else {
                    LOG_ERROR("NodeFactory::getComponents Component '" + componentName + "' has '" + std::to_string(size.Size()) + "' size keys!");
                }
            }
            if (object.HasMember("scale") && object["scale"].IsNumber()) {
                transform.setScale(object["scale"].GetFloat());
            }
        }
            break;
        case SPRITE_COMPONENT: {
            node->addComponent<SpriteComponent>();
            auto &sprite = node->getComponent<SpriteComponent>();
            if (object.HasMember("image") && object["image"].IsString()) {
                sprite.setTexture(object["image"].GetString());
            }
        }
            break;
        case ANIMSPRITE_COMPONENT:
            node->addComponent<SpriteComponent>();
            break;
    }
}

bool NodeFactory::hasRegisteredComponent(const std::string &componentName) {
    return (componentsMap.find(componentName) != componentsMap.end());
}
