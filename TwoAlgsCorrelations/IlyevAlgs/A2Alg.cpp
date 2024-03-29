#include "A2Alg.h"

#include <iostream>
#include <iterator>
#include <ostream>
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

A2Alg::A2Alg(const IGraphPtr& graph, int cluster_size)
{
	_adjacency_matrix = (*graph).GetCopyOfAdjacencyMatrix();
	_matrix_size = (*graph).Size();
	_cluster_size = cluster_size;
	std::vector<std::vector<bool>> blank(_matrix_size, std::vector<bool>(_matrix_size));
	_m_graph = blank;
	_k_graph = blank;
}

void A2Alg::CreateMGraph()
{
	std::vector<std::vector<bool>> k_graph(_matrix_size);
	std::vector<bool> vertecises_array(_matrix_size); // ������ ������, ����� ������� ��� ���������� k_graph-a
	MatrixWriter* mw = new MatrixWriter();
	for (auto& row : k_graph)
	{
		row = std::vector<bool>(_matrix_size, false);
	}
	
	//
	// TODO: ������� ���� ������������ �� ���������� ������
	// ���������, �������� �� �����-�� �������, ���� ��� �� ������� �� ���������

	while (checkPossibleContinue()) //TODO: ������� ���������
	{
		std::cout << (*mw).ToJson(_m_graph, "m_graph_at_start_iteration");
		std::cout << (*mw).ToJson(_adjacency_matrix, "_adjacency_matrix_at_start_iteration");

		getNotPointedVertexIfPossible(vertecises_array);
		while (getClusterSize(vertecises_array) <= _cluster_size) // ���������  |K_i| < p  
		{
			if (findNeighbourVertex(vertecises_array)) // ���� ���������� �������
			{
				addNeighbourVertexToKGraph(vertecises_array, k_graph); // ��������� ���������� ����
			}
			else
			{
				// ��� ���������� �������
				break;
			}
		}
		supplementMGraph(k_graph); //��������� m graph
		cutKGraphFromAdjMatrix(k_graph, vertecises_array); // ��������� ������� i-� �������
	}
}

void A2Alg::cutKGraphFromAdjMatrix(std::vector<std::vector<bool>>& k_graph, std::vector<bool>& vertecises_set)
{
	std::vector<int> vertex_nums_in_k_graph;
	// �������� � ������ ����� ������, ������ ��, ������� ��� ���� � ������������

	getVectorVerNumsInKGraph(vertecises_set, vertex_nums_in_k_graph);


	//TODO: ������ �������������� �������, ����� �������� ������� � ������, �� ������ �� ���� ��������
	for (int i = 0; i < _matrix_size; i++)
	{
		for (int j = 0; j < _matrix_size; j++)
		{
			if (std::find(vertex_nums_in_k_graph.begin(), vertex_nums_in_k_graph.end(), j) != vertex_nums_in_k_graph.
				end())
			{
				k_graph[i][j] = false;
				_adjacency_matrix[i][j] = false;
			}
		}
	}

	for (int i = 0; i < _matrix_size; i++)
	{
		if (std::find(vertex_nums_in_k_graph.begin(), vertex_nums_in_k_graph.end(), i) != vertex_nums_in_k_graph.
			end())
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				k_graph[i][j] = false;
				_adjacency_matrix[i][j] = false;
			}
		}
	}

	for (int i = 0; i < _matrix_size; i++)
	{
		if (vertecises_set[i]) { std::cout << i; }
		vertecises_set[i] = false;
	}
}

void A2Alg::supplementMGraph(std::vector<std::vector<bool>>& k_graph)
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

std::vector<std::vector<bool>> A2Alg::GetCopyOfMGraph() const
{
	return _m_graph;
}


/// <summary>
/// ��������� ������� �� ����������� ������ � ���, ���� �����, ��� � ���� ������� �� ������ ���� �� ������������ ����
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
	return false;
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

void A2Alg::getVectorVerNumsInKGraph(std::vector<bool>& vertecises_set, std::vector<int>& vertex_nums_in_k_graph)
{
	// �������� � ������ ������� ������, ������ ��, ������� ��� ���� � ������������
	for (int i = 0; i < vertecises_set.size(); i++)
	{
		if (vertecises_set[i] == true)
		{
			vertex_nums_in_k_graph.push_back(i);
		}
	}
}

bool A2Alg::jVertexHasEdgesWithAllOtherVertexInKraph(int j, std::vector<bool>& vertecises_set)
{
	std::vector<int> vertex_nums_in_k_graph;
	getVectorVerNumsInKGraph(vertecises_set, vertex_nums_in_k_graph);

	for (int k_graph_vertex_num : vertex_nums_in_k_graph)
	{
		if (_adjacency_matrix[j][k_graph_vertex_num] != true)
			return false;
	}
	// ��������� ��� ������� k-��������
	return true;
}

/// <summary>
/// ��������� ������� � k_graph, �������� �� ������� �� ������� ������ � �������, ������� �� �������� ��� �������������� � �����
/// </summary>
/// <param name="vertecises_set"></param>
/// <param name="k_graph"></param>
void A2Alg::addNeighbourVertexToKGraph(std::vector<bool>& vertecises_set, std::vector<std::vector<bool>>& k_graph)
{
	for (int i = 0; i < _matrix_size; i++)
	{
		if (!vertecises_set[i]) { continue; }

		for (int j = 0; j < _matrix_size; j++)
		{
			if (!vertecises_set[j] || i == j) { continue; }
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

void A2Alg::getNotPointedVertexIfPossible(std::vector<bool>& vertecises_set)
{
	for (int i = 0; i < _matrix_size; i++)
	{
		for (int j = 0; j < _matrix_size; j++)
		{
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
*/
