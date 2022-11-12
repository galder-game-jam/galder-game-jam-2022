//
// Created by robin on 28.10.22.
//

#ifndef GAME_DEV_TEMPLATE_GAMEDEVBASE_H
#define GAME_DEV_TEMPLATE_GAMEDEVBASE_H

//Enums
#include "enums/LogLevel.h"

//Interfaces
#include "interfaces/managers/IAnimationManager.h"
#include "interfaces/managers/IDebugManager.h"
#include "interfaces/managers/IGameManager.h"
#include "interfaces/managers/IInputManager.h"
#include "interfaces/managers/IResourceManager.h"
#include "interfaces/managers/ITextureManager.h"
#include "interfaces/managers/IWorldManager.h"

#include "interfaces/system/IExecutableInfo.h"
#include "interfaces/system/IGameObject.h"
#include "interfaces/system/ILogger.h"
#include "interfaces/system/ITimer.h"
#include "interfaces/system/IWorld.h"

//System
#include "system/Colori.hpp"
#include "system/ConsoleLogger.h"
#include "system/DummyLogger.hpp"
#include "system/ExecutableInfo.h"
#include "system/Timer.h"
#include "system/Vector2D.hpp"

#endif //GAME_DEV_TEMPLATE_GAMEDEVBASE_H
