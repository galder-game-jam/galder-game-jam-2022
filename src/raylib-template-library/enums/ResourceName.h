//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_RESOURCENAME_H
#define GAME_DEV_TEMPLATE_RESOURCENAME_H

#include <cstdint>

namespace ggj
{
    /*!
     * ResourceName should be composed by something like this:
     * <ResourceType><ResourceId>.
     * Example:
     * GraphicsPlayer - Where <ResourceType>=Graphics and <ResourceId>=Player.
     *
     * ResourceTypes:
     * Graphics
     * Sound
     *
     */
    enum class ResourceName : uint16_t
    {
        None = 0,
        GraphicsPlayer = 1,
        GraphicsBoulderSmall = 2,
        GraphicsBoulderMedium = 3,
        GraphicsBoulderBig = 4,
        GraphicsTileset1 = 5,
        GraphicsTileset2 = 6,
        MapProject = 7,
        GraphicsAndre = 8,
        GraphicsPlayerSimple = 9,
        GraphicsMagicCliffsTileset = 10,
        GraphicsEnemyBat = 11,
        GraphicsCrate = 12,
        GraphicsNinjaSmiley = 13,
    };
}

#endif //GAME_DEV_TEMPLATE_RESOURCENAME_H
