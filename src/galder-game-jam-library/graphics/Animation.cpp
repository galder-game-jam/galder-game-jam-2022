//
// Created by soberga on 12.11.22.
//

#include "Animation.h"

namespace ggj
{

    Animation::Animation(const raylib::Vector2 &size) :  m_drawingRect{0.f, 0.f, size.x, size.y}
    {
    }

    Animation::Animation(const raylib::Vector2 &size, const std::vector<Frame> &frames) : Animation(size)
    {
        m_frames = frames;
        if(!m_frames.empty())
            updateDrawingRect();
    }

    void Animation::addFrame(const Frame &frame)
    {
        m_frames.emplace_back(frame);

        if(m_frames.size() == 1)
        {
            updateDrawingRect();
        }
    }

    void Animation::updateDrawingRect()
    {
        m_drawingRect.x = m_frames[m_currentFrame].position.x;
        m_drawingRect.y = m_frames[m_currentFrame].position.y;
    }

    void Animation::addFrames(const std::vector<Frame> &frames)
    {
        for(const Frame &frame: frames)
        {
            addFrame(frame);
        }
    }

    void Animation::update(float timeDelta)
    {
        m_frameTime += timeDelta * 1000;

        if(m_frameTime > m_frames[m_currentFrame].time)
        {
            m_frameTime -= m_frames[m_currentFrame].time;
            ++m_currentFrame;
            if(m_currentFrame > m_frames.size() - 1)
                m_currentFrame = 0;

            updateDrawingRect();
        }
    }

    const raylib::Rectangle &Animation::getDrawingRect() const
    {
        return m_drawingRect;
    }
} // ggj