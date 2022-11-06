//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_ITEXTUREMANAGER_H
#define GAME_DEV_TEMPLATE_ITEXTUREMANAGER_H

namespace ggj
{
    template <class TId, class TTexture>
    class ITextureManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~ITextureManager() noexcept = default;

            virtual bool initialize() = 0;
            virtual TTexture* get(const TId &id) = 0;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_ITEXTUREMANAGER_H
