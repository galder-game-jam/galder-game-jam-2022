//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IRESOURCEMANAGER_H
#define GAME_DEV_TEMPLATE_IRESOURCEMANAGER_H

#include <string>

namespace dev
{
    template <class T>
    class IResourceManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IResourceManager() noexcept = default;

            virtual void initialize() = 0;
            virtual void add(T resourceType, std::string value) = 0;
            virtual bool exists(T resourceType) = 0;
            virtual std::string getResource(T resourceType) = 0;
            virtual std::string getResource(const std::string &resource) = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IRESOURCEMANAGER_H
