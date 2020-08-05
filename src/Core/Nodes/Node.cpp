#include "Node.h"

using namespace TGEngine::core;

void Node::loadProperty() {
  if (getId().empty()) {
    //TODO LOG_ERROR this!
    return;
  }

  std::string path = "nodes/";
  if (!getModuleId().empty()) {
    path += getModuleId() + "/" + getId();
  } else {
    path += getId();
  }

  auto json = GET_JSON(path);
  if (json.HasParseError() || !json.IsObject()) {
    //TODO LOG_ERROR this!
    return;
  }
  if (!json["type"].IsString() || !json["name"].IsString()) {
    //TODO LOG_ERROR this!
    return;
  }
  //TODO get "properties/"

  if (json["childs"].IsArray()) {
    //TODO get childs
  }

}
