#pragma once
#include <memory>
#include <vector>
#include "ecs.hpp"
#include "common.hpp"

/**
 * @brief TreeNode base class
 * 
 */
struct TreeNode : virtual public std::enable_shared_from_this<TreeNode> {
    std::weak_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;
    void addChild(std::shared_ptr<TreeNode>& child) {
        children.push_back(child);
        child->parent = shared_from_this();
    }
    void removeChild(std::shared_ptr<TreeNode>& child) {
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }

    template <typename Function>
    void traverse(Function&& func) {
        func(*this);
        for (auto& child : children) {
            child->traverse(func);
        }
    }

    // https://stackoverflow.com/a/318137
    virtual ~TreeNode ();
};

// Graph implementation:
struct GraphEdge;

struct GraphNode {
    std::vector<std::shared_ptr<GraphEdge>> edges;
};

/**
 * @brief Edges between graph nodes.
 * Can be used for transitions.
 */
struct GraphEdge {
    std::weak_ptr<GraphNode> origin;
    std::weak_ptr<GraphNode> dest;
};
