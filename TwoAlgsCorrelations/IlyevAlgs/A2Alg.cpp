#include "A2Alg.h"

#include <iterator>
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
	std::vector<bool> vertecises_array{}; // ������ ������, ����� ������� ��� ���������� k_graph-a
	//
	// TODO:��� ���� ������������ �� ���������� ������
	// ���������, �������� �� �����-�� �������, ���� ��� �� ������� �� ���������
	getRandomVertexIfPossible(vertecises_array); //����� ������������ ������� � ���������� � � _k_graph
	while (checkPossibleContinue())
	{
		if (getClusterSize(vertecises_array) <= _cluster_size) // ���������  |K_i| < p  
		{
			if (findNeighbourVertex(vertecises_array)) // ���� ���������� �������
			{
				addNeighbourVertexToKGraph(vertecises_array, k_graph); // ��������� ���������� ����
			}
			else
			{
				// ��� ���������� �������
			}
		}
		supplementMGraph(k_graph); //��������� m graph
		cutKGraphFromAdjMatrix(); // ��������� ������� i-� �������
	}
}

void  A2Alg::supplementMGraph(std::vector<std::vector<bool>>& k_graph)
{
	for (int i = 0; i < _matrix_size; i++)
	{
		for (int j = 0; j < _matrix_size; j++)
		{
			if (k_graph[i][j] != false)
				_m_graph[i][j] = true;
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <returns> true ���� � ���� ���������� ��� ����� ��������</returns>
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

/// <summary>
/// �������� ������ ��������, ������� ������������� � ��������� ������, 
/// </summary>
/// <param name="vertecises_set"></param>
/// <returns></returns>
int A2Alg::getClusterSize(std::vector<bool>& vertecises_set)
{
	int count = 0;
	for (bool vertex : vertecises_set)
	{
		if (vertex) count++;
	}
	return count;
}

bool A2Alg::findNeighbourVertex(std::vector<bool>& vertecises_set)
{
	int vertex_num = 0;
	for (int i = 0; i < _matrix_size; i++)
	{
		if (vertecises_set[i])
		{
			vertex_num = i;
		}
	}

	for (int j = 0; j < _matrix_size; j++)
	{
		if (jVertexHasEdgesWithAllOtherVertexInKraph(j, vertecises_set))
		{
			vertecises_set[j] = true; // ��������� �������, � ������� � ��������������� ���� ����� �����
			return true;
		}
	}
	return false;
}

bool A2Alg::jVertexHasEdgesWithAllOtherVertexInKraph(int j, std::vector<bool>& vertecises_set)
{
	std::vector<int> vertex_nums_in_k_graph;
	// �������� � ������ ����� ������, ������ ��, ������� ��� ���� � ������������
	std::copy_if(vertecises_set.begin(), vertecises_set.end(), std::back_inserter(vertex_nums_in_k_graph), [](int i) {return i == true; });
	for (int k_graph_vertex_num : vertex_nums_in_k_graph)
	{
		if (_adjacency_matrix[j][k_graph_vertex_num] != true)
			return false;
	}
	// ��������� ��� ������� k-��������
	return true;
}

void A2Alg::addNeighbourVertexToKGraph(std::vector<bool>& vertecises_set, std::vector<std::vector<bool>>& k_graph)
{
	for (int i = 0; i < _matrix_size; i++)
	{
		if (!vertecises_set[i]) { continue; }

		for (int j = 0; j < _matrix_size; j++)
		{
			if (!vertecises_set[i] || i==j) { continue; }
			k_graph[i][j] = true;
		}
	}
}

void A2Alg::getRandomVertexIfPossible(std::vector<bool>& vertecises_set)
{
	std::mt19937 gen(1729);
	std::uniform_real_distribution<> distr(0, _matrix_size);
	vertecises_set[distr(gen)] = true;
}

bool isPossibleClusterGraph()
{
	//TODO: �������� ������������� ����, �������, ������,�������������� ��� ����� ���������� ������
	//TODO: ���� ����� ����������� �����, ���� �� ��� ������������ � �������, ��� ��������� �����, ���� �� - �� �����

	for (int i = 0; i < _size; ++i)
	{
		int count_of_marked_edges = 0; // ����������, ����������� ��� ���������� claw-������
		for (int j = 0; j < _size; ++j)
		{
			if (_current_node_marked_matrix[i][j] == true)
			{
				count_of_marked_edges++;
			}
			if (count_of_marked_edges >= 3)
			{
				return false; // ����� �������, � ������� ���� ������, � ��� ����������� ������
			}
		}
	}

	// ����� ����� � ������ �� ������� ���������, � ������� ��������
	for (int i = 0; i < _size; ++i)
	{
		int diameter = 0; // ����������, ����������� ��� �������� ���������
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
				return false; // ����� ���� ����� 3 ��� ������
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
	//TODO: ������� j-��� ������������

	if (!vertices.empty())
		check_neighbours(diameter, new_neighbours);

	return diameter;
}
