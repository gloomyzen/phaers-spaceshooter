#ifndef TOWERDEFENSE_GAME_NODEMANAGER_H
#define TOWERDEFENSE_GAME_NODEMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Node.h"

#define GET_NODE_MANAGER() TGEngine::core::NodeManagerInstance::getInstance()
#define GET_NODE() TGEngine::core::NodeManagerInstance::getInstance().getRoot()

namespace TGEngine::core {

    class NodeManagerInstance {
    public:
        static NodeManagerInstance &getInstance();
        unsigned int getNextUid() {
            return nextUid++;
        }
        Node* getRoot() { return rootNode; }
    private:
        unsigned int nextUid = 0u;
        Node* rootNode = nullptr;
    };

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_NODEMANAGER_H
