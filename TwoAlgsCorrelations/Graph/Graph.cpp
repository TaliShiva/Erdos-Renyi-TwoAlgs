#include <sstream>

#include "Graph.h"

std::vector<short> Graph::GetNeighbours(short i) {
    std::vector<short> neighbours{};
    for (short j = 0; j < _adjacency_matrix.size(); j++) {
        if (_adjacency_matrix[i][j]) {
            neighbours.push_back(j);
        }
    }
    return neighbours;
}

std::vector<std::vector<bool>> Graph::GetCopyOfAdjacencyMatrix() const {
    return _adjacency_matrix;
}

int Graph::GetRoot() const {
    for (short i = 0; i < _adjacency_matrix.size(); i++) {
        for (short j = 0; j < _adjacency_matrix.size(); j++) {
            if (_adjacency_matrix[i][j]) {
                return 0;
            }
        }
    }
    return 0;
}
