//
// Created by robin on 28.10.22.
//

#include "InputManager.h"
#include "../enums/KeyboardKey.h"

namespace ggj
{
    bool InputManager::keyPressed(ggj::KeyboardKey key)
    {
        return keyPressedCode((int16_t) key);
    }

    bool InputManager::keysPressed(const std::vector<ggj::KeyboardKey> &keys)
    {
        bool allPressed = true;
        if(keys.empty())
            allPressed = false;

        for(ggj::KeyboardKey key : keys)
        {
            if(!keyPressed(key))
                return false;
        }

        return allPressed;
    }

    bool InputManager::keyPressedCode(int16_t key)
    {
        return IsKeyPressed(key);
    }

    bool InputManager::keysPressedCode(const std::vector<int16_t> &keys)
    {
        bool allPressed = true;
        if(keys.empty())
            allPressed = false;

        for(int16_t key : keys)
        {
            if(!keyPressedCode(key))
                return false;
        }

        return allPressed;
    }

    bool InputManager::keyReleased(ggj::KeyboardKey key)
    {
        return keyReleasedCode((int16_t) key);
    }

    bool InputManager::keysReleased(const std::vector<ggj::KeyboardKey> &keys)
    {
        bool allReleased = true;
        if(keys.empty())
            allReleased = false;

        for(ggj::KeyboardKey key : keys)
        {
            if(!keyReleased(key))
                return false;
        }

        return allReleased;
    }

    bool InputManager::keyReleasedCode(int16_t key)
    {
        return IsKeyReleased(key);
    }

    bool InputManager::keysReleasedCode(const std::vector<int16_t> &keys)
    {
        bool allReleased = true;
        if(keys.empty())
            allReleased = false;

        for(int16_t key : keys)
        {
            if(!keyReleasedCode(key))
                return false;
        }

        return allReleased;
    }


    bool InputManager::keyDown(KeyboardKey key)
    {
        return keyDownCode((int16_t) key);
    }

    bool InputManager::keysDown(const std::vector<ggj::KeyboardKey> &keys)
    {
        bool allDown = true;
        if(keys.empty())
            allDown = false;

        for(ggj::KeyboardKey key : keys)
        {
            if(!keyDownCode((int16_t) key))
                return false;
        }

        return allDown;
    }

    bool InputManager::keyDownCode(int16_t key)
    {
        return IsKeyDown(key);
    }

    bool InputManager::keysDownCode(const std::vector<int16_t> &keys)
    {
        bool allDown = true;
        if(keys.empty())
            allDown = false;

        for(int16_t key : keys)
        {
            if(!keyDownCode(key))
                return false;
        }

        return allDown;
    }

    bool InputManager::keyUp(KeyboardKey key)
    {
        return keyUpCode((int16_t) key);
    }

    bool InputManager::keysUp(const std::vector<ggj::KeyboardKey> &keys)
    {
        bool allUp = true;
        if(keys.empty())
            allUp = false;

        for(ggj::KeyboardKey key : keys)
        {
            if(!keyUpCode((int16_t) key))
                return false;
        }

        return allUp;
    }

    bool InputManager::keyUpCode(int16_t key)
    {
        return IsKeyUp(key);
    }

    bool InputManager::keysUpCode(const std::vector<int16_t> &keys)
    {
        bool allUp = true;
        if(keys.empty())
            allUp = false;

        for(int16_t key : keys)
        {
            if(!keyUpCode(key))
                return false;
        }

        return allUp;
    }

    std::vector<int16_t> InputManager::getScanCodeOfKeysPressed()
    {
        std::vector<int16_t> keys;
        while (int16_t key = (int16_t)GetKeyPressed())
        {
            keys.push_back(key);
        }
        return keys;
    }

} // dev
