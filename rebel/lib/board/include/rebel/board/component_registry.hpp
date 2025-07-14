//
// Created by pouyan on 7/14/25.
//

#pragma once

#include <map>

#include "component.hpp"
#include "component_type.hpp"

namespace Rebel::Board
{
    class ComponentRegistry
    {
    public:
		static void Register(ComponentType type, Component* component);

		static Component* Get(ComponentType type);

	private:
		static std::map<ComponentType, Component*>& components();
    };
}
