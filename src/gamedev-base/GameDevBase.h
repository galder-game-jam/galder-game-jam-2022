//
// Created by robin on 28.10.22.
//

#ifndef GAME_DEV_TEMPLATE_GAMEDEVBASE_H
#define GAME_DEV_TEMPLATE_GAMEDEVBASE_H

//Enums
#include "enums/LogLevel.h"

//Interfaces
#include "interfaces/managers/IInputManager.h"
#include "interfaces/managers/IGameManager.h"
#include "interfaces/managers/IResourceManager.h"
#include "interfaces/managers/ITextureManager.h"
#include "interfaces/managers/IWorldManager.h"
#include "interfaces/managers/IDebugManager.h"
#include "interfaces/system/ITimer.h"
#include "interfaces/system/IWorld.h"
#include "interfaces/system/ILogger.h"
#include "interfaces/system/IExecutableInfo.h"
#include "interfaces/system/IGameObject.h"

//System
#include "system/ExecutableInfo.h"
#include "system/ConsoleLogger.h"
#include "system/DummyLogger.hpp"
#include "system/Timer.h"
#include "system/Vector2D.hpp"
#include "system/Colori.hpp"

#endif //GAME_DEV_TEMPLATE_GAMEDEVBASE_H
