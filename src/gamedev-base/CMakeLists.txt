project(gamedev_base VERSION 1.0.0)

add_library(gamedev_base GameDevBase.h system/ConsoleLogger.cpp system/ExecutableInfo.cpp interfaces/system/IWorld.h interfaces/system/ITimer.h system/Timer.cpp system/Timer.h interfaces/managers/ITextureManager.h interfaces/system/IGameObject.h system/Vector2D.hpp interfaces/managers/IDebugManager.h system/Colori.hpp interfaces/managers/IAnimationManager.h)
