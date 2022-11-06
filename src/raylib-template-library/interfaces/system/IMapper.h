//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IMAPPER_H
#define GAME_DEV_TEMPLATE_IMAPPER_H

#include "../../enums/ResourceName.h"
#include "../../enums/TextureName.h"

namespace ggj
{
    class IMapper
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IMapper() = default;

            virtual TextureName getTextureNameByString(const std::string &id) = 0;

            virtual ResourceName getResourceNameByTextureName(TextureName id) = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IMAPPER_H
