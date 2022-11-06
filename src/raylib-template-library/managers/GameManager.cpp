//
// Created by robin on 26.10.22.
//

#include "GameManager.h"


bool dev::GameManager::initialize()
{
    if(!m_worlds.initialize())
    {
        m_logger.error("WorldManager initialization failed!");
        return false;
    }

    m_originalWindowSize = raylib::Vector2((float)m_window.GetWidth(), (float)m_window.GetHeight());
    m_renderTexture = raylib::RenderTexture((int)m_originalWindowSize.x, (int)m_originalWindowSize.y);

    return true;
}

void dev::GameManager::update(float timeDelta)
{
    m_lastTimeDelta = timeDelta;
    m_debugManager.clearText();
    m_worlds.update(timeDelta);
    m_debugManager.setText(0, "Debug: F1/F2/..=change map. W=jump, Space=rotate. Move = A/D");
    updateTestStuff();
}

void dev::GameManager::draw()
{
    m_renderTexture.BeginMode();
    //drawTestStuff();
    m_worlds.draw();
    m_renderTexture.EndMode();

    render();
}

/*!
 *  Makes anything drawn to the m_renderTexture get rendered on the screen and scaled with the screen size.
 */
void dev::GameManager::render()
{
    float scale = std::min((float)m_window.GetWidth()/m_originalWindowSize.x, (float)m_window.GetHeight()/m_originalWindowSize.y);
    BeginDrawing();
    m_window.ClearBackground(BLACK);
    DrawTexturePro(m_renderTexture.texture, (Rectangle){ 0.0f, 0.0f, (float)m_renderTexture.texture.width, (float)-m_renderTexture.texture.height },
                   (Rectangle){ ((float)m_window.GetWidth() - ((float)m_originalWindowSize.x*scale))*0.5f, ((float)m_window.GetHeight() - ((float)m_originalWindowSize.y*scale))*0.5f,
                                (float)m_originalWindowSize.x*scale, (float)m_originalWindowSize.y*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    m_debugManager.draw();
    EndDrawing();
}

void dev::GameManager::updateTestStuff()
{
    std::string keys = "Keys: ";
    bool first = true;
    for(int16_t key : m_input.getScanCodeOfKeysPressed())
    {
        keys += (first) ? fmt::format("{0}", key) : fmt::format(", {0}", key);

        first = false;
    }
    if(!first) //Only change text when something is returned
        m_testTextKeys.SetText(keys);

    m_testShouldDrawPinkRect = m_input.keysDown({dev::KeyboardKey::R, dev::KeyboardKey::B, dev::KeyboardKey::P});
}

void dev::GameManager::drawTestStuff()
{
    //DrawText("Congrats! You created your first window!", 10, 200, 16, LIGHTGRAY);
    m_testRect.Draw(raylib::Color::Blue());
    m_testText.Draw(10, 200);
    m_testTextKeys.Draw(10, 220);
    if(m_testShouldDrawPinkRect)
        m_testRectPink.Draw(raylib::Color::Pink());

    DrawText(fmt::format("Last update time delta: {0}", m_lastTimeDelta).c_str(), 10, 0, 16, RED);

}
