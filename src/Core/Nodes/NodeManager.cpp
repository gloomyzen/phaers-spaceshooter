#include "NodeManager.h"

using namespace TGEngine::core;

nodeManager::NodeManager *currentNodeManager = nullptr;

nodeManager::NodeManager & NodeManagerInstance::getInstance() {
  if (currentNodeManager == nullptr) {
    currentNodeManager = new nodeManager::NodeManager();
  }
  return *currentNodeManager;
}