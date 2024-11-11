#pragma once
#include <memory>
#include <vector>
#include "ecs.hpp"
#include "common.hpp"

/**
 * @brief TreeNode base class
 * 
 */
template <class NodeType>
struct TreeNode : virtual public std::enable_shared_from_this<NodeType> {
    std::weak_ptr<NodeType> parent;
    std::vector<std::shared_ptr<NodeType>> children;
    void addChild(std::shared_ptr<NodeType>& child) {
        children.push_back(child);
        child->parent = this->weak_from_this();
    }
    void removeChild(std::shared_ptr<NodeType>& child) {
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
    // virtual ~TreeNode ();
};

// Graph implementation:
template <class NodeType>
struct GraphNode;

template <class NodeType>
struct GraphEdge {
    private:
        GraphEdge(
            const std::shared_ptr<GraphNode<NodeType>>& a, 
            const std::shared_ptr<GraphNode<NodeType>>& b,
            bool bidirectional = false) 
            : origin(a), dest(b) {}
    public:
        static std::shared_ptr<GraphEdge>createEdge(
            const std::shared_ptr<GraphNode<NodeType>>& a, 
            const std::shared_ptr<GraphNode<NodeType>>& b,
            bool bidirectional = false) {
                return std::shared_ptr<NodeType>(
                    new GraphEdge(a, b, bidirectional));
            }
        std::weak_ptr<GraphNode<NodeType>> origin; // The node the edge is coming from
        std::weak_ptr<GraphNode<NodeType>> dest; // The node the edge ends on
        bool bidirectional; // If the edge goes both ways
};

template <class NodeType>
struct GraphNode : virtual public std::enable_shared_from_this<NodeType> {
    std::vector<NodeType> edges;

    // For inherits with more complex constructors
    template <typename... Args>
    static std::shared_ptr<NodeType>createNode(Args &&... args) {
        return std::shared_ptr<NodeType>(new NodeType(std::forward<Args>(args)...));
    }

    std::shared_ptr<NodeType>getPtr() {
        return this->shared_from_this();
    }

    std::shared_ptr<GraphEdge<NodeType>> attachNode(const std::shared_ptr<NodeType>& dest, bool bidirectional = true) {
        auto&& e = GraphEdge<NodeType>::createEdge(getPtr(), dest, bidirectional);
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

template <class NodeType, class EdgeType>
struct Graph {
    std::vector<std::shared_ptr<NodeType>> nodes;
    std::vector<std::shared_ptr<EdgeType>> edges;
    
    void addNode(const std::shared_ptr<NodeType>& node) {
        nodes.push_back(node);
    }
    void addEdge(const std::shared_ptr<EdgeType>& edge) {
        edges.push_back(edge);
    }
};