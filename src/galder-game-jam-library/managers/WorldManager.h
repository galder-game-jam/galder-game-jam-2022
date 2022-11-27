//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_WORLDMANAGER_H
#define GAME_DEV_TEMPLATE_WORLDMANAGER_H

#include "../enums/ResourceName.h"
#include "../../gamedev-base/GameDevBase.h"
#include "../system/World.h"
#include "tileson.hpp"
#include "../enums/KeyboardKey.h"
#include <map>
#include "CollisionManager.h"
#include "UserDataManager.hpp"

namespace ggj
{
    class WorldManager : public ggj::IWorldManager
    {
        public:
            WorldManager(ggj::ILogger &logger, ggj::IResourceManager<ResourceName> &resources, IMapper &mapper,
                         ggj::ITextureManager<TextureName, raylib::Texture> &textures, raylib::Window &window,
                         ggj::IInputManager<ggj::KeyboardKey> &input, ggj::CollisionManager & collisionManager,
                         ggj::IDebugManager &debugManager, ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager,
                         IUserDataManager<PhysicsObject*> &userDataManager)
                    : m_logger{logger}, m_resources{resources}, m_mapper{mapper}, m_textures{textures},
                      m_window{window}, m_input{input}, m_collisionManager {collisionManager},
                      m_debugManager {debugManager}, m_animationManager {animationManager}, m_userDataManager{userDataManager}
            {

            }

            bool initialize() override;
            void update(float timeDelta) override;
            void draw() override;

        private:
            bool parseProject();

            const int32_t NO_MAP_ID = -1;
            const int32_t FINAL_MAP_ID = 99999;

            //Stage getStageByFilename(const std::string &filename);
            int32_t getStageIndexByFilename(const std::string &filename);

            ggj::ILogger &m_logger;
            ggj::IResourceManager<ResourceName> &m_resources;
            IMapper &m_mapper;
            ggj::ITextureManager<TextureName, raylib::Texture> &m_textures;
            raylib::Window &m_window;
            ggj::IInputManager<ggj::KeyboardKey> &m_input;
            ggj::CollisionManager &m_collisionManager;
            ggj::IDebugManager &m_debugManager;
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            IUserDataManager<PhysicsObject*> &m_userDataManager;

            std::unique_ptr<tson::Project> m_project{nullptr};

            std::map<int32_t, std::unique_ptr<ggj::IWorld<int32_t>>> m_worlds;
            //Stage m_currentStage{Stage::None};
            int32_t m_startupIndex{-1};
            int32_t m_currentStageIndex {-1};
            //std::vector<std::unique_ptr<tson::Map>> m_maps;

    };
}

#endif //GAME_DEV_TEMPLATE_WORLDMANAGER_H
