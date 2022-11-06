//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_LOGLEVEL_H
#define GAME_DEV_TEMPLATE_LOGLEVEL_H

#include <cstdint>

namespace dev
{
    enum class LogLevel : uint8_t
    {
        None = 0,
        Trace = 1,
        Debug = 2,
        Information = 3,
        Warning = 4,
        Error = 5,
        Critical = 6
    };
}

#endif //GAME_DEV_TEMPLATE_LOGLEVEL_H
