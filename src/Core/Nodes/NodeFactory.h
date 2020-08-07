#ifndef TOWERDEFENSE_GAME_NODEFACTORY_H
#define TOWERDEFENSE_GAME_NODEFACTORY_H

#include "Node.h"
#include "../Components/AllComponentsHeaders.h"
#include <string>
#include <map>

namespace TGEngine::core {

enum eNodeFactory : size_t {
  TRANSFORM_COMPONENT,
  SPRITE_COMPONENT,
  ANIMSPRITE_COMPONENT,
};

class NodeFactory
{
public:
  static void getComponents(Node *node, const std::string &componentName);
  static bool hasRegisteredComponent(const std::string &componentName);
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_NODEFACTORY_H
