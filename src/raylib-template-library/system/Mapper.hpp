//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_MAPPER_HPP
#define GAME_DEV_TEMPLATE_MAPPER_HPP

#include <map>
#include "../interfaces/system/IMapper.h"
#include "../enums/TextureName.h"
#include "../enums/ResourceName.h"

namespace ggj
{
    class Mapper : public IMapper
    {
        public:
            Mapper()
            {
                m_strToTex["characters.png"] = TextureName::Player;
                m_strToTex["sheet.png"] = TextureName::Tileset1;
                m_strToTex["tiles.png"] = TextureName::Tileset2;
                m_strToTex["boulder-small.png"] = TextureName::BoulderSmall;
                m_strToTex["andre.png"] = TextureName::Andre;
                m_strToTex["player-simple.png"] = TextureName::PlayerSimple;
                m_strToTex["magic-cliffs.png"] = TextureName::MagicCliffsTileset;

                m_texToRes[TextureName::Player] = ResourceName::GraphicsPlayer;
                m_texToRes[TextureName::Tileset1] = ResourceName::GraphicsTileset1;
                m_texToRes[TextureName::Tileset2] = ResourceName::GraphicsTileset2;
                m_texToRes[TextureName::BoulderSmall] = ResourceName::GraphicsBoulderSmall;
                m_texToRes[TextureName::Andre] = ResourceName::GraphicsAndre;
                m_texToRes[TextureName::PlayerSimple] = ResourceName::GraphicsPlayerSimple;
                m_texToRes[TextureName::MagicCliffsTileset] = ResourceName::GraphicsMagicCliffsTileset;
            };

            TextureName getTextureNameByString(const std::string &id) override
            {
                return (m_strToTex.count(id) > 0) ? m_strToTex[id] : TextureName::None;
            }

            ResourceName getResourceNameByTextureName(TextureName id) override
            {
                return (m_texToRes.count(id) > 0) ? m_texToRes[id] : ResourceName::None;
            }

            AnimationName getAnimationNameByPlayerState(PlayerState playerState)
            {
                switch (playerState)
                {
                    case PlayerState::Idle:
                        return AnimationName::PlayerIdle;
                    case PlayerState::Walk:
                        return AnimationName::PlayerWalk;
                    case PlayerState::Jump:
                        return AnimationName::PlayerJump;
                    case PlayerState::Fall:
                        return AnimationName::PlayerFall;
                    default:
                        return AnimationName::None;
                }
            }

        private:
            std::map<TextureName, ResourceName> m_texToRes;
            std::map<std::string, TextureName> m_strToTex;
    };
}
#endif //GAME_DEV_TEMPLATE_MAPPER_HPP
