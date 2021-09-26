#pragma once
#include <functional>

#include "BnBTreeNode.h"

struct MatrixCoordinate
{
	int i;
	int j;
};

/// <summary>
/// ����� ��� �������� ��������� � ������, � �������� �������� �� ������ ���
/// </summary>
class BranchAndBounds
{
	std::vector<std::vector<bool>> _marked_edges_ajacency_matrix{};
	std::vector<std::vector<bool>> _adjacency_matrix{};
	int _matrix_size = 0;
	int _general_best_distance = INT_MAX;

	BranchAndBounds(int size, const IGraphPtr& graph)
	{
		_adjacency_matrix = (*graph).GetCopyOfAdjacencyMatrix();
		_matrix_size = size;
		_general_best_distance = INT_MAX;
		for (int i = 0; i < size; i++)
		{
			_current_node_matches_matrix.push_back(std::vector<bool>(size));
		}
	}


	/// <summary>
	/// ����������� ����� �� ������ � ������� ��������� ������ � ������
	/// </summary>
	/// <param name="treeNode">�� ��������� �� ������� ������ ������� ���� ���������</param>
	/// <returns> ���������� ����� ������������ ������ ���������� �� ���� </returns>
	int CalculateTree(CalculatedTreeNode& treeNode)
	{
		if(_general_best_distance < (*treeNode).getCurrentDistance())
		{
			return _general_best_distance;
		}

		if ((*treeNode).checkEmpty()) // ��������� ������ ����
		{
			return _general_best_distance; // �� ���� �� ������ ���� ��������
		}

		if (!(*treeNode).isPossibleClusterGraph()) // �������� ��������, � ���������� ���� ������ �� ������ ��� ���, ����� �� ���� ����� ����
		{
			return _general_best_distance;
		}

		if ((*treeNode).checkFullMarking()) // ���� ��� ��� ��������� ����������� ����
		{
			//Todo: �������� � ������ ������� ���� ����
			auto current_distance = (*treeNode).getCurrentDistance();
			_general_best_distance = current_distance;
			return current_distance; // ��� ��� �������
		}


		// ����� ����� �� ��� �����, ��� �� ����� ����� ����������� ��������� �����, � � ������ ����� ��� ��������� �� �����,
		// �������� ������������� �������, �� ����, �������� � ���� ��� �� �������� ������������� �������, � �������� ����� ����������� ���������

		MatrixCoordinate next_edge = GetNextEdge(); // �������� ��������� �����, ������� ����� �����������, ���� �������

		// ������ ������� ��������� �� ����� � ����������� ����
		CalculatedTreeNode calculate_marked_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_marked_tree_node_copy.markEdge(next_edge); //  �������� ����� �����
		CalculateTree(calculate_marked_tree_node_copy);

		// ������ ������� ��������� �� ����� � ��������� �����
		CalculatedTreeNode calculate_reject_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_reject_tree_node_copy.markEdge(next_edge); //  ������� �����
		calculate_reject_tree_node_copy.incCurDistance();
		CalculateTree(calculate_reject_tree_node_copy);
	}

	MatrixCoordinate GetNextEdge()
	{
		std::vector<std::vector<bool>> unmarked_adjacency_matrix;
		int size = _marked_edges_ajacency_matrix.size();
		for (int i = 0; i < size; i++)
		{
			unmarked_adjacency_matrix.push_back(std::vector<bool>(size));
			//TODO: ����� ����� ��������, ��� ���������������� �������, ����� �� ��������� �������� ������
		}

		for (int i = 0; i < _matrix_size; i++)
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				if (!(_marked_edges_ajacency_matrix[i][j] && _adjacency_matrix[i][j]))
					unmarked_adjacency_matrix[i][j] = _adjacency_matrix[i][j];
			}
		}

		// TODO: �������� �� �������� ���� �������, ���� �������, �� �� ������ ���� ����

		for (int i = 0; i < _matrix_size; i++)
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				if (unmarked_adjacency_matrix[i][j] != false)
				{
					MatrixCoordinate matrix_coordinate{i, j};
					return matrix_coordinate;
				}
			}
		}

		// ���� ������, ������ ���� ��� ��� ���� ��������� � �� ������� ������� - ������
	}
};
