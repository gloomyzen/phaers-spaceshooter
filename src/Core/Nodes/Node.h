#ifndef TOWERDEFENSE_GAME_NODE_H
#define TOWERDEFENSE_GAME_NODE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "../Components/Component.h"

namespace TGEngine::core {

//forward
class Node;
class NodeManager;
class NodeManagerInstance;

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

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

#pragma endregion ComponentsHelper

class Node : public IComponent {
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
    for (auto &c : componentArray) {
      if (c->getActive()) c->update();
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
    c->setNode(this);
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

  void addChild(Node *node) {
    childs.emplace_back(node);
  }

  std::string &getId() { return id; }

  void setId(std::string newId){ id = newId; }

  Node* findNode(std::string findId) {
    if (getId() == findId) return this;
    for (auto c : childs) {
      if (c->getId() == findId) return c;
    }
    return nullptr;
  }

};

}


#endif// TOWERDEFENSE_GAME_NODE_H
