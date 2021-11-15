#include "A2Alg.h"

#include <random>


A2Alg::A2Alg(const std::vector<std::vector<bool>>& adjacency_matrix, int matrix_size, int cluster_size,
             const std::vector<std::vector<bool>>& m_graph, const std::vector<std::vector<bool>>& k_graph)
	: _adjacency_matrix(adjacency_matrix),
	  _matrix_size(matrix_size),
	  _cluster_size(cluster_size),
	  _m_graph(m_graph),
	  _k_graph(k_graph)
{
}

void A2Alg::startCreateCluster()
{
	std::vector<std::vector<bool>> k_graph{};
	std::vector<bool> vertecises_array{}; // массив вершин, через который идёт заполнение k_graph-a
	// проверяем, остались ли какие-то вершины, если нет то выходим из алгоритма
	getRandomVertexIfPossible(vertecises_array); //выбор произвольной вершины и добавление её в _k_graph
	while (checkPossibleContinue())
	{
		if (getClusterSize() < p) // проверяем  |K_i| < p  
		{
			if (findNeighbourVertex()) // ищем подходящих соседей
			{
				addNeighbourVertex(); // дополняем кластерный граф
			}
		}
		supplementMGraph(); //пополняем m graph
		cutKGraphFromAdjMatrix(); // аккуратно удаляем i-й кластер
	}
}

/// <summary>
/// 
/// </summary>
/// <returns> true если с этим алгоритмом ещё можно работать</returns>
bool A2Alg::checkPossibleContinue()
{
	for (int i = 0; i < _matrix_size; i++)
	{
		for (int j = 0; j < _matrix_size; j++)
		{
			if (_adjacency_matrix[i][j] != false)
				return true;
		}
	}
}

void A2Alg::getRandomVertexIfPossible(std::vector<bool> & vertecises_set)
{
	std::mt19937 gen(1729);
	std::uniform_real_distribution<> distr(0, _matrix_size);
	vertecises_set[distr(gen)] = true;
}

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
