#ifndef TOWERDEFENSE_GAME_LOGGER_H
#define TOWERDEFENSE_GAME_LOGGER_H

#include <string>
#include <iostream>
#include <vector>

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

class Logger
{
public:
  static void info(const std::string &message)
  {
#ifdef DEBUG
    std::cout << message << std::endl;
    log.emplace_back(message);
#endif
    log.emplace_back(new Message(0, message));
  };

  static void warning(const std::string &message)
  {
#ifdef DEBUG
    std::cout << message << std::endl;
    log.emplace_back(new Message(1, message));
#endif
  };

  static void error(const std::string &message)
  {
#ifdef DEBUG
    std::cout << message << std::endl;
    log.emplace_back(new Message(2, message));
#endif
  };

private:
  static std::vector<Message *> log;
};


#endif// TOWERDEFENSE_GAME_LOGGER_H