#include "A2Alg.h"

#include <iostream>
#include <iterator>
#include <random>
#include <utility>
#include <algorithm>

A2Alg::A2Alg(std::vector<std::vector<bool>> adjacency_matrix, int matrix_size, int cluster_size,
             std::vector<std::vector<bool>> m_graph, std::vector<std::vector<bool>> k_graph)
        : _adjacency_matrix(std::move(adjacency_matrix)),
          _matrix_size(matrix_size),
          _cluster_size(cluster_size),
          _m_graph(std::move(m_graph)),
          _k_graph(std::move(k_graph)) {
}

A2Alg::A2Alg(const IGraphPtr &graph, int cluster_size) {
    _adjacency_matrix = (*graph).GetCopyOfAdjacencyMatrix();
    _matrix_size = (*graph).Size();
    _cluster_size = cluster_size;
    std::vector<std::vector<bool>> blank(_matrix_size, std::vector<bool>(_matrix_size));
    _m_graph = blank;
    _k_graph = blank;
}

void A2Alg::CreateMGraph() {
    std::vector<std::vector<bool>> k_graph(_matrix_size);
    std::vector<bool> vertecises_array(_matrix_size); // массив вершин, через который идёт заполнение k_graph-a
    for (auto &row: k_graph) {
        row = std::vector<bool>(_matrix_size, false);
    }

    // TODO: массивы надо аллоцировать по количеству вершин
    // проверяем, остались ли какие-то вершины, если нет то выходим из алгоритма

    while (checkPossibleContinue()) {
        //TODO: условие поправить
        std::cout << MatrixWriter::ToJson(_m_graph, "m_graph_at_start_iteration");
        std::cout << MatrixWriter::ToJson(_adjacency_matrix, "_adjacency_matrix_at_start_iteration");

        getNotPointedVertexIfPossible(vertecises_array);
        while (getClusterSize(vertecises_array) <= _cluster_size) {
            // проверяем  |K_i| < p
            if (findNeighbourVertex(vertecises_array)) {
                // ищем подходящих соседей
                addNeighbourVertexToKGraph(vertecises_array, k_graph); // дополняем кластерный граф
            } else {
                // нет подходящих соседей
                break;
            }
        }
        supplementMGraph(k_graph); // пополняем m graph
        cutKGraphFromAdjMatrix(k_graph, vertecises_array); // аккуратно удаляем i-й кластер
    }
}

void A2Alg::cutKGraphFromAdjMatrix(std::vector<std::vector<bool>> &k_graph, std::vector<bool> &vertecises_set) {
    std::vector<int> vertex_nums_in_k_graph;
    // копируем в массив номер вершин, только те, которые уже есть в рассмотрении

    getVectorVerNumsInKGraph(vertecises_set, vertex_nums_in_k_graph);

    //TODO: сделал дегенеративное решение, чтобы вырезать столбцы и строки, но ничего не могу поделать
    for (int i = 0; i < _matrix_size; i++) {
        for (int j = 0; j < _matrix_size; j++) {
            if (std::find(vertex_nums_in_k_graph.begin(), vertex_nums_in_k_graph.end(), j) !=
                vertex_nums_in_k_graph.end()) {
                k_graph[i][j] = false;
                _adjacency_matrix[i][j] = false;
            }
        }
    }

    for (int i = 0; i < _matrix_size; i++) {
        if (std::find(vertex_nums_in_k_graph.begin(), vertex_nums_in_k_graph.end(), i) !=
            vertex_nums_in_k_graph.end()) {
            for (int j = 0; j < _matrix_size; j++) {
                k_graph[i][j] = false;
                _adjacency_matrix[i][j] = false;
            }
        }
    }

    for (int i = 0; i < _matrix_size; i++) {
        if (vertecises_set[i]) { std::cout << i; }
        vertecises_set[i] = false;
    }
}

void A2Alg::supplementMGraph(std::vector<std::vector<bool>> &k_graph) {
    for (int i = 0; i < _matrix_size; i++) {
        for (int j = 0; j < _matrix_size; j++) {
            if (k_graph[i][j])
                _m_graph[i][j] = true;
        }
    }
}

std::vector<std::vector<bool>> A2Alg::GetCopyOfMGraph() const {
    return _m_graph;
}

/// <summary>
/// Проверяем матрицу на возможность работы с ней, суть такая, что в этой матрице не должно быть не отсмотренных рёбер
/// </summary>
/// <returns> true если с этим алгоритмом ещё можно работать</returns>
bool A2Alg::checkPossibleContinue() {
    for (int i = 0; i < _matrix_size; i++) {
        for (int j = 0; j < _matrix_size; j++) {
            if (_adjacency_matrix[i][j])
                return true;
        }
    }
    return false;
}

/// <summary>
/// Получить размер кластера, который рассматриваем в настоящий момент, 
/// </summary>
/// <param name="vertecises_set"></param>
/// <returns></returns>
int A2Alg::getClusterSize(std::vector<bool> &vertecises_set) {
    int count = 0;
    for (bool vertex: vertecises_set) {
        if (vertex) count++;
    }
    return count;
}

bool A2Alg::findNeighbourVertex(std::vector<bool> &vertecises_set) {

    for (int j = 0; j < _matrix_size; j++) {
        if (jVertexHasEdgesWithAllOtherVertexInKraph(j, vertecises_set)) {
            vertecises_set[j] = true; // поместили вершину, у которой с рассматриваемой есть общее ребро
            return true;
        }
    }
    return false;
}

void A2Alg::getVectorVerNumsInKGraph(std::vector<bool> &vertecises_set, std::vector<int> &vertex_nums_in_k_graph) {
    // копируем в массив номеров вершин, только те, которые уже есть в рассмотрении
    for (int i = 0; i < vertecises_set.size(); i++) {
        if (vertecises_set[i]) {
            vertex_nums_in_k_graph.push_back(i);
        }
    }
}

bool A2Alg::jVertexHasEdgesWithAllOtherVertexInKraph(int j, std::vector<bool> &vertecises_set) {
    std::vector<int> vertex_nums_in_k_graph;
    getVectorVerNumsInKGraph(vertecises_set, vertex_nums_in_k_graph);

    for (int k_graph_vertex_num: vertex_nums_in_k_graph) {
        if (!_adjacency_matrix[j][k_graph_vertex_num])
            return false;
    }
    // перебрали все вершина k-кластера
    return true;
}

/// <summary>
/// Добавляем вершины в k_graph, выпуская из прохода по матрице строки и столбцы, которые не отмечены как использованные в графе
/// </summary>
/// <param name="vertecises_set"></param>
/// <param name="k_graph"></param>
void
A2Alg::addNeighbourVertexToKGraph(std::vector<bool> &vertecises_set, std::vector<std::vector<bool>> &k_graph) const {
    for (int i = 0; i < _matrix_size; i++) {
        if (!vertecises_set[i]) { continue; }

        for (int j = 0; j < _matrix_size; j++) {
            if (!vertecises_set[j] || i == j) { continue; }
            k_graph[i][j] = true;
        }
    }
}

void A2Alg::getRandomVertexIfPossible(std::vector<bool> &vertecises_set) {
    std::mt19937 gen(1729);
    std::uniform_real_distribution<> distr(0, _matrix_size);
    vertecises_set[distr(gen)] = true;
}

void A2Alg::getNotPointedVertexIfPossible(std::vector<bool> &vertecises_set) {
    for (int i = 0; i < _matrix_size; i++) {
        for (int j = 0; j < _matrix_size; j++) {
            if (_adjacency_matrix[i][j]) {
                vertecises_set[i] = true;
                return;
            }
        }
    }
}


/*
bool isPossibleClusterGraph()
{
	//TODO: является маркированный граф, точками, парами,треугольниками или двумя связанными парами
	//TODO: либо через запрещённые пойти, есть ли тут треугольники с соплями, три связанных ребра, если то - то плохо

	for (int i = 0; i < _size; ++i)
	{
		int count_of_marked_edges = 0; // переменная, необходимая для исключения claw-графов
		for (int j = 0; j < _size; ++j)
		{
			if (_current_node_marked_matrix[i][j] == true)
			{
				count_of_marked_edges++;
			}
			if (count_of_marked_edges >= 3)
			{
				return false; // нашли подграф, в котором есть клешня, а это невозможный случай
			}
		}
	}

	// Нужен обход в ширину по матрице смежности, с поиском диаметра
	for (int i = 0; i < _size; ++i)
	{
		int diameter = 0; // переменная, необходимая для подсчёта диаметрка
		std::vector<int> vertices{};
		for (int j = i; j < _size; ++j)
		{
			if (_current_node_marked_matrix[i][j] == true)
			{
				diameter++;
				vertices.push_back(j);
			}
		}

		if (vertices.empty())
		{
			continue;
		}
		else
		{
			check_neighbours(diameter, vertices);
			if (diameter >= 3)
			{
				return false; // нашли цепь длины 3 или больше
			}
		}
	}
}

int checkNeighbours(int& diameter, std::vector<int> vertices)
{
	std::vector<int> new_neighbours{};
	for (int vertex : vertices)
	{
		for (int j = 0; j < _size; ++j)
		{
			if (_current_node_marked_matrix[vertex][j] == true)
			{
				diameter++;
				new_neighbours.push_back(j);
			}
		}
	}
	//TODO: скипать j-шку отсмотренную

	if (!vertices.empty())
		check_neighbours(diameter, new_neighbours);

	return diameter;
}
*/
