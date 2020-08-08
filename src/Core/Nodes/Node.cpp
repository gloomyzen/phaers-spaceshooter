#include "Node.h"
#include "../Components/AllComponentsHeaders.h"
#include "../Nodes/NodeFactory.h"

using namespace TGEngine::core;

void Node::loadProperty(const std::string &prefix) {
    if (getId().empty()) {
        LOG_ERROR("Node::loadProperty Node has no identifier!");
        return;
    }

    std::string pathNodes = "nodes/";
    std::string pathProperties = "properties/";
    if (!getModuleId().empty()) {
        pathNodes += getModuleId() + "/" + getId();
        pathProperties += getModuleId() + "/" + getId();
    } else {
        pathNodes += getId();
        pathProperties += getId();
    }

    auto json = GET_JSON_PREF(pathNodes, prefix);
    if (json.HasParseError() || !json.IsObject()) {
        LOG_ERROR("Node::loadProperty Json file '" + pathNodes + "' is not valid!");
        return;
    }
    if (!json.HasMember("type") || !json.HasMember("name") || !json["type"].IsString() || !json["name"].IsString()) {
        LOG_ERROR("Node::loadProperty Json file '" + pathNodes + "' not has 'type' and 'name'!");
        return;
    }

    if (json["name"].GetString() != getId()) {
        LOG_ERROR("Node::loadProperty Node id: '" + static_cast<std::string>(json["name"].GetString()) + "' and getId() '" + getId() + "' is not match!");
        return;
    }

    if (json.HasMember("childs") && json["childs"].IsArray()) {
        parseData(this, json["childs"].GetArray());
    }

    parseProperty(this, pathProperties, prefix);
}

void Node::parseData(Node *node, const rapidjson::GenericValue<rapidjson::UTF8<char>>::Array &array) {
    for (auto &item : array) {
        if (item["type"].IsString() && item["name"].IsString()) {
            auto childNode = new Node(item["name"].GetString());
            if (item.HasMember("childs") && item["childs"].IsArray()) {
                parseData(childNode, item["childs"].GetArray());
            }
            node->addChild(childNode);
        }
    }
}

void Node::parseProperty(Node *node, const std::string &pathProperties, const std::string &prefix) {
    // TODO
    //  1. составляем список нод из nodes и создаем пустые ноды
    //  2. забираем все из properties и обновляет ноды через find
    // TODO then run without log warnings

    auto propJson = GET_JSON_PREF(pathProperties, prefix);

    if (propJson.HasParseError() || !propJson.IsObject()) { return; }

    for (auto &propList : propJson.GetObject()) {
        auto nodeName = propList.name.GetString();

        if (!propJson[nodeName].IsObject()) {
            continue;
        }
        auto *targetNode = node->findNode(nodeName);
        for (auto &item : propJson[nodeName].GetObject()) {
            std::string componentName = item.name.GetString();
            if (item.value.IsObject()) {
                NodeFactory::getComponents(targetNode, componentName, item.value.GetObject());
            }
        }

    }

}
