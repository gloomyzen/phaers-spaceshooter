#include "Logger.h"
#include <map>
#include <string>

using namespace TGEngine::core;

const std::map<eLogTypes, std::string> mapPrefix = {
		{eLogTypes::INFO,    "[INFO] "},
		{eLogTypes::WARNING, "[WARNING] "},
		{eLogTypes::ERROR,   "[ERROR] "},
};

const size_t maxLogMessages = 32;

void Logger::info(const std::string &message) {
#ifdef DEBUG
#if defined(WIN32) or defined(EMSCRIPTEN)
	std::cout << getType(eLogTypes::INFO) << message << std::endl;
#else// WIN32
	std::cout << "\033[1;32m" + getType(eLogTypes::INFO) + "\033[0m" << "\033[0;32m" << message << "\033[0m"
			  << std::endl;
#endif// WIN32
#endif// DEBUG
	addLogMessage(new sLogMessage(eLogTypes::INFO, message));
}

void Logger::warning(const std::string &message) {
#ifdef DEBUG
#if defined(WIN32) or defined(EMSCRIPTEN)
	std::cout << getType(eLogTypes::WARNING) << message << std::endl;
#else// WIN32
	std::cout << "\033[1;33m" + getType(eLogTypes::WARNING) + "\033[0m" << "\033[0;33m" << message << "\033[0m"
			  << std::endl;
#endif// WIN32
#endif// DEBUG
	addLogMessage(new sLogMessage(eLogTypes::WARNING, message));
}

void Logger::error(const std::string &message) {
#ifdef DEBUG
#if defined(WIN32) or defined(EMSCRIPTEN)
	std::cout << getType(eLogTypes::ERROR) << message << std::endl;
#else// WIN32
	std::cout << "\033[1;31m" + getType(eLogTypes::ERROR) + "\033[0m" << "\033[0;31m" << message << "\033[0m"
			  << std::endl;
#endif// WIN32
#endif// DEBUG
	addLogMessage(new sLogMessage(eLogTypes::ERROR, message));
}

std::string Logger::getType(const eLogTypes &type) {
	if (mapPrefix.find(type) != mapPrefix.end()) {
		return mapPrefix.find(type)->second;
	}
	return std::string();
}

void Logger::addLogMessage(sLogMessage *message) {
	log.emplace_back(message);
	if (log.size() > maxLogMessages) {
		log.erase(log.begin());
	}
}

Logger *_loggerInstance = nullptr;

Logger &LoggerInstance::getInstance() {
	if (_loggerInstance == nullptr) {
		_loggerInstance = new Logger();
	}
	return *_loggerInstance;
}
