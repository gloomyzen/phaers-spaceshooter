#include "Logger.h"

using namespace TGEngine::core;

void Logger::info(const std::string &message) {
#ifdef DEBUG
    std::cout << "\033[1;32m[INFO]\033[0m " << "\033[0;32m" << message << "\033[0m" << std::endl;
#endif
    log.emplace_back(new sLogMessage(eLogTypes::INFO, message));
}

void Logger::warning(const std::string &message) {
#ifdef DEBUG
    std::cout << "\033[1;33m[WARNING]\033[0m " << "\033[0;33m" << message << "\033[0m" << std::endl;
#endif
    log.emplace_back(new sLogMessage(eLogTypes::WARNING, message));
}

void Logger::error(const std::string &message) {
#ifdef DEBUG
    std::cout << "\033[1;31m[ERROR]\033[0m " << "\033[0;31m" << message << "\033[0m" << std::endl;
#endif
    log.emplace_back(new sLogMessage(eLogTypes::ERROR, message));
}

Logger *_loggerInstance = nullptr;

Logger &LoggerInstance::getInstance() {
    if (_loggerInstance == nullptr) {
        _loggerInstance = new Logger();
    }
    return *_loggerInstance;
}
