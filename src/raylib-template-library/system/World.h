//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_WORLD_H
#define GAME_DEV_TEMPLATE_WORLD_H

#include "../../gamedev-base/GameDevBase.h"
#include "../enums/Stage.h"
#include "../enums/ResourceName.h"
#include "box2d/box2d.h"
#include "tileson.hpp"
#include "../interfaces/system/IMapper.h"
#include "raylib-cpp.hpp"
#include "WorldLayer.h"
#include "../enums/KeyboardKey.h"
#include "../graphics/PhysicsObject.h"
#include "../RaylibTemplateLibrary.h"

namespace dev
{
    class World : public dev::IWorld<Stage>
    {
        public:
            World(dev::ILogger &logger, dev::IResourceManager<ResourceName> &resources, IMapper &mapper,
                  dev::ITextureManager<TextureName, raylib::Texture> &textures,
                  raylib::Window &window, dev::IInputManager<dev::KeyboardKey> &input, CollisionManager &collisionManager, IDebugManager &debugManager,
                  std::unique_ptr<tson::Map> map)
                    : m_logger{logger}, m_resources{resources}, m_mapper{mapper}, m_textures{textures}, m_window{window},
                    m_input {input}, m_collisionManager {collisionManager}, m_debugManager {debugManager}, m_map{std::move(map)}
            {
                m_camera.target = (Vector2){ 0.f, 0.f };
                m_camera.offset = {0.f, 0.f};//{8.f, 8.f};//(Vector2){ (float) window.GetWidth() / 2.0f, (float)window.GetHeight() / 2.0f };
                m_camera.rotation = 0.0f;
                m_camera.zoom = 1.0f;
            }

            bool  initialize() override;
            void update(float timeDelta) override;
            void draw() override;

        private:
            dev::ILogger &m_logger;
            dev::IResourceManager<ResourceName> &m_resources;
            IMapper &m_mapper;
            dev::ITextureManager<TextureName, raylib::Texture> &m_textures;
            raylib::Window &m_window;
            dev::IInputManager<dev::KeyboardKey> &m_input;
            dev::CollisionManager &m_collisionManager;
            dev::IDebugManager &m_debugManager;
            raylib::Camera2D m_camera;

            Player *m_player = nullptr;

            b2World m_world{{0.f, 0.f}};
            std::unique_ptr<tson::Map> m_map{nullptr};

            raylib::Color m_backgroundColor = raylib::Color::White();
            std::map<int32_t, dev::WorldLayer> m_layers;

    };
}

#endif //GAME_DEV_TEMPLATE_WORLD_H
