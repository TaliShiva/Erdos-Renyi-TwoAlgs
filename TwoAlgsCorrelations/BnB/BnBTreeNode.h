#pragma once
#include <list>
#include <set>
#include <vector>

#include "BnB.h"
#include "IGraph.h"
#include "MatrixCoordinate.h"

/// <summary>
	/// �����, ��� �������� ��������� ����� � ���� ������ ���������
	/// </summary>
class CalculatedTreeNode
{
	int _best_distance = 0;
	int _current_distance = 0;
	int _matrix_size = 0;
public:
	std::vector<std::vector<bool>> _current_node_adjacency_matrix{};
	std::vector<std::vector<bool>> _current_node_marked_matrix{};

	CalculatedTreeNode(int size)
	{
		for (int i = 0; i < size; i++)
		{
			_current_node_adjacency_matrix.emplace_back(size);
			_current_node_marked_matrix.emplace_back(size);
		}
		_best_distance = 0;
		_current_distance = 0;
		_matrix_size = size;
	}

	CalculatedTreeNode(std::vector<std::vector<bool>>& _adjacency_matrix,
	                   std::vector<std::vector<bool>>& _marked_edges_ajacency_matrix, int matrix_size) :
		_current_node_adjacency_matrix(_adjacency_matrix),
		_current_node_marked_matrix(_marked_edges_ajacency_matrix),
		_matrix_size(matrix_size)
	{
	}

	CalculatedTreeNode(CalculatedTreeNode& treeNode, int bestDistance) :
		_current_node_adjacency_matrix(treeNode._current_node_adjacency_matrix),
		_current_node_marked_matrix(treeNode._current_node_marked_matrix),
		_best_distance(bestDistance),
		_matrix_size(treeNode._matrix_size),
		_current_distance(treeNode._current_distance)
	{
	}

	/// <summary>
	/// ������� ���������� ����� ����������� ������ � ������ � ����
	/// </summary>
	/// <returns> ���������� ���������� ����� ������� � ���������� ��������� ���� </returns>
	int calculateDistance(const IGraphPtr& graph)
	{
		const auto graph_size = (*graph).Size();

		int distance = 0; // 

		for (int i = 0; i < graph_size; ++i)
		{
			for (int j = i; j < graph_size; ++j)
			{
				if (((*graph).IsJoined(i, j) && _current_node_adjacency_matrix[i][j]) == false)
				{
					distance++;
				}
			}
		}

		return distance;
	}

	/// <summary>
	/// �������� ����� �� �������
	/// </summary>
	/// <returns></returns>
	bool checkEmptySubGraph()
	{
		for (int i = 0; i < _matrix_size; ++i)
		{
			for (int j = i; j < _matrix_size; ++j)
			{
				if (_current_node_adjacency_matrix[i][j] == true)
				{
					return false;
				}
			}
		}
		return true;
	}


	/// <summary>
	/// ��������, ��� �� ���� � ����� ��� �����������
	/// </summary>
	/// <returns> true - ���� ��� ����� �������, false � �������� ������ </returns>
	bool checkFullMarking()
	{
		for (int i = 0; i < _matrix_size; ++i)
		{
			for (int j = i; j < _matrix_size; ++j)
			{
				if (_current_node_adjacency_matrix[i][j] != _current_node_marked_matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool isPossibleClusterGraph(bool isResultedGraph)
	{
		// �������� � ������ ����� ������, ������ ��, ������� ��� ���� � ������������

		std::set<int> checked_vertesises{};
		for (int i = 0; i < _matrix_size; ++i)
		{
			if (checked_vertesises.find(i) != checked_vertesises.end()) continue;
			for (int j = i; j < _matrix_size; ++j)
			{
				if (checked_vertesises.find(j) != checked_vertesises.end()) continue;
				if (_current_node_marked_matrix[i][j])
				{
					if (!is_cluster(checked_vertesises, i, isResultedGraph)) return false;
					//���� ������������� ������������� ������� ���������� �������
				}
			}
		}

		return true;
	}

	bool is_cluster(std::set<int>& checked_vertesises, int i, bool isResultedGraph)
	{
		// ������ �������� ������ ��������� ������
		std::set<int> visited{};
		std::set<int> neighbours{};
		visited.insert(i);
		for (int j = 0; j < _matrix_size; j++)
		{
			if (_current_node_marked_matrix[i][j] == true)
			{
				neighbours.insert(j);
			}
		}
		// ������ ������ ��������

		while (!neighbours.empty())
		{
			int neighbour = *neighbours.begin();
			visited.insert(neighbour);
			for (int j = 0; j < _matrix_size; j++)
			{
				if (visited.find(j) != visited.end()) continue;
				if (_current_node_marked_matrix[neighbour][j] == true)
				{
					neighbours.insert(j);
				}
			}
			neighbours.erase(neighbour);
		}
		// �� ���� ������� � ��� ���� ���� ��������� ������

		// ��������� ���������� ������, ���� ��� ������ ������� ��������������� �������� - �� �� ��, �������� � ������ ������������� ���� � �������
		if (!isResultedGraph)
		{
			if (visited.size() <= 3)
				return true; // ���� ��� ��������
		}
		// �����, ��������� �� ����� ������ ���������� �� ����� ������-�� ������� ��� ���
		for (int vertex_num : visited)
			if (!VertexHasEdgesWithAllOtherVertexInCluster(vertex_num, visited))
			{
				return false;
			}
		// �� ������ �������� � checked_vertex ������ ������
		checked_vertesises = visited;
		return true;
	}

	bool VertexHasEdgesWithAllOtherVertexInCluster(int j, std::set<int>& vertecises_set)
	{
		for (int vertex_num : vertecises_set)
		{
			if (vertex_num == j) continue;
			if (_current_node_marked_matrix[j][vertex_num] != true)
				return false;
		}
		// ��������� ��� ������� k-��������
		return true;
	}

	/// <summary>
	/// �������� �����
	/// </summary>
	void markEdge(MatrixCoordinate matrix_coordinate)
	{
		_current_node_marked_matrix[matrix_coordinate.i][matrix_coordinate.j] = true;
		_current_node_marked_matrix[matrix_coordinate.j][matrix_coordinate.i] = true;
	}

	void incCurDistance()
	{
		_current_distance++;
	}

	void rejectEdge(MatrixCoordinate matrix_coordinate)
	{
		_current_node_adjacency_matrix[matrix_coordinate.i][matrix_coordinate.j] = false;
		_current_node_adjacency_matrix[matrix_coordinate.j][matrix_coordinate.i] = false;
	}

	bool isMayBeTriangle(const int i_1, const int j_1, const int i_2, const int j_2)
	{
		if (_current_node_adjacency_matrix[i_1][j_2] != 0) return true;
		return false;
	}

	int getCurrentDistance()
	{
		return _current_distance;
	}
};
