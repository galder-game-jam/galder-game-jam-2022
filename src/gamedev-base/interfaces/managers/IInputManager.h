//
// Created by robin on 28.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IINPUTMANAGER_H
#define GAME_DEV_TEMPLATE_IINPUTMANAGER_H

#include <vector>
#include <cstdint>

namespace ggj
{
    template <class T>
    class IInputManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IInputManager() noexcept = default;

            virtual bool keyPressed(T key) = 0;
            virtual bool keysPressed(const std::vector<T> &keys) = 0;
            virtual bool keyPressedCode(int16_t key) = 0;
            virtual bool keysPressedCode(const std::vector<int16_t> &keys) = 0;

            virtual bool keyReleased(T key) = 0;
            virtual bool keysReleased(const std::vector<T> &keys) = 0;
            virtual bool keyReleasedCode(int16_t key) = 0;
            virtual bool keysReleasedCode(const std::vector<int16_t> &keys) = 0;

            virtual bool keyDown(T key) = 0;
            virtual bool keysDown(const std::vector<T> &keys) = 0;
            virtual bool keyDownCode(int16_t key) = 0;
            virtual bool keysDownCode(const std::vector<int16_t> &keys) = 0;

            virtual bool keyUp(T key) = 0;
            virtual bool keysUp(const std::vector<T> &keys) = 0;
            virtual bool keyUpCode(int16_t key) = 0;
            virtual bool keysUpCode(const std::vector<int16_t> &keys) = 0;

            virtual std::vector<int16_t> getScanCodeOfKeysPressed() = 0;

    };
}

#endif //GAME_DEV_TEMPLATE_IINPUTMANAGER_H
