//
// Created by robin on 29.10.22.
//

#include <cstdint>
#include "Timer.h"

namespace dev
{
    Timer::Timer()
    {
        m_start = std::chrono::steady_clock::now();

    }
    int64_t Timer::elapsed()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::microseconds microsec = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start);
        return microsec.count();
    }

    void Timer::restart()
    {
        m_start = std::chrono::steady_clock::now();
    }

    float Timer::secondsElapsed()
    {
        return (float)((double)elapsed() / 1000000);
    }

    void Timer::setStartPoint()
    {
        m_startPoint = elapsed();
    }

    int64_t Timer::timeSinceStart()
    {
        return elapsed() - m_startPoint;
    }

} // dev