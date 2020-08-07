#include "Logger.h"

using namespace TGEngine::core;

void Logger::info(const std::string &message)
{
#ifdef DEBUG
  std::cout << "[INFO] " << message << std::endl;
#endif
  log.emplace_back(new Message(0, message));
}

void Logger::warning(const std::string &message)
{
#ifdef DEBUG
  std::cout << "[WARNING] " << message << std::endl;
#endif
  log.emplace_back(new Message(1, message));
}

void Logger::error(const std::string &message)
{
#ifdef DEBUG
  std::cout << "[ERROR] " << message << std::endl;
#endif
  log.emplace_back(new Message(2, message));
}

Logger* _loggerInstance = nullptr;

Logger &LoggerInstance::getInstance() {
  if (_loggerInstance == nullptr) {
    _loggerInstance = new Logger();
  }
  return *_loggerInstance;
}
