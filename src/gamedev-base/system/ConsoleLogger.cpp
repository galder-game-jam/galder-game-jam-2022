//
// Created by robin on 27.10.22.
//

#include "ConsoleLogger.h"

namespace ggj
{
    void ConsoleLogger::log(const std::string &msg, LogLevel level)
    {
        if(canLog(level))
        {
            std::string text = getText(msg, false);
            switch (level)
            {

                case LogLevel::None:
                    break;
                case LogLevel::Trace:
                    fmt::print(fg(color_trace), text);
                    break;
                case LogLevel::Debug:
                    #ifdef GAME_DEV_DEBUG
                    fmt::print(fg(color_debug), text);
                    #endif
                    break;
                case LogLevel::Information:
                    fmt::print(fg(color_info), text);
                    break;
                case LogLevel::Warning:
                    fmt::print(fg(color_warning), text);
                    break;
                case LogLevel::Error:
                    fmt::print(fg(color_error), text);
                    break;
                case LogLevel::Critical:
                    fmt::print(bg(color_critical) | fg(fmt::color::black), text);
                    break;
            }
        }
    }

    std::string ConsoleLogger::getTimeStr()
    {
        return fmt::format("{:%Y-%m-%d %H:%M:%S} ", std::chrono::system_clock::now());
    }

    std::string ConsoleLogger::getText(const std::string &msg, bool useTime)
    {
        std::string timeStr = (useTime) ? getTimeStr() : "";
        return fmt::format("{0}{1}\n", timeStr, msg);
    }


} // dev