#ifndef TOWERDEFENSE_GAME_NODE_H
#define TOWERDEFENSE_GAME_NODE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Core/Components/Component.h"
#include "Core/ResourceModule/Loaders/JsonLoader.h"
#include "Core/Debug/Logger.h"

namespace TGEngine::core {

//forward
    class Node;
    class NodeManager;
    class NodeManagerInstance;

#pragma region ComponentsHelper
    using ComponentID = std::size_t;
    using Group = std::size_t;

    inline ComponentID getNewComponentTypeID() {
        static ComponentID lastID = 0u;
        return lastID++;
    }

    template<typename T>
    inline ComponentID getComponentTypeID() noexcept {
        static_assert(std::is_base_of<Component, T>::value, "");
        static ComponentID typeID = getNewComponentTypeID();
        return typeID;
    }

    constexpr std::size_t maxComponents = 6;

    using ComponentBitSet = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component *, maxComponents>;

#pragma endregion ComponentsHelper

    class Node : public IComponent {
    private:
        std::vector<std::unique_ptr<Component>> components;
        ComponentArray componentArray{};
        ComponentBitSet componentBitSet;
        std::vector<Node *> childs{};
        std::vector<Node *> childsList{};
        std::string id{};
        unsigned int uid;
    public:

        Node() {
            setNextUid();
        }

        Node(std::string nodeId) {
            if (nodeId.empty()) {
                throw std::runtime_error("The current node has no id set!");
            }
            id = nodeId;
            setNextUid();
        }

        ~Node() {
            for (auto &c : childs) {
                delete c;
            }
        }

        void init() override {}

        void update() override {
            for (auto &c : componentArray) {
                if (c != nullptr && c->getActive()) {
                    c->update();
                }
            }
            for (auto &c : childs) {
                if (c->getActive()) {
                    c->update();
                }
            }
        }

        void render() override {
            for (auto &c : components) {
                if (c != nullptr && c->isActive()) {
                    c->render();
                }
            }
            for (auto &c : childs) {
                if (c->getActive()) {
                    c->render();
                }
            }
        }

        void setNextUid();

        unsigned int getUid() { return uid; }

        template<typename T>
        [[nodiscard]] bool hasComponent() const { return componentBitSet[getComponentTypeID<T>()]; }

        template<typename T, typename... TArgs>
        T &addComponent(TArgs &&... mArgs) {
            T *c(new T(std::forward<TArgs>(mArgs)...));
            c->setNode(this);
            std::unique_ptr<Component> uPtr{c};
            components.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            c->init();
            return *c;
        }

        template<typename T>
        T &getComponent() const {
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T *>(ptr);
        }

        std::vector<Node *> &getChilds() {
            return childs;
        };

        std::vector<Node *> &getChildsList() {
            return childsList;
        };

        void addChild(Node *node) {
            if (node->getId().empty()) {
                LOG_ERROR("Node::addChild Child node has no identifier!");
                return;
            }
//            std::for_each(this->childsList.begin(), this->childsList.end(), [&node](Node* n) {
//                node->childsList.emplace_back(n);
//            });
//            for(auto c : childsList) {
//                node->childsList.emplace_back(c);
//            }
//            std::for_each(node->childsList.begin(), node->childsList.end(), [&](Node* n) {
//                childsList.emplace_back(n);
//            });
//            for(auto c : node->childsList) {
//                childsList.emplace_back(c);
//            }
            node->childsList.emplace_back(this);
            childs.emplace_back(node);
            //node
            //*** node <- current
            //*** *** node
        }

        bool hasChilds() {
            return !childs.empty();
        }

        std::string &getId() { return id; }

        void setId(std::string newId) { id = newId; }

        /***
         * Поиск ноды потомка по id
         * @param findId id искомого объекта
         * @return Node*
         */
        Node *findNode(const std::string &findId) {
            if (getId() == findId) return this;
            for (auto c : childs) {
                if (c->getId() == findId) return c;
                if (c->hasChilds()) {
                    auto find = c->findNode(findId);
                    if (find != nullptr) {
                        return find;
                    }
                }
            }
            return nullptr;
        }

        bool hasNode(const std::string &findId) {
            if (getId() == findId) return true;
            bool currentLevel = false;
            for (auto c : childs) {
                currentLevel = c->hasNode(findId);
                if (currentLevel) return true;
            }
            return false;
        }

        /***
         * Парсинг параметров из json файла
         * @param module Module name
         * @param prefix @only for GTests
         */
        void loadProperty(const std::string &module = "", const std::string &prefix = "");

    protected:
        void parseData(Node *node, const rapidjson::GenericValue<rapidjson::UTF8<char>>::Array &array);

        void parseProperty(Node *node, const std::string &string, const std::string &prefix = "");

    };

}


#endif// TOWERDEFENSE_GAME_NODE_H
