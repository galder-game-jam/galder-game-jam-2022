//
// Created by robin on 30.10.22.
//

#ifndef GAME_DEV_TEMPLATE_WORLDLAYER_H
#define GAME_DEV_TEMPLATE_WORLDLAYER_H

#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"

namespace dev
{
    class WorldLayer
    {
        public:

            WorldLayer() = default;
            WorldLayer(int32_t layerNumber, bool disableUpdate) : m_layer {layerNumber}, m_disableUpdate {disableUpdate}
            {

            }

            template <typename T, typename... Args>
            T * createGameObject(Args &&... args);

            void update(float timeDelta);
            void draw();

            [[nodiscard]] int32_t getLayer() const;

            void setLayer(int32_t layer);

        private:
            int32_t m_layer {};
            bool m_disableUpdate {};
            std::vector<std::unique_ptr<dev::IGameObject<raylib::Vector2>>> m_gameObjects;
    };

    template<typename T, typename... Args>
    T *WorldLayer::createGameObject(Args &&... args)
    {
        //size_t id = getNextDynamicId();
        size_t index = m_gameObjects.size();
        m_gameObjects.emplace_back(std::make_unique<T>(args...));

        m_gameObjects[index]->setLayer(m_layer);
        T* obj = static_cast<T*>(m_gameObjects[index].get());

        return obj;
    }

} // dev

#endif //GAME_DEV_TEMPLATE_WORLDLAYER_H
