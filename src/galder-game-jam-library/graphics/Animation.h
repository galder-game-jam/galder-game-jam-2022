//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_ANIMATION_H
#define GAME_DEV_TEMPLATE_ANIMATION_H

#include "raylib-cpp.hpp"
#include "Frame.hpp"

namespace ggj
{

    class Animation
    {
        public:
            Animation() = default;
            explicit Animation(const raylib::Vector2 &size);
            Animation(const raylib::Vector2 &size, const std::vector<Frame> &frames);
            void addFrame(const Frame &frame);
            void addFrames(const std::vector<Frame> &frames);
            void update(float timeDelta);
            bool isValid()
            {
                return !m_frames.empty();
            }

            [[nodiscard]] const raylib::Rectangle &getDrawingRect() const;

        private:
            void updateDrawingRect();

            raylib::Rectangle m_drawingRect{};
            std::vector<Frame> m_frames{};
            int m_currentFrame{0};
            float m_frameTime{0.f};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_ANIMATION_H
