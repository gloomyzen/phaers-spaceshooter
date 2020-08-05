#include "Node.h"

using namespace TGEngine::core;

void Node::loadProperty() {
  if (getId().empty()) {
    //TODO LOG_ERROR this!
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

  auto json = GET_JSON(pathNodes);
  if (json.HasParseError() || !json.IsObject()) {
    //TODO LOG_ERROR this!
    return;
  }
  if (!json["type"].IsString() || !json["name"].IsString()) {
    //TODO LOG_ERROR this!
    return;
  }

  if (json["childs"].IsArray()) {
    //TODO get childs
  }

  //TODO get "properties/"
  //1. составляем список нод из nodes и создаем пустые ноды
  //2. забираем все из properties и обновляет ноды через find

  auto propJson = GET_JSON(pathProperties);
  if (propJson.HasParseError() || !propJson.IsObject()) {
    return;
  }
  //TODO then run without log warnings

}
