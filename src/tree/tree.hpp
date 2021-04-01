#pragma once

#include <vector>
#include <memory>

#include "node.hpp"
#include "node/iamsafe.hpp"
#include "node/move.hpp"
#include "action/move.hpp"
#include "action/idle.hpp"

struct DecisionTree_t {
    using NodeStorage_t = std::vector<std::unique_ptr<Node_t>>;

    DecisionTree_t(std::size_t reserved_size) noexcept {
        nodes.reserve(reserved_size);
    }

    template <typename NodeType, typename... Params>
    auto& createNode(Params&&... params) {
        auto node = std::make_unique<NodeType>(std::forward<Params>(params)...);
        Node_t& refNode { *node };
        addNode(std::move(node));
        return refNode;
    }

    void addNode(std::unique_ptr<Node_t> node) noexcept {
        nodes.push_back(std::move(node));
    }

    void run(World_t& w) noexcept {
        if (nodes.size() > 0) {
            nodes.back()->run(w);
        }
    }

private:
    NodeStorage_t nodes;
};