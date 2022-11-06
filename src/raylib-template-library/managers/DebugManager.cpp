//
// Created by robin on 05.11.22.
//

#include "DebugManager.h"

namespace ggj
{
    void DebugManager::setText(uint16_t line, const std::string &text, const Colori &color)
    {
        m_debugTexts[line] = {text, color};
    }

    bool DebugManager::initialize()
    {
        return true;
    }

    void DebugManager::update(float timeDelta)
    {

    }

    void DebugManager::draw()
    {
        raylib::Vector2 textPos {4, 4};

        for(auto & debugText : m_debugTexts)
        {
            std::string text = debugText.second.first;
            ggj::Colori c = debugText.second.second;
            raylib::Color color = {c.r, c.g, c.b, c.a};

            DrawText(text.c_str(), (int)textPos.x, (int)textPos.y, m_fontSize, color);
            textPos = raylib::Vector2(textPos.x, textPos.y + (float)m_fontSize + 4.f);
        }
    }

    void DebugManager::clearText()
    {
        m_debugTexts.clear();
    }
} // dev