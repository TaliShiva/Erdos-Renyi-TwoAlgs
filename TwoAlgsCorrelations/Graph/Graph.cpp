#include <string>
#include <sstream>

#include "Graph.h"

std::vector<short> Graph::GetNeighbours(short i) {
    std::vector<short> neighbours{};
    for (short j = 0; j < _adjacency_matrix.size(); j++) {
        if (_adjacency_matrix[i][j] != -1) {
            neighbours.push_back(j);
        }
    }
    return neighbours;
}

std::string Graph::ToJson() const {
    std::stringstream ss;
    ss << "\"graph\": " << "[" << std::endl;
    unsigned row_idx = 0;
    for (const auto& row : _adjacency_matrix) {
        row_idx++;
        ss << "[";
        unsigned elem_idx = 0;
        for (const auto elem : row) {
            elem_idx++;
            ss << elem;
            if (elem_idx != row.size()) {
                ss << ",";
            }
        }
        if (row_idx != _adjacency_matrix.size()) {
            ss << "],";
        }
        else {
            ss << "]";
        }
        ss << std::endl;
    }
    ss << "]";
    return ss.str();
}

int Graph::GetRoot() const {
    for (short i = 0; i < _adjacency_matrix.size(); i++) {
        for (short j = 0; j < _adjacency_matrix.size(); j++) {
            if (_adjacency_matrix[i][j] == true) {
                return 0;
            }
        }
    }
}