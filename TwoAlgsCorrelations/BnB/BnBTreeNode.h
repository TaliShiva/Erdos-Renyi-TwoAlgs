#pragma once
#include <vector>

#include "BnB.h"
#include "IGraph.h"
#include "MatrixCoordinate.h"

/// <summary>
	/// �����, ��� �������� ��������� ����� � ���� ������ ���������
	/// </summary>
class CalculatedTreeNode
{
	std::vector<std::vector<bool>> _current_node_adjacency_matrix{};
	std::vector<std::vector<bool>> _current_node_marked_matrix{};
	int _best_distance = 0;
	int _current_distance = 0;
	int _matrix_size = 0;
public:
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

	CalculatedTreeNode(std::vector<std::vector<bool>>& _adjacency_matrix, std::vector<std::vector<bool>>& _marked_edges_ajacency_matrix, int matrix_size) :
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


	bool checkClawGraph(bool& value)
	{
		for (int i = 0; i < _matrix_size; ++i)
		{
			int count_of_marked_edges = 0; // ����������, ����������� ��� ���������� claw-������
			for (int j = 0; j < _matrix_size; ++j)
			{
				if (_current_node_marked_matrix[i][j] == true)
				{
					count_of_marked_edges++;
				}
				if (count_of_marked_edges >= 3)
				{
					value = false;
					return true; // ����� �������, � ������� ���� ������, � ��� ����������� ������
				}
			}
		}
		return false;
	}

	bool isPossibleClusterGraph()
	{
		//TODO: �������� ������������� ����, �������, ������,�������������� ��� ����� ���������� ������
		//TODO: ���� ����� ����������� �����, ���� �� ��� ������������ � �������, ��� ��������� �����, ���� ���� - �� �����

		bool value;
		if (checkClawGraph(value)) return value;

		// ����� ����� � ������ �� ������� ���������, � ������� ��������
		for (int i = 0; i < _matrix_size; ++i)
		{
			int diameter = 0; // ����������, ����������� ��� �������� ���������
			std::vector<int> vertices{};
			for (int j = i; j < _matrix_size; ++j)
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
				if(diameter>=3)
				{
					return false; // ����� ���� ����� 3 ��� ������
				}
			}
		}
	}

	int check_neighbours(int& diameter, std::vector<int>& vertices)
	{
		std::vector<int> new_neighbours{};
		for (int vertex : vertices)
		{
			for (int j = 0; j < _matrix_size; ++j)
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
