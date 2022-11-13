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

namespace ggj
{
    class TextureManager : public ggj::ITextureManager<TextureName, raylib::Texture>
    {
        public:
            TextureManager(ggj::ILogger &logger, IMapper &mapper, ggj::IResourceManager<ResourceName> &resources)
                    : m_logger{logger}, m_mapper{mapper}, m_resources{resources}
            {

            }

            bool initialize() override;

            raylib::Texture *get(const TextureName &id) override;

        private:
            bool loadTexture(TextureName id);

            ggj::ILogger &m_logger;
            IMapper &m_mapper;
            ggj::IResourceManager<ResourceName> &m_resources;

            std::map<TextureName, std::unique_ptr<raylib::Texture>> m_textures;
    };
}

#endif //GAME_DEV_TEMPLATE_TEXTUREMANAGER_H
