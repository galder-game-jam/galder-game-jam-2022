//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_ITIMER_H
#define GAME_DEV_TEMPLATE_ITIMER_H

#include <cstdint>

namespace ggj
{

    class ITimer
    {
        public:
            virtual ~ITimer() noexcept = default;
            /*! Elapsed time as microseconds */
            virtual int64_t elapsed() = 0;
            virtual float secondsElapsed() = 0;
            virtual void restart() = 0;

            virtual void setStartPoint() = 0;
            virtual int64_t timeSinceStart() = 0;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_ITIMER_H
