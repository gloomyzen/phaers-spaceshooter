#include "JsonLoader.h"

using namespace TGEngine::core;

const std::string propFolder = "resources/data/";

JsonLoader::JsonLoader() {}
JsonLoader::~JsonLoader() {}

rapidjson::Document JsonLoader::loadJson(const std::string &path, const std::string &prefix) {
    const std::string pref = prefix + propFolder;
    std::ifstream ifs(pref + path + ".json", std::ifstream::in);
    if (!ifs.is_open()) {
        return nullptr;
    }
    rapidjson::IStreamWrapper isw{ifs};
    rapidjson::Document document{};
    document.ParseStream(isw);
    if (!document.HasParseError() && document.IsObject()) {
        return document;
    } else {
        return nullptr;
    }
}
