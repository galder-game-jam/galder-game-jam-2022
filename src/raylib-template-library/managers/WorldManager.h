//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_WORLDMANAGER_H
#define GAME_DEV_TEMPLATE_WORLDMANAGER_H

#include "../enums/Stage.h"
#include "../enums/ResourceName.h"
#include "../../gamedev-base/GameDevBase.h"
#include "../system/World.h"
#include "tileson.hpp"
#include "../enums/KeyboardKey.h"
#include <map>
#include "CollisionManager.h"

namespace ggj
{
    class WorldManager : public ggj::IWorldManager
    {
        public:
            WorldManager(ggj::ILogger &logger, ggj::IResourceManager<ResourceName> &resources, IMapper &mapper,
                         ggj::ITextureManager<TextureName, raylib::Texture> &textures, raylib::Window &window,
                         ggj::IInputManager<ggj::KeyboardKey> &input, ggj::CollisionManager & collisionManager, ggj::IDebugManager &debugManager)
                    : m_logger{logger}, m_resources{resources}, m_mapper{mapper}, m_textures{textures},
                      m_window{window}, m_input{input}, m_collisionManager {collisionManager}, m_debugManager {debugManager}
            {

            }

            bool initialize() override;
            void update(float timeDelta) override;
            void draw() override;

        private:
            bool parseProject();

            Stage getStageByFilename(const std::string &filename);

            ggj::ILogger &m_logger;
            ggj::IResourceManager<ResourceName> &m_resources;
            IMapper &m_mapper;
            ggj::ITextureManager<TextureName, raylib::Texture> &m_textures;
            raylib::Window &m_window;
            ggj::IInputManager<ggj::KeyboardKey> &m_input;
            ggj::CollisionManager &m_collisionManager;
            ggj::IDebugManager &m_debugManager;

            std::unique_ptr<tson::Project> m_project{nullptr};

            std::map<Stage, std::unique_ptr<ggj::IWorld<Stage>>> m_worlds;
            Stage m_currentStage{Stage::None};
            //std::vector<std::unique_ptr<tson::Map>> m_maps;

    };
}

#endif //GAME_DEV_TEMPLATE_WORLDMANAGER_H
