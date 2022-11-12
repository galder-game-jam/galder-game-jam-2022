//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_OBJECTGENERATORDATA_HPP
#define GAME_DEV_TEMPLATE_OBJECTGENERATORDATA_HPP

#include <string>
#include "raylib-cpp.hpp"
#include "UserData.hpp"
#include "tileson.hpp"

namespace ggj
{

    struct ObjectGeneratorData
    {
        bool isStatic{};
        bool isTrigger{};
        bool isPlayer{};
        bool isKinematic{};
        std::string sprite{};
        raylib::Vector2 spriteSize{};
        UserData userData{};
        raylib::Vector2 velocity{};

        int layerIndex{};
        tson::Object obj{};
        tson::Vector2i pos{};
        tson::Vector2i size{};
        tson::Vector2i originalSize{};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_OBJECTGENERATORDATA_HPP
