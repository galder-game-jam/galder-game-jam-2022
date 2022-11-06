//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_TEXTUREMANAGER_H
#define GAME_DEV_TEMPLATE_TEXTUREMANAGER_H

#include <map>
#include <cstdint>
#include "../../gamedev-base/GameDevBase.h"
#include "raylib-cpp.hpp"
#include "../enums/TextureName.h"
#include "../interfaces/system/IMapper.h"

namespace dev
{
    class TextureManager : public dev::ITextureManager<TextureName, raylib::Texture>
    {
        public:
            TextureManager(dev::ILogger &logger, IMapper &mapper, dev::IResourceManager<ResourceName> &resources)
                    : m_logger{logger}, m_mapper{mapper}, m_resources{resources}
            {

            }

            bool initialize() override;

            raylib::Texture *get(const TextureName &id) override;

        private:
            bool loadTexture(TextureName id);

            dev::ILogger &m_logger;
            IMapper &m_mapper;
            dev::IResourceManager<ResourceName> &m_resources;

            std::map<TextureName, std::unique_ptr<raylib::Texture>> m_textures;
    };
}

#endif //GAME_DEV_TEMPLATE_TEXTUREMANAGER_H
