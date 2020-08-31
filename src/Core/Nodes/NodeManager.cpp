#include "NodeManager.h"

using namespace TGEngine::core;

NodeManagerInstance *currentNodeManager = nullptr;

NodeManagerInstance &NodeManagerInstance::getInstance() {
	if (currentNodeManager == nullptr) {
		currentNodeManager = new NodeManagerInstance();
		currentNodeManager->rootNode = new Node("root");
	}
	return *currentNodeManager;
}