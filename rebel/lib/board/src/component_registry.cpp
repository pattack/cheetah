//
// Created by pouyan on 7/14/25.
//

#include <rebel/board/component_registry.hpp>

namespace Rebel::Board
{
    void ComponentRegistry::Register(const ComponentType type, Component* component)
    {
        components()[type] = component;
    }

    Component* ComponentRegistry::Get(const ComponentType type)
    {
        auto& map = components();
        if (const auto it = map.find(type); it != map.end())
        {
            return it->second;
        }

        return nullptr;
    }

    std::map<ComponentType, Component*>& ComponentRegistry::components()
    {
        static std::map<ComponentType, Component*> instance;

        return instance;
    }
}
