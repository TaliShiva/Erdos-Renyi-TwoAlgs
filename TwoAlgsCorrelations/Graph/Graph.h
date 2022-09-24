#pragma once

#include "IGraph.h"
#include <utility>
#include <vector>

class Graph : public IGraph {
private:
    std::vector<std::vector<bool>> _adjacency_matrix;

public:
    Graph() = delete;

    explicit Graph(std::vector<std::vector<bool>> adjacency_matrix) : _adjacency_matrix(std::move(adjacency_matrix)) {}

    bool IsJoined(const unsigned i, const unsigned j) const override { return _adjacency_matrix[i][j]; }

    unsigned Size() const override { return _adjacency_matrix.size(); }

    std::vector<short> GetNeighbours(short i) override;

    std::vector<std::vector<bool>> GetCopyOfAdjacencyMatrix() const override;

    int GetRoot() const override;
};
