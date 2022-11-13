//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IWORLD_H
#define GAME_DEV_TEMPLATE_IWORLD_H

namespace ggj
{

    template <class T>
    class IWorld
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IWorld() = default;
            virtual bool initialize() = 0;
            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;

            bool isLevelCleared() const { return m_isLevelCleared; }
            void setLevelCleared(bool isLevelCleared) { m_isLevelCleared = isLevelCleared; }

        private:
            bool m_isLevelCleared {false};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_IWORLD_H
