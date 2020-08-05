#include "JsonLoader.h"

using namespace TGEngine::core;

JsonLoader *currentLoader = nullptr;

const std::string propFolder = "resources/data/";

JsonLoader &JsonLoader::getInstance()
{
  if (currentLoader != nullptr) { return *currentLoader; }
  throw std::runtime_error("There is no current JsonLoader");
}
JsonLoader::JsonLoader() {
  currentLoader = this;
}
JsonLoader::~JsonLoader() {}

rapidjson::Document JsonLoader::loadJson(const std::string &path, const std::string &prefix)
{
  const std::string pref = prefix + propFolder;
  std::ifstream ifs(pref + path, std::ifstream::in);
  if (!ifs.is_open()) {
    return nullptr;
  }
  rapidjson::IStreamWrapper isw { ifs };
  rapidjson::Document document {};
  document.ParseStream( isw );
  if (!document.HasParseError() && document.IsObject()) {
    return document;
  } else {
    return nullptr;
  }
}
