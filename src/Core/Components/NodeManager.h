#ifndef TOWERDEFENSE_GAME_NODEMANAGER_H
#define TOWERDEFENSE_GAME_NODEMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Component.h"

#define GET_NODE_MANAGER() TGEngine::core::NodeManagerInstance::getInstance()

namespace TGEngine::core {

#pragma region ComponentsHelper
using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
  static ComponentID lastID = 0u;
  return lastID++;
}

template<typename T> inline ComponentID getComponentTypeID() noexcept
{
  static_assert(std::is_base_of<Component, T>::value, "");
  static ComponentID typeID = getNewComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component *, maxComponents>;

enum eNodeLayers : std::size_t { GROUND, UNITS, UI };
#pragma endregion ComponentsHelper

class Node;
class NodeManager;
class NodeManagerInstance;

class Node : IComponent {
private:
  std::vector<std::unique_ptr<Component>> components;
  ComponentArray componentArray{};
  ComponentBitSet componentBitSet;
  std::vector<Node*> childs{};
  std::string id{};
public:

  Node(std::string nodeId) {
    if (nodeId.empty()) {
      throw std::runtime_error("The current node has no id set!");
    }
    id = nodeId;
  }
  ~Node() {
    for (auto &c : childs) {
      delete c;
    }
  }

  void init() override {
//    if (!hasComponent<Tra>())
  }

  void update() override
  {
    for (auto &c : components) {
      if (c->isActive()) c->update();
    }
  }
  void render() override
  {
    for (auto &c : components) {
      if (c->isActive()) c->render();
    }
  }

  template<typename T>[[nodiscard]] bool hasComponent() const { return componentBitSet[getComponentTypeID<T>()]; }

  template<typename T, typename... TArgs> T &addComponent(TArgs &&... mArgs)
  {
    T *c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{ c };
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
  }

  template<typename T> T &getComponent() const
  {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }

  std::vector<Node*> &getChilds() {
    return childs;
  };

};


class NodeManager
{
public:
  NodeManager() = default;
  ~NodeManager() = default;
  void spawnTestObjects() {
//    auto node = new Node("test");
//    node->addComponent<TransformComponent>();
//    nodes.emplace_back(node);
  }
private:
  std::vector<Node*> nodes{};
  std::vector<Node*> *cache{};
  std::vector<Node*> *warmCache{};
};

class NodeManagerInstance {
public:
  static NodeManager &getInstance();
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_NODEMANAGER_H
