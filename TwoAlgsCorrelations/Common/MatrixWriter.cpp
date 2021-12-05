#include "MatrixWriter.h"

std::string MatrixWriter::ToJson(const std::vector<std::vector<bool>>& _adjacency_matrix,const std::string& name)
{
    std::stringstream ss;
    ss << name <<"\"graph\": " << "[" << std::endl;
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
