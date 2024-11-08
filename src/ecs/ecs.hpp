#pragma once
#include <vector>
#include <unordered_map>

#ifndef DEBUGMODE
#include <assert.h>
#else
#  define assert(x) {}
#endif

// This is mostly based off of the tinyecs.hpp code provided by UBC's CPSC 427 course.

namespace ECS {

    template <typename Component>
    class ComponentContainer;

	template<class Component>
	ComponentContainer<Component> registry;
    
    // For recycling Entity IDs (TODO)
    // Entity IDs
    static unsigned int id_count = 1;
    static std::vector<unsigned int> recycleQueue = {};

    static unsigned int next_id() {
        if (!recycleQueue.empty()) {
            unsigned int i = recycleQueue.back();
            recycleQueue.pop_back();
            return i;
        }
        return id_count++;
    }
    static void remove_id(unsigned int id) {
        recycleQueue.push_back(id);
    }

    struct Entity 
    {
        // Constructor uses next_id() to generate new ID. Either increment or using a discarded ID.
        Entity()
        {
            id = next_id();
        }
        unsigned int id;
        
    private:
    };


	// From CS427 
    // Common interface to refer to all containers in the ECS registry
	struct ContainerInterface
	{
		virtual void clear() = 0;
		virtual size_t size() = 0;
		virtual void remove(Entity e) = 0;
		virtual bool has(Entity entity) = 0;

		// The entities associated to the components in the container
		std::vector<Entity> entities;

		// Callbacks to remove a particular or all entities in the system
		static void clear_all_components();
		static void list_all_components();
		static void remove_all_components_of(Entity e);
		static void list_all_components_of(Entity e);
	protected:
		// The hash map from Entity -> array index.
		std::unordered_map<unsigned int, unsigned int> map_entity_component_index; // the entity is cast to uint to be hashable.
		static std::vector<ContainerInterface*>& registry_list_singleton();
	};

	// A container that stores components of type 'Component' and associated entities
	template <typename Component> // A component can be any class
	class ComponentContainer : public ContainerInterface
	{
	public:
		// Container of all components of type 'Component'
		std::vector<Component> components;

		// Constructor that registers the component type
		ComponentContainer()
		{
			auto& singleton = registry_list_singleton();
			singleton.push_back(this);
		}
		// Destructor that frees memory from the singleton vector
        ~ComponentContainer()
        {
            auto& singleton = registry_list_singleton();
            auto it = find(begin(singleton), end(singleton), this);
            assert(it != end(singleton));
			singleton.erase(it);
        }

		// Disable copy operators
        ComponentContainer(const ComponentContainer&) = delete;
        ComponentContainer& operator=(const ComponentContainer&) = delete;

		// Inserting a component c associated to entity e
		inline Component& insert(Entity e, Component c, bool check_for_duplicates = true)
		{
			// Usually, every entity should only have one instance of each component type
			if (check_for_duplicates)
				assert(map_entity_component_index.find(e.id) == map_entity_component_index.end());

			auto component_index = static_cast<unsigned int>(components.size());
			map_entity_component_index[e.id] = component_index; // Note, not using insert or emplace to allow inserting multiple components for the same entity (at your own risk)
			components.push_back(std::move(c)); // the move enforces move instead of copy constructor
			entities.push_back(e);
			return components.back();
		};

		// The emplace function takes the the provided arguments Args, creates a new object of type Component, and inserts it into the ECS system
		template<typename... Args>
		Component& emplace(Entity e, Args &&... args) {
			return insert(e, Component(std::forward<Args>(args)...)); // the forward ensures that arguments are moved not copied
		};
		template<typename... Args>
		Component& emplace_with_duplicates(Entity e, Args &&... args) {
			return insert(e, Component(std::forward<Args>(args)...), false);
		};

		// A wrapper to return the component of an entity
		Component& get(Entity e) {
			const auto it = map_entity_component_index.find(e.id);
			assert(it != map_entity_component_index.end());
			return components[it->second]; //it->first is the key, it->second the value
		}

		// Check if entity has a component of type 'Component'
		bool has(Entity e) override  {
			return map_entity_component_index.find(e.id) != map_entity_component_index.end();
		}

		// Remove an component and pack the container to re-use the empty space
		void remove(Entity e) override
		{
			// Get the current position
			const auto it = map_entity_component_index.find(e.id);
			if (it == map_entity_component_index.end())
				return; // no component stored for this element, nothing to do

			int array_index = it->second;
			// Move the last element to position cID using the move operator
			// Note, components[cID] = components.back() would trigger the copy instead of move operator
			components[array_index] = std::move(components.back());
			entities[array_index] = entities.back(); // the entity is only a single index, copy it.
			map_entity_component_index[entities.back().id] = array_index;

			// Erase the old component and free its memory
			map_entity_component_index.erase(it);
			components.pop_back();
			entities.pop_back();
		};

		// Sort the components and associated entity assignment structures by the comparisonFunction that compares the order of two entities, see std::sort
		template <class Compare>
		void sort(Compare comparisonFunction)
		{
			// First sort the entity list as desired
			std::sort(entities.begin(), entities.end(), comparisonFunction);
			// Now re-arrange the components (Note, creates a temporary vector, which may be slow! Not sure if in-place could be faster: https://stackoverflow.com/questions/63703637/how-to-efficiently-permute-an-array-in-place-using-stdswap)
			std::vector<Component> components_new; components_new.reserve(components.size());
			std::transform(entities.begin(), entities.end(), std::back_inserter(components_new), [&](Entity e) { return std::move(get(e)); }); // note, the get still uses the old hash map (on purpose!)
			components = std::move(components_new); // Note, we use move operations to not create unneccesary copies of objects, but memory is still allocated for the new vector
			// Fill the new hashmap
			for (unsigned int i = 0; i < entities.size(); i++)
				map_entity_component_index[entities[i].id] = i;
		}

		// Remove all components of type 'Component'
		void clear() override
		{
			map_entity_component_index.clear();
			components.clear();
			entities.clear();
		}

		// Report the number of components of type 'Component'
		size_t size() override
		{
			return components.size();
		}
	};
}