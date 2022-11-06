//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_CONSOLELOGGER_H
#define GAME_DEV_TEMPLATE_CONSOLELOGGER_H

#include "../interfaces/system/ILogger.h"
#include "fmt/core.h"
#include "fmt/color.h"
#include "fmt/ostream.h"
#include "fmt/chrono.h"
namespace dev
{

    class ConsoleLogger : public ILogger
    {
        public:
            ConsoleLogger() = default;
            explicit ConsoleLogger(LogLevel level) { m_logLevel = level; }
            void log(const std::string &msg, LogLevel level) override;

        private:
            std::string getText(const std::string &msg, bool useTime = true);
            std::string getTimeStr();

            constexpr static fmt::color color_trace{fmt::color::light_pink};
            constexpr static fmt::color color_debug{fmt::color::cornflower_blue};
            constexpr static fmt::color color_info{fmt::color::white};
            constexpr static fmt::color color_warning{fmt::color::yellow};
            constexpr static fmt::color color_error{fmt::color::red};
            constexpr static fmt::color color_critical{fmt::color::dark_red};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_CONSOLELOGGER_H
