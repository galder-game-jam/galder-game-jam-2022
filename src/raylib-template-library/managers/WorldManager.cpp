//
// Created by robin on 29.10.22.
//

#include "WorldManager.h"

namespace dev
{
    bool WorldManager::initialize()
    {
        bool projectExists = m_resources.exists(ResourceName::MapProject);
        if (projectExists)
        {
            m_logger.debug("FOUND project!");
            parseProject();
        }

        return projectExists;
    }

    bool WorldManager::parseProject()
    {
        m_project = std::make_unique<tson::Project>();

        if (!m_project->parse(fs::path(m_resources.getResource(ResourceName::MapProject))))
        {
            m_logger.error("Failed parsing project...");
            return false;
        }
        m_logger.debug("Project parsed SUCCESSFULLY");
        tson::Tileson t{m_project.get()};
        for (const auto &folder: m_project->getFolders())
        {
            for (const auto &file: folder.getFiles())
            {
                if (file.filename().string().ends_with(".json")) //Make sure it's a map!
                {
                    Stage stage = getStageByFilename(file.filename());
                    if (stage == Stage::None)
                    {
                        m_logger.warning(fmt::format("The filename '{0}' is not recognized as a stage. File is ignored...", file.filename().c_str()));
                        continue;
                    }
                    std::unique_ptr<tson::Map> map = t.parse(fs::path(folder.getPath() / file.filename()));

                    if (map->getStatus() == tson::ParseStatus::OK)
                    {
                        m_worlds[stage] = std::make_unique<World>(m_logger, m_resources, m_mapper, m_textures, m_window, m_input, m_collisionManager, m_debugManager, std::move(map));
                        m_worlds[stage]->initialize();
                        m_logger.debug(fmt::format("World added: {0}", file.filename().c_str()));
                    }
                    else
                        m_logger.error(fmt::format("Error while parsing map: {0}", file.filename().c_str()));
                }
            }
        }

        //Expect something!
        if (m_worlds.empty())
        {
            m_logger.error("No maps found! initialization of WorldManager failed!");
            return false;
        }
        if (m_worlds.count(Stage::Stage1) > 0)
            m_currentStage = Stage::Stage1;

        m_logger.debug("WorldManager initialized SUCCESSFULLY!");

        return true;
    }

    void WorldManager::update(float timeDelta)
    {
        #ifdef GAME_DEV_DEBUG
        if (m_input.keyPressed(dev::KeyboardKey::F1)) m_currentStage = Stage::Stage1;
        if (m_input.keyPressed(dev::KeyboardKey::F2)) m_currentStage = Stage::Stage2;
        #endif

        if (m_currentStage == Stage::None)
            return;

        if (m_worlds.count(m_currentStage) > 0)
        {
            m_worlds[m_currentStage]->update(timeDelta);
        }
    }

    void WorldManager::draw()
    {
        if (m_currentStage == Stage::None)
            return;

        if (m_worlds.count(m_currentStage) > 0)
        {
            m_worlds[m_currentStage]->draw();
        }
    }

    Stage WorldManager::getStageByFilename(const std::string &filename)
    {
        if (filename == "map1.json") return Stage::Stage1;
        if (filename == "map2.json") return Stage::Stage2;

        return Stage::None;
    }
}