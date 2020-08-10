#ifndef TOWERDEFENSE_GAME_NODEMANAGER_H
#define TOWERDEFENSE_GAME_NODEMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Node.h"

#define GET_NODE_MANAGER() TGEngine::core::NodeManagerInstance::getInstance()

namespace TGEngine::core {

    namespace nodeManager {

        class NodeManager {
        public:
            NodeManager() = default;

            ~NodeManager() = default;

            void addChild(Node *node) {
                nodes.emplace_back(node);
            }

            Node *findNode(std::string findId) {
                for (auto &n : nodes) {
                    auto res = n->findNode(findId);
                    if (res != nullptr) return res;
                }
                return nullptr;
            }

            std::vector<Node *> &getChilds() {
                return nodes;
            };

            void init() {
                //TODO Load Scenes with states
            }

            void update() {
                for (auto &n : nodes) n->update();
            }

            void render() {
                for (auto &n : nodes) n->render();
            }

        private:
            std::vector<Node*> nodes;
        };

    }//nodeManager

    class NodeManagerInstance {
    public:
        static nodeManager::NodeManager &getInstance();
    };

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_NODEMANAGER_H
