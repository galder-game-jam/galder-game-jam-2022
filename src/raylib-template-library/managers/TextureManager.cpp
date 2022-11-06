//
// Created by robin on 29.10.22.
//

#include "TextureManager.h"

namespace dev
{
    bool TextureManager::initialize()
    {
        loadTexture(TextureName::Tileset1);
        loadTexture(TextureName::Tileset2);

        return true;
    }

    bool TextureManager::loadTexture(TextureName id)
    {
        if (m_textures.count(id) > 0)
        {
            m_logger.debug(fmt::format("Texture with ID '{0}' already loaded", (int32_t) id));
            return true;
        }

        ResourceName res = m_mapper.getResourceNameByTextureName(id);
        if (res == ResourceName::None)
        {
            m_logger.error(
                    fmt::format("Error when attempting to load texture with id '{0}'! Texture could not be mapped to resource. ", (int32_t) id));
            return false;
        }

        std::string path = m_resources.getResource(res);
        std::unique_ptr<raylib::Texture> tex = std::make_unique<raylib::Texture>(path);
        if (!tex->IsReady())
        {
            m_logger.error(fmt::format("Error when attempting to load texture with id '{0}'. Path: '{1}'", (int32_t) id, path.c_str()));
            return false;
        }

        m_textures[id] = std::move(tex);

        return true;
    }

    raylib::Texture *TextureManager::get(const TextureName &id)
    {
        return (m_textures.count(id) > 0) ? m_textures[id].get() :
               loadTexture(id) ? m_textures[id].get() : nullptr;
    }
}