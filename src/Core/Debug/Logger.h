#ifndef TOWERDEFENSE_GAME_LOGGER_H
#define TOWERDEFENSE_GAME_LOGGER_H

#include <string>
#include <iostream>
#include <vector>

#pragma region
#define GET_LOGGER() TGEngine::core::LoggerInstance::getInstance()
#define LOG_INFO(W) TGEngine::core::LoggerInstance::getInstance().info(W)
#define LOG_WARNING(W) TGEngine::core::LoggerInstance::getInstance().warning(W);
#define LOG_ERROR(W) TGEngine::core::LoggerInstance::getInstance().error(W);


namespace TGEngine::core {

struct Message
{
  int type; // 0 info 1 warning 2 error
  std::string message;
  Message(int _type, std::string _message)
  {
    type = _type;
    message = _message;
  }
};

/***
 * Данный класс нужен для логирования исключительных событий
 */
class Logger
{
public:
  void info(const std::string &message);
  void warning(const std::string &message);
  void error(const std::string &message);

private:
  std::vector<Message *> log;
};

class LoggerInstance {
public:
  static Logger &getInstance();
};

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_LOGGER_H