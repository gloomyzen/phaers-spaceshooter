#include "NodeManagerInstance.h"

using namespace TGEngine::core;

NodeManager *currentNodeManager = nullptr;

NodeManager & NodeManagerInstance::getInstance() {
  if (currentNodeManager == nullptr) {
    currentNodeManager = new NodeManager();
  }
  return *currentNodeManager;
}