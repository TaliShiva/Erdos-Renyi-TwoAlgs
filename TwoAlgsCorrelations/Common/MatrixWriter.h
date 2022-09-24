#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include <vector>

/// <summary>
/// Вспомогательный класс, используемый для выведения в консоль матриц
/// </summary>
class MatrixWriter {
public:
    static std::string ToJson(const std::vector<std::vector<bool>> &_adjacency_matrix, const std::string &name);
};
