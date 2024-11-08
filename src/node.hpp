#pragma once
#include <memory>
#include <vector>
#include "ecs.hpp"

/**
 * @brief NodeComponent base class
 * 
 */
class NodeComponent : public std::enable_shared_from_this<NodeComponent> {
public:
    std::weak_ptr<NodeComponent> parent;
    std::vector<std::shared_ptr<NodeComponent>> children;
    void addChild(std::shared_ptr<NodeComponent>& child) {
        children.push_back(child);
        child->parent = shared_from_this();
    }
    void removeChild(std::shared_ptr<NodeComponent>& child) {
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }

    template <typename Function>
    void traverse(Function&& func) {
        func(*this);
        for (auto& child : children) {
            child->traverse(func);
        }
    }
};

