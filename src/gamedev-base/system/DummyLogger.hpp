//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_DUMMYLOGGER_HPP
#define GAME_DEV_TEMPLATE_DUMMYLOGGER_HPP

#include "../../gamedev-base/GameDevBase.h"

namespace dev
{
    /*!
     * Use when you want to disable logging
     */
    class DummyLogger : public ILogger
    {
        public:
            DummyLogger() = default;

            void log(const std::string &msg, LogLevel level) override {  }
    };

} // dev

#endif //GAME_DEV_TEMPLATE_DUMMYLOGGER_HPP
