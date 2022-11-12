//
// Created by robin on 29.10.22.
//

#include "World.h"
#include "../graphics/Sprite.h"
#include "../graphics/PhysicsSprite.h"

namespace ggj
{
    bool World::initialize()
    {
        if (m_map == nullptr)
            return false;

        tson::Colori bg = m_map->getBackgroundColor();
        m_backgroundColor = raylib::Color(bg.r, bg.g, bg.b, bg.a);
        m_world.SetContactListener(&m_collisionManager);
        if(m_map->getProp("gravity_x") != nullptr && m_map->getProp("gravity_y") != nullptr)
        {
            m_world.SetGravity({m_map->get<float>("gravity_x"), m_map->get<float>("gravity_y")});
        }
        if(m_map->getProp("camera_min_x") != nullptr && m_map->getProp("camera_min_y") != nullptr)
        {
            m_cameraMin = raylib::Vector2(m_map->get<float>("camera_min_x"), m_map->get<float>("camera_min_y"));
            m_camera.target = raylib::Vector2(m_cameraMin.GetX(), m_camera.target.y);
        }
        if(m_map->getProp("camera_max_x") != nullptr && m_map->getProp("camera_max_y") != nullptr)
        {
            m_cameraMax = raylib::Vector2(m_map->get<float>("camera_max_x"), m_map->get<float>("camera_max_y"));
            m_camera.target = raylib::Vector2(m_camera.target.x, m_cameraMax.GetY());
        }

        m_cameraDefault = m_camera.target;

        int32_t layerIndex = 0;
        for (auto &layer: m_map->getLayers())
        {

            if (layer.getType() == tson::LayerType::TileLayer)
            {
                if(m_layers.count(layerIndex) == 0)
                    m_layers[layerIndex] = {layerIndex, true}; //Tiles are only for drawing and will not be updated

                for (auto &tileObject: layer.getTileObjects())
                {
                    auto pos = tileObject.second.getPosition();
                    auto rect = tileObject.second.getDrawingRect();
                    auto tileset = tileObject.second.getTile()->getTileset()->getImagePath().filename().string();
                    TextureName id = m_mapper.getTextureNameByString(tileset);
                    if (id != TextureName::None)
                    {
                        raylib::Texture *tex = m_textures.get(id);
                        if(tex != nullptr)
                        {
                            raylib::Vector2 origin = {(float)rect.width / 2, (float)rect.height / 2};
                            raylib::Vector2 v = {pos.x + origin.x, pos.y + origin.y};
                            raylib::Rectangle r = {(float) rect.x, (float) rect.y, (float) rect.width, (float) rect.height};
                            m_layers[layerIndex].createGameObject<ggj::Sprite>(v, r, tex);
                        }
                    }
                }
            }
            else if (layer.getType() == tson::LayerType::ObjectGroup)
            {
                if(m_layers.count(layerIndex) == 0)
                    m_layers[layerIndex] = {layerIndex, false}; //Objects will have their positions updated!

                for(auto &obj : layer.getObjects())
                {
                    tson::TiledClass *c = obj.getClass();
                    if(c == nullptr)
                        continue;

                    if(c->getMember("is_static") != nullptr && c->getMember("is_trigger") != nullptr)
                    {
                        bool isStatic = c->get<bool>("is_static");
                        bool isTrigger = c->get<bool>("is_trigger");
                        bool isPlayer = c->get<bool>("is_player");
                        std::string sprite = c->get<std::string>("sprite");
                        int spriteSizeX = c->get<int>("sprite_size_x");
                        int spriteSizeY = c->get<int>("sprite_size_y");

                        //RBP: Note to self: Improve Tileson so this was handled automatically in the TiledClass.
                        for(auto &[key, value] : obj.getProperties().getProperties())
                        {
                            if(key == "is_static")
                                isStatic = value.getValue<bool>();
                            else if(key == "is_trigger")
                                isTrigger = value.getValue<bool>();
                            else if(key == "is_player")
                                isPlayer = value.getValue<bool>();
                            else if(key == "sprite")
                                sprite = value.getValue<std::string>();
                            else if(key == "sprite_size_x")
                                spriteSizeX = value.getValue<int>();
                            else if(key == "sprite_size_y")
                                spriteSizeY = value.getValue<int>();
                        }

                        bool isVisible = !isStatic;
                        tson::Vector2i pos = obj.getPosition();
                        tson::Vector2i size = obj.getSize();
                        tson::Vector2i originalSize = obj.getSize();

                        b2BodyType bodyType = (isStatic) ? b2_staticBody : b2_dynamicBody;
                        PhysicsShape shape = PhysicsShape::None;
                        if(obj.getObjectType() == tson::ObjectType::Rectangle) shape = PhysicsShape::Rectangle;
                        else if(obj.getObjectType() == tson::ObjectType::Ellipse) shape = PhysicsShape::Circle;

                        b2BodyDef bodyDef;
                        bodyDef.type = bodyType;

                        b2Vec2 b2size = PhysicsObject::ConvertToB2Vec2({(float)size.x, (float)size.y});
                        b2Vec2 b2origin = PhysicsObject::ConvertToB2Vec2({(float)size.x / 2, (float)size.y / 2});
                        b2Vec2 b2pos = PhysicsObject::ConvertToB2Vec2({(float)pos.x, (float)pos.y});

                        bodyDef.position.Set(b2pos.x + b2origin.x, b2pos.y + b2origin.y);
                        b2Body *body = m_world.CreateBody(&bodyDef);
                        if(shape == PhysicsShape::Rectangle)
                        {
                            b2PolygonShape box;
                            box.SetAsBox(b2size.x / 2 - b2_polygonRadius, b2size.y / 2 - b2_polygonRadius);

                            b2FixtureDef fd;
                            fd.shape = &box;
                            fd.density = 1.0f; //Density must be something to react to gravity.
                            fd.friction = 0.3f;
                            body->CreateFixture(&fd);

                        }
                        else if(shape == PhysicsShape::Circle)
                        {
                            b2CircleShape circle;
                            size = {size.x / 2, size.y / 2}; //Size is half, as it is radius
                            circle.m_p.Set(0.f, 0.f);
                            circle.m_radius = b2origin.x;

                            b2FixtureDef fd;
                            fd.shape = &circle;
                            fd.density = 1.0f; //Density must be something to react to gravity.
                            fd.friction = 1.0f;

                            body->CreateFixture(&fd);
                        }

                        for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
                        {
                            f->SetSensor(isTrigger);
                        }

                        raylib::Color color = isStatic ? RED : DARKPURPLE;
                        if(sprite.empty())
                            m_layers[layerIndex].createGameObject<ggj::PhysicsObject>(body, raylib::Vector2((float)size.x, (float)size.y), shape, color, isVisible);
                        else
                        {
                            TextureName id = m_mapper.getTextureNameByString(sprite);
                            if (id != TextureName::None)
                            {
                                raylib::Texture *tex = m_textures.get(id);
                                if(tex != nullptr)
                                {
                                    raylib::Rectangle rect = {0.f, 0.f, (float)originalSize.x, (float)originalSize.y};
                                    raylib::Vector2 origin = {(float)rect.width / 2, (float)rect.height / 2};
                                    raylib::Vector2 v = {(float)pos.x + origin.x, (float)pos.y + origin.y};

                                    raylib::Rectangle r = {(float) rect.x, (float) rect.y, (float) rect.width, (float) rect.height};


                                    if(spriteSizeX != 0 && spriteSizeY != 0)
                                    {
                                        r.width = (float)spriteSizeX;
                                        r.height = (float)spriteSizeY;
                                    }

                                    raylib::Vector2 offset = raylib::Vector2(r.width - rect.width, r.height - rect.height);

                                    raylib::Vector2 spriteSize = raylib::Vector2(r.width, r.height);

                                    if(isPlayer)
                                    {
                                        m_player = m_layers[layerIndex].createGameObject<ggj::Player>(m_input, m_animationManager, body, raylib::Vector2((float) size.x, (float) size.y), spriteSize, r,
                                                                                                  tex);
                                    }
                                    else
                                        m_layers[layerIndex].createGameObject<ggj::PhysicsSprite>(body, raylib::Vector2((float) size.x, (float) size.y), spriteSize, r,
                                                                                              tex);
                                }
                            }

                        }
                    }
                }
            }

            ++layerIndex;
        }

        return true;
    }

    void World::update(float timeDelta)
    {

        m_world.Step(timeDelta, 8, 3); //8 and 3 are numbers suggested by Box2D documentation, higher numbers: more accuracy but costs more performance.
        for(auto & layer : m_layers)
        {
            layer.second.update(timeDelta);
        }
        if(m_player != nullptr)
        {

            m_camera.target = (m_player->cameraShouldFollowPlayer())
                    ? raylib::Vector2((float)(int)(std::round(m_player->getPosition().x) - (float)400.f / 2), (float)(int)(std::round(m_player->getPosition().y) - (float)240.f / 2))
                    : m_cameraDefault;

            m_debugManager.setText(1, fmt::format("PlayerPos: ({0}, {1})", (int) m_player->getPosition().x, (int) m_player->getPosition().y));
            m_debugManager.setText(2, fmt::format("CameraPos: ({0}, {1})", (int) m_camera.target.x, (int) m_camera.target.y));
        }

        if(m_camera.target.x > m_cameraMax.x)
            m_camera.target.x = m_cameraMax.x;
        if(m_camera.target.x < m_cameraMin.x)
            m_camera.target.x = m_cameraMin.x;
        if(m_camera.target.y > m_cameraMax.y)
            m_camera.target.y = m_cameraMax.y;
        if(m_camera.target.y < m_cameraMin.y)
            m_camera.target.y = m_cameraMin.y;
    }

    void World::draw()
    {
        m_window.ClearBackground(m_backgroundColor);
        m_camera.BeginMode();
        for(auto & layer : m_layers)
        {
            layer.second.draw();
        }
        m_camera.EndMode();
    }
}