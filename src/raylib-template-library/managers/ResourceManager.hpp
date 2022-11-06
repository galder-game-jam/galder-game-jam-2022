//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP
#define GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP

#include <map>
#include "../../gamedev-base/GameDevBase.h"
#include "fmt/format.h"

namespace dev
{
    template <class T>
    class ResourceManager : public IResourceManager<T>
    {
        public:
            explicit ResourceManager(dev::IExecutableInfo &executableInfo) : m_executableInfo {executableInfo} {};
            void initialize() override;

            void add(T resourceType, std::string value) override;
            bool exists(T resourceType) override;

            std::string getResource(T resourceType) override;

            std::string getResource(const std::string &resource) override;

        private:
            std::map<T, std::string> m_resources;

            dev::IExecutableInfo &m_executableInfo;
    };

    template<class T>
    void ResourceManager<T>::initialize()
    {
        add(dev::ResourceName::GraphicsPlayer, "graphics/characters.png");
        add(dev::ResourceName::GraphicsPlayerSimple, "graphics/player-simple.png");
        add(dev::ResourceName::GraphicsTileset1, "graphics/sheet.png");
        add(dev::ResourceName::GraphicsTileset2, "graphics/tiles.png");
        add(dev::ResourceName::GraphicsBoulderSmall, "graphics/boulder-small.png");
        add(dev::ResourceName::GraphicsBoulderMedium, "graphics/boulder-medium.png");
        add(dev::ResourceName::GraphicsBoulderBig, "graphics/boulder-big.png");
        add(dev::ResourceName::GraphicsAndre, "graphics/andre.png");
        add(dev::ResourceName::MapProject, "maps/gamedev.tiled-project");
    }

    template<class T>
    std::string ResourceManager<T>::getResource(T resourceType)
    {
        static std::string defaultStr;
        return (m_resources.count(resourceType) > 0)
                    ? fmt::format("{0}/{1}", m_executableInfo.getContentRootDirectory().string(), m_resources[resourceType])
                    : defaultStr;
    }

    template<class T>
    void ResourceManager<T>::add(T resourceType, std::string value)
    {
        m_resources[resourceType] = value;
    }

    template<class T>
    bool ResourceManager<T>::exists(T resourceType)
    {
        if(m_resources.count(resourceType) > 0)
        {
            std::filesystem::path p = std::filesystem::path(getResource(resourceType));
            return std::filesystem::exists(p);
        }
        return false;
    }

    template<class T>
    std::string ResourceManager<T>::getResource(const std::string &resource)
    {
        return fmt::format("{0}/{1}", m_executableInfo.getContentRootDirectory().string(), resource);
    }

} // dev

#endif //GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP
