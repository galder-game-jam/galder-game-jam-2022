//
// Created by robin on 26.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IGAMEMANAGER_H
#define GAME_DEV_TEMPLATE_IGAMEMANAGER_H

namespace dev
{
    class IGameManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IGameManager() noexcept = default;
            virtual bool initialize() = 0;

            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IGAMEMANAGER_H
