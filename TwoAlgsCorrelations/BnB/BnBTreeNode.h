#pragma once

#include <list>
#include <set>
#include <vector>

#include "BnB.h"
#include "IGraph.h"
#include "MatrixCoordinate.h"

/// <summary>
/// Класс, для хранения состояния графа в ноде дерева рассчётов
/// </summary>
class CalculatedTreeNode {
    int _best_distance = 0;
    int _current_distance = 0;
    int _matrix_size = 0;
public:
    std::vector<std::vector<bool>> _current_node_adjacency_matrix{};
    std::vector<std::vector<bool>> _current_node_marked_matrix{};

    CalculatedTreeNode(int size) {
        for (int i = 0; i < size; i++) {
            _current_node_adjacency_matrix.emplace_back(size);
            _current_node_marked_matrix.emplace_back(size);
        }
        _best_distance = 0;
        _current_distance = 0;
        _matrix_size = size;
    }

    CalculatedTreeNode(std::vector<std::vector<bool>> &_adjacency_matrix,
                       std::vector<std::vector<bool>> &_marked_edges_ajacency_matrix, int matrix_size) :
            _current_node_adjacency_matrix(_adjacency_matrix),
            _current_node_marked_matrix(_marked_edges_ajacency_matrix),
            _matrix_size(matrix_size) {
    }

    CalculatedTreeNode(CalculatedTreeNode &treeNode, int bestDistance) :
            _current_node_adjacency_matrix(treeNode._current_node_adjacency_matrix),
            _current_node_marked_matrix(treeNode._current_node_marked_matrix),
            _best_distance(bestDistance),
            _matrix_size(treeNode._matrix_size),
            _current_distance(treeNode._current_distance) {
    }

    /// <summary>
    /// Считаем расстояние между изначальным графом и графом в ноде
    /// </summary>
    /// <returns> Возвращает расстояние между графами в количестве различных рёбер </returns>
    int calculateDistance(const IGraphPtr &graph) {
        const auto graph_size = (*graph).Size();

        int distance = 0; //

        for (int i = 0; i < graph_size; ++i) {
            for (int j = i; j < graph_size; ++j) {
                if (!((*graph).IsJoined(i, j) && _current_node_adjacency_matrix[i][j])) {
                    distance++;
                }
            }
        }

        return distance;
    }

    /// <summary>
    /// Проверка графа на пустоту
    /// </summary>
    /// <returns></returns>
    bool checkEmptySubGraph() {
        for (int i = 0; i < _matrix_size; ++i) {
            for (int j = i; j < _matrix_size; ++j) {
                if (_current_node_adjacency_matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }


    /// <summary>
    /// Проверка, все ли рёбра в графе уже маркированы
    /// </summary>
    /// <returns> true - если все ребра совпали, false в обратном случае </returns>
    bool checkFullMarking() {
        for (int i = 0; i < _matrix_size; ++i) {
            for (int j = i; j < _matrix_size; ++j) {
                if (_current_node_adjacency_matrix[i][j] != _current_node_marked_matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isPossibleClusterGraph(bool isResultedGraph) {
        // копируем в массив номер вершин, только те, которые уже есть в рассмотрении

        std::set<int> checked_vertesises{};
        for (int i = 0; i < _matrix_size; ++i) {
            if (checked_vertesises.find(i) != checked_vertesises.end()) continue;
            for (int j = i; j < _matrix_size; ++j) {
                if (checked_vertesises.find(j) != checked_vertesises.end()) continue;
                if (_current_node_marked_matrix[i][j]) {
                    if (!is_cluster(checked_vertesises, i, isResultedGraph)) return false;
                    //если рассмотренный маркированный подграф невозможен выходим
                }
            }
        }

        return true;
    }

    bool is_cluster(std::set<int> &checked_vertesises, int i, bool isResultedGraph) {
        // сперва получаем список связанных вершин
        std::set<int> visited{};
        std::set<int> neighbours{};
        visited.insert(i);
        for (int j = 0; j < _matrix_size; j++) {
            if (_current_node_marked_matrix[i][j]) {
                neighbours.insert(j);
            }
        }
        // прошла первая итерация

        while (!neighbours.empty()) {
            int neighbour = *neighbours.begin();
            visited.insert(neighbour);
            for (int j = 0; j < _matrix_size; j++) {
                if (visited.find(j) != visited.end()) continue;
                if (_current_node_marked_matrix[neighbour][j]) {
                    neighbours.insert(j);
                }
            }
            neighbours.erase(neighbour);
        }
        // на этом моменте у нас типо есть множество вершин

        // Проверяем количество вершин, если оно меньше размера предполагаемого кластера - то всё ок, помещаем в массив потенциальных клик и выходим
        if (!isResultedGraph) {
            if (visited.size() <= 3)
                return true; // пока что возможен
        }
        // Потом, проверяем по этому списку получается ли клика какого-то размера или нет
        for (int vertex_num: visited)
            if (!VertexHasEdgesWithAllOtherVertexInCluster(vertex_num, visited)) {
                return false;
            }
        // не забыть поместим в checked_vertex нужные вершин
        checked_vertesises = visited;
        return true;
    }

    bool VertexHasEdgesWithAllOtherVertexInCluster(int j, std::set<int> &vertecises_set) {
        for (int vertex_num: vertecises_set) {
            if (vertex_num == j) continue;
            if (!_current_node_marked_matrix[j][vertex_num])
                return false;
        }
        // перебрали все вершина k-кластера
        return true;
    }

    /// <summary>
    /// Помечаем ребро
    /// </summary>
    void markEdge(MatrixCoordinate matrix_coordinate) {
        _current_node_marked_matrix[matrix_coordinate.i][matrix_coordinate.j] = true;
        _current_node_marked_matrix[matrix_coordinate.j][matrix_coordinate.i] = true;
    }

    void incCurDistance() {
        _current_distance++;
    }

    void rejectEdge(MatrixCoordinate matrix_coordinate) {
        _current_node_adjacency_matrix[matrix_coordinate.i][matrix_coordinate.j] = false;
        _current_node_adjacency_matrix[matrix_coordinate.j][matrix_coordinate.i] = false;
    }

    bool isMayBeTriangle(const int i_1, const int j_1, const int i_2, const int j_2) {
        if (_current_node_adjacency_matrix[i_1][j_2] != 0) return true;
        return false;
    }

    int getCurrentDistance() const {
        return _current_distance;
    }
};
