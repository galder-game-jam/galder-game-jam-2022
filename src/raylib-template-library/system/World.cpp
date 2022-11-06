//
// Created by robin on 29.10.22.
//

#include "World.h"
#include "../graphics/Sprite.h"
#include "../graphics/PhysicsSprite.h"

namespace dev
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
                            m_layers[layerIndex].createGameObject<dev::Sprite>(v, r, tex);
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
                            m_layers[layerIndex].createGameObject<dev::PhysicsObject>(body, raylib::Vector2((float)size.x, (float)size.y), shape, color, isVisible);
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

                                    if(isPlayer)
                                    {
                                        m_player = m_layers[layerIndex].createGameObject<dev::Player>(m_input, body, raylib::Vector2((float) size.x, (float) size.y), r,
                                                                                                  tex);
                                    }
                                    else
                                        m_layers[layerIndex].createGameObject<dev::PhysicsSprite>(body, raylib::Vector2((float) size.x, (float) size.y), r,
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
                    : raylib::Vector2(0.f, 0.f);

            m_debugManager.setText(1, fmt::format("PlayerPos: ({0}, {1})", (int) m_player->getPosition().x, (int) m_player->getPosition().y));
        }
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