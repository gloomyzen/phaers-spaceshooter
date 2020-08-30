#ifndef TOWERDEFENSE_GAME_LOGGER_H
#define TOWERDEFENSE_GAME_LOGGER_H

#include <string>
#include <iostream>
#include <vector>
#include <string>

#define GET_LOGGER() TGEngine::core::LoggerInstance::getInstance()
#define LOG_INFO(W) GET_LOGGER().info(W)
#define LOG_WARNING(W) GET_LOGGER().warning(W)
#define LOG_ERROR(W) GET_LOGGER().error(W)

namespace TGEngine::core {

    enum eLogTypes : size_t {
        INFO, WARNING, ERROR
    };

    struct sLogMessage {
        eLogTypes type;
        std::string message;

        sLogMessage(eLogTypes _type, std::string _message) {
            type = _type;
            message = _message;
        }
    };

/***
 * Данный класс нужен для логирования исключительных событий
 */
    class Logger {
    public:
        void info(const std::string &message);

        void warning(const std::string &message);

        void error(const std::string &message);

    private:
        /**
         * Получение префикса типа события
         * @return std::string
         */
        std::string getType(const eLogTypes&);

        void addLogMessage(sLogMessage *);

        std::vector<sLogMessage *> log{};
    };

    class LoggerInstance {
    public:
        static Logger &getInstance();
    };

}//TGEngine::core

#endif// TOWERDEFENSE_GAME_LOGGER_H