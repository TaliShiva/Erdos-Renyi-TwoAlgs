#include <string>
#include <sstream>

#include "Graph.h"

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