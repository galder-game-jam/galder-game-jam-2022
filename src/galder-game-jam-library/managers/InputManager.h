//
// Created by robin on 28.10.22.
//

#ifndef GAME_DEV_TEMPLATE_INPUTMANAGER_H
#define GAME_DEV_TEMPLATE_INPUTMANAGER_H

#include "../enums/KeyboardKey.h"
#include "../../gamedev-base/GameDevBase.h"
#include "raylib-cpp.hpp"


namespace ggj
{
    class InputManager : public IInputManager<ggj::KeyboardKey>
    {
        public:
            InputManager() = default;

            bool keyPressed(KeyboardKey key) override;
            bool keysPressed(const std::vector<ggj::KeyboardKey> &keys) override;
            bool keyPressedCode(int16_t key) override;
            bool keysPressedCode(const std::vector<int16_t> &keys) override;

            bool keyReleased(KeyboardKey key) override;
            bool keysReleased(const std::vector<ggj::KeyboardKey> &keys) override;
            bool keyReleasedCode(int16_t key) override;
            bool keysReleasedCode(const std::vector<int16_t> &keys) override;

            bool keyDown(KeyboardKey key) override;
            bool keysDown(const std::vector<ggj::KeyboardKey> &keys) override;
            bool keyDownCode(int16_t key) override;
            bool keysDownCode(const std::vector<int16_t> &keys) override;

            bool keyUp(KeyboardKey key) override;
            bool keysUp(const std::vector<ggj::KeyboardKey> &keys) override;
            bool keyUpCode(int16_t key) override;
            bool keysUpCode(const std::vector<int16_t> &keys) override;

            std::vector<int16_t> getScanCodeOfKeysPressed() override;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_INPUTMANAGER_H
