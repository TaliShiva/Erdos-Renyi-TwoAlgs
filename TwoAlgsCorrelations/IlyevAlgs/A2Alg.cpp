#include "A2Alg.h"


A2Alg::A2Alg(const std::vector<std::vector<bool>>& adjacency_matrix, int matrix_size, int cluster_size,
	const std::vector<std::vector<bool>>& m_graph)
	: _adjacency_matrix(adjacency_matrix),
	_matrix_size(matrix_size),
	_cluster_size(cluster_size),
	_m_graph(m_graph)
{
}

void A2Alg::startCreateCluster()
{
	getRandomVertex(); //����� ������������ ������� � ���������� � � _k_graph

 
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