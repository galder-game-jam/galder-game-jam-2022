//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_TIMER_H
#define GAME_DEV_TEMPLATE_TIMER_H

#include <cstdint>
#include <chrono>
#include "../interfaces/system/ITimer.h"

namespace ggj
{
    class Timer : public ITimer
    {
        public:
            Timer();

            int64_t elapsed() override;
            float secondsElapsed() override;
            void restart() override;
            void setStartPoint() override;
            int64_t timeSinceStart() override;

        private:
            std::chrono::time_point<std::chrono::steady_clock> m_start;
            int64_t m_startPoint {0};
    };
} // dev

#endif //GAME_DEV_TEMPLATE_TIMER_H
