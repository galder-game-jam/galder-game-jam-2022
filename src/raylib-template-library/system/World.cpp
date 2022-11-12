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
                        ObjectGeneratorData generatorData {};

                        std::string name = obj.getName();
                        generatorData.isStatic = c->get<bool>("is_static");
                        generatorData.isTrigger = c->get<bool>("is_trigger");
                        generatorData.isKinematic = c->get<bool>("is_kinematic");
                        generatorData.isPlayer = c->get<bool>("is_player");
                        generatorData.sprite = c->get<std::string>("sprite");
                        generatorData.spriteSize.x = (float)c->get<int>("sprite_size_x");
                        generatorData.spriteSize.y = (float)c->get<int>("sprite_size_y");
                        generatorData.velocity.x = c->get<float>("velocity_x");
                        generatorData.velocity.y = c->get<float>("velocity_y");

                        float userDataForceX = c->get<float>("userdata_force_x");
                        float userDataForceY = c->get<float>("userdata_force_y");
                        int userdataObjectType = c->get<int>("userdata_objecttype");
                        std::string userdataCommand = c->get<std::string>("userdata_command");

                        //RBP: Note to self: Improve Tileson so this was handled automatically in the TiledClass.
                        for(auto &[key, value] : obj.getProperties().getProperties())
                        {
                            if(key == "is_static")
                                generatorData.isStatic = value.getValue<bool>();
                            else if(key == "is_trigger")
                                generatorData.isTrigger = value.getValue<bool>();
                            else if(key == "is_player")
                                generatorData.isPlayer = value.getValue<bool>();
                            else if(key == "sprite")
                                generatorData.sprite = value.getValue<std::string>();
                            else if(key == "sprite_size_x")
                                generatorData.spriteSize.x = (float)value.getValue<int>();
                            else if(key == "sprite_size_y")
                                generatorData.spriteSize.y = (float)value.getValue<int>();
                            else if(key == "velocity_x")
                                generatorData.velocity.x = value.getValue<float>();
                            else if(key == "velocity_y")
                                generatorData.velocity.y = value.getValue<float>();
                            else if(key == "is_kinematic")
                                generatorData.isKinematic = value.getValue<bool>();
                            else if(key == "userdata_force_x")
                                userDataForceX = value.getValue<float>();
                            else if(key == "userdata_force_y")
                                userDataForceY = value.getValue<float>();
                            else if(key == "userdata_objecttype")
                                userdataObjectType = value.getValue<int>();
                            else if(key == "userdata_command")
                                userdataCommand = value.getValue<std::string>();
                        }

                        ObjectType objectType = (ObjectType)userdataObjectType;
                        bool isVisible = !generatorData.isStatic;
                        tson::Vector2i pos = obj.getPosition();
                        tson::Vector2i size = obj.getSize();
                        tson::Vector2i originalSize = obj.getSize();

                        b2BodyType bodyType = (generatorData.isStatic) ? b2_staticBody : b2_dynamicBody;

                        if(generatorData.isKinematic)
                        {
                            bodyType = b2_kinematicBody;
                        }

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
                            f->SetSensor(generatorData.isTrigger);
                        }

                        UserData userData {objectType, {userDataForceX, userDataForceY}, userdataCommand};

                        raylib::Color color = generatorData.isStatic ? RED : DARKPURPLE;
                        if(generatorData.sprite.empty())
                        {
                            PhysicsObject* physicsObject = m_layers[layerIndex].createGameObject<ggj::PhysicsObject>(body, raylib::Vector2((float) size.x, (float) size.y), shape,
                                                                                      userData, color, isVisible);
                            m_userDataManager.addUserData(body, physicsObject);

                        }
                        else
                        {
                            TextureName id = m_mapper.getTextureNameByString(generatorData.sprite);
                            if (id != TextureName::None)
                            {
                                raylib::Texture *tex = m_textures.get(id);
                                if(tex != nullptr)
                                {
                                    raylib::Rectangle rect = {0.f, 0.f, (float)originalSize.x, (float)originalSize.y};
                                    raylib::Vector2 origin = {(float)rect.width / 2, (float)rect.height / 2};
                                    raylib::Vector2 v = {(float)pos.x + origin.x, (float)pos.y + origin.y};

                                    raylib::Rectangle r = {(float) rect.x, (float) rect.y, (float) rect.width, (float) rect.height};


                                    if(generatorData.spriteSize.x != 0 && generatorData.spriteSize.y != 0)
                                    {
                                        r.width = generatorData.spriteSize.x;
                                        r.height = generatorData.spriteSize.y;
                                    }

                                    raylib::Vector2 offset = raylib::Vector2(r.width - rect.width, r.height - rect.height);

                                    raylib::Vector2 spriteSize = raylib::Vector2(r.width, r.height);

                                    if(generatorData.isPlayer)
                                    {
                                        m_player = m_layers[layerIndex].createGameObject<ggj::Player>(m_input, m_animationManager, m_mapper, body, raylib::Vector2((float) size.x, (float) size.y), spriteSize, r,
                                                                                                  tex, userData);
                                        m_userDataManager.addUserData(body, m_player);
                                    }
                                    else
                                    {
                                        PhysicsObject* physicsObject = m_layers[layerIndex].createGameObject<ggj::PhysicsSprite>(body,
                                                                                                  raylib::Vector2((float) size.x, (float) size.y),
                                                                                                  spriteSize, r,
                                                                                                  tex, userData);
                                        m_userDataManager.addUserData(body, physicsObject);
                                    }
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