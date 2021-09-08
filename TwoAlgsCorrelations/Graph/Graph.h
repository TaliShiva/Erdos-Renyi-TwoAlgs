#pragma once

#include "IGraph.h"
#include <vector>

class Graph : public IGraph {
private:
	std::vector<std::vector<int>> _adjacency_matrix;

public:
	Graph() = delete;
	Graph(const std::vector<std::vector<int>> &adjacency_matrix) : _adjacency_matrix(adjacency_matrix) {}
	
	bool IsJoined(const unsigned i, const unsigned j) const override { return _adjacency_matrix[i][j]; }
	unsigned Size() const override {return _adjacency_matrix.size(); }

	std::vector<short> GetNeighbours(short i) override;

	std::string ToJson() const override;

	int GetRoot() const override;
};