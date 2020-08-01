#ifndef TOWERDEFENSE_GAME_NODEMANAGERINSTANCE_H
#define TOWERDEFENSE_GAME_NODEMANAGERINSTANCE_H
#include "NodeManager.h"

#define GET_NODE_MANAGER() TGEngine::core::NodeManagerInstance::getInstance()

namespace TGEngine::core {

class NodeManagerInstance {
public:
  static NodeManager &getInstance();
};

}

#endif// TOWERDEFENSE_GAME_NODEMANAGERINSTANCE_H
