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
        child->parent = weak_from_this();
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
struct GraphNode;

struct GraphEdge {
    private:
        GraphEdge(
            const std::shared_ptr<GraphNode>& a, 
            const std::shared_ptr<GraphNode>& b,
            bool bidirectional = false) 
            : origin(a), dest(b) {}
    public:
        static std::shared_ptr<GraphEdge>createEdge(
            const std::shared_ptr<GraphNode>& a, 
            const std::shared_ptr<GraphNode>& b,
            bool bidirectional = false) {
                return std::shared_ptr<GraphEdge>(
                    new GraphEdge(a, b, bidirectional));
            }
        std::weak_ptr<GraphNode> origin; // The node the edge is coming from
        std::weak_ptr<GraphNode> dest; // The node the edge ends on
        bool bidirectional; // If the edge goes both ways
};

struct GraphNode : virtual public std::enable_shared_from_this<GraphNode> {
    std::vector<std::shared_ptr<GraphEdge>> edges;

    // For inherits with more complex constructors
    template <typename... Args>
    static std::shared_ptr<GraphNode>createNode(Args &&... args) {
        return std::shared_ptr<GraphNode>(new GraphNode(std::forward<Args>(args)...));
    }

    std::shared_ptr<GraphNode>getPtr() {
        return shared_from_this();
    }

    std::shared_ptr<GraphEdge> attachNode(const std::shared_ptr<GraphNode>& dest, bool bidirectional = true) {
        auto e = GraphEdge::createEdge(getPtr(), dest, bidirectional);
        edges.emplace_back(e);

        if(bidirectional) {
            dest->edges.emplace_back(e);
        }
        return e;
    }
};

/**
 * @brief Edges between graph nodes.
 * Can be used for transitions.
 */


struct Graph {
    std::vector<std::shared_ptr<GraphNode>> nodes;
    std::vector<std::shared_ptr<GraphEdge>> edges;
    
    void addNode(const std::shared_ptr<GraphNode>& node) {
        nodes.push_back(node);
    }
    void addEdge(const std::shared_ptr<GraphEdge>& edge) {
        edges.push_back(edge);
    }
};