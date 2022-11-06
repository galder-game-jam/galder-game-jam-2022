//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_ILOGGER_H
#define GAME_DEV_TEMPLATE_ILOGGER_H

#include <string>
#include "../../enums/LogLevel.h"

namespace ggj
{
    class ILogger
    {
        public:
            virtual ~ILogger() noexcept = default;
            /*! */
            void trace(const std::string &msg)       { if(canLog(LogLevel::Trace))       log(msg, LogLevel::Trace); };
            void debug(const std::string &msg)       { if(canLog(LogLevel::Debug))       log(msg, LogLevel::Debug); };
            void information(const std::string &msg) { if(canLog(LogLevel::Information)) log(msg, LogLevel::Information); };
            void warning(const std::string &msg)     { if(canLog(LogLevel::Warning))     log(msg, LogLevel::Warning); };
            void error(const std::string &msg)       { if(canLog(LogLevel::Error))       log(msg, LogLevel::Error); };
            void critical(const std::string &msg)    { if(canLog(LogLevel::Critical))    log(msg, LogLevel::Critical); };

            void setLevel(LogLevel level) { m_logLevel = level; }

            [[nodiscard]] LogLevel getLevel() const { return m_logLevel; }
            bool canLog(LogLevel level){ return m_logLevel != LogLevel::None && level >= m_logLevel; };
            virtual void log(const std::string &msg, LogLevel level) = 0;

        protected:
            LogLevel m_logLevel = LogLevel::None;
    };
}

#endif //GAME_DEV_TEMPLATE_ILOGGER_H
