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

	class JsonLoader {
	public:
		JsonLoader();

		~JsonLoader();

		/**
		 * Method for load unparsed json, as is, with is object check
		 * @param path Path to json in resources folder
		 * @param prefix @only for gtest
		 * @return rapidjson::Document
		 */
		rapidjson::Document loadJson(const std::string &path, const std::string &prefix = "");
	};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_JSONLOADER_H
