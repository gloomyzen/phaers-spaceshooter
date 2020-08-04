#ifndef TOWERDEFENSE_GAME_JSONLOADER_H
#define TOWERDEFENSE_GAME_JSONLOADER_H
#include <fstream>
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <string>

namespace TGEngine::core {

class JsonLoader
{
public:
  /**
   * Method for load unparsed json, as is, with is object check
   * @param path Path to json in resources folder
   * @param prefix @only for gtest
   * @return rapidjson::Document
   */
  static rapidjson::Document loadJson(const std::string &path, const std::string &prefix = "")
  {
    std::ifstream ifs(prefix + path, std::ifstream::in);
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
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_JSONLOADER_H
