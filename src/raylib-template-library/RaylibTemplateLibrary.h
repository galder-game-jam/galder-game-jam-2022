//
// Created by robin on 26.10.22.
//

#ifndef GAME_DEV_TEMPLATE_RAYLIBTEMPLATELIBRARY_H
#define GAME_DEV_TEMPLATE_RAYLIBTEMPLATELIBRARY_H

#include "../gamedev-base/GameDevBase.h"

//Interfaces
#include "interfaces/system/IMapper.h"

//Enums
#include "enums/AnimationName.h"
#include "enums/KeyboardKey.h"
#include "enums/PlayerState.h"

//Game
#include "game/Player.h"

//Enemies
#include "game/enemies/Bat.h"
#include "game/enemies/Snake.h"

//Managers
#include "managers/AnimationManager.h"
#include "managers/CollisionManager.h"
#include "managers/DummyDebugManager.hpp"
#include "managers/DebugManager.h"
#include "managers/GameManager.h"
#include "managers/ResourceManager.hpp"
#include "managers/InputManager.h"
#include "managers/TextureManager.h"
#include "managers/UserDataManager.hpp"
#include "managers/WorldManager.h"

//System
#include "system/World.h"
#include "system/Mapper.hpp"


#endif //GAME_DEV_TEMPLATE_RAYLIBTEMPLATELIBRARY_H
