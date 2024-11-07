#include "ecs.hpp"
#include "defines.hpp"


// #define NDEBUG // (uncomment to disable asserts)
#include <cassert>

using namespace ECS;

std::vector<ContainerInterface*>& ContainerInterface::registry_list_singleton() {
	// This is a Meyer's singleton, i.e., a function returning a static local variable by reference to solve SIOF
	static std::vector<ContainerInterface*> singleton; // constructed during first call
	return singleton;
}

void ContainerInterface::clear_all_components() {
	for (auto reg : registry_list_singleton()) {
		reg->clear();
    }
}


void ContainerInterface::remove_all_components_of(Entity e) {
	for (auto reg : registry_list_singleton()) {
        assert(reg); // Must not be null
		reg->remove(e);
    }
}

// For debugging use
void ContainerInterface::list_all_components() {
	DEBUG_LOG("Debug info on all registry entries:\n");
	const auto& singleton = registry_list_singleton();
	for (auto reg : singleton) {
        assert(reg); // Must not be null
		if (reg->size() > 0) {
			DEBUG_LOG("  " << reg->size() << " components of type "
                << typeid(*reg).name() << "\n    ");
			for (auto entity : reg->entities) {
				DEBUG_LOG(entity.id << ", ");
            }
			DEBUG_LOG('\n');
		}
	}
#ifndef DEBUGMODE
    FLUSH();
#endif
}

void ContainerInterface::list_all_components_of(Entity e) {
	DEBUG_LOG("Debug info on components of entity " << e.id << ":\n");
	for (auto reg : registry_list_singleton()) {
        assert(reg); // Must not be null
		if (reg->has(e)) {
			DEBUG_LOG(
                "  type " << typeid(*reg).name() << ", stored at location "
                << reg->map_entity_component_index[e.id] << '\n');
        }
    }
}

