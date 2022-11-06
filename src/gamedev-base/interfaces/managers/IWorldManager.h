//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IWORLDMANAGER_H
#define GAME_DEV_TEMPLATE_IWORLDMANAGER_H

namespace ggj
{
    //template <class T>
    class IWorldManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IWorldManager() noexcept = default;
            virtual bool initialize() = 0;
            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IWORLDMANAGER_H
