#pragma once
#include <functional>

#include "BnBTreeNode.h"

struct MatrixCoordinate
{
	int i;
	int j;
};

/// <summary>
/// Класс для рассчёта кластеров в графах, с размером кластера не больше трёх 
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


	/// Рекурсивный спуск по дереву к листьям алгоритма ветвей и границ
	///
	/// по симуляции мы передаём внутрь текущую ноду симуляции
	/// Возвращаем число обозначающее лучшее расстоения из ноды 
	int CalculateTree(CalculatedTreeNode& treeNode)
	{
		if(_general_best_distance < (*treeNode).getCurrentDistance())
		{
			return _general_best_distance;
		}

		if ((*treeNode).checkEmpty()) // ïîëó÷èëñÿ ïóñòîé ãðàô
		{
			return _general_best_distance; // ïî èäåå íå äîëæíû ñþäà ïîïàäàòü
		}

		if (!(*treeNode).isPossibleClusterGraph()) // Проверка ситуаций, в допустимую ноду дерева мы попали или нет, может ли быть такой граф
		{
			return _general_best_distance;
		}

		if ((*treeNode).checkFullMarking()) // åñëè ýòî óæå ïîëíîñòüþ ðàçìå÷åííûé ãðàô
		{
			//Todo: äîáàâèòü â ñïèñîê ðåøåíèé ýòîò ãðàô
			auto current_distance = (*treeNode).getCurrentDistance();
			_general_best_distance = current_distance;
			return current_distance; // Âîò îíî ðåøåíèå
		}


		// иначе делим на две ветки, где по одной ветке маркируется выбранное ребро, а в другой ветке оно удаляется из графа,
		// проверка маркированной матрицы, по идее, включает в себя как от просмотр маркированной матрицы, а удаление ребра увеличивает дистанцию 

		MatrixCoordinate next_edge = GetNextEdge(); // ïîëó÷àåì ñëåäóþùåå ðåáðî, êîòîðîå áóäåò ìàðêèðîâàíî, ëèáî óäàëåíî

		// сперва проведём симуляцию по ветке с маркировкой рёбер 
		CalculatedTreeNode calculate_marked_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_marked_tree_node_copy.markEdge(next_edge); //  отмечаем новое ребро 
		CalculateTree(calculate_marked_tree_node_copy);

		// теперь проведём симуляцию по ветке с удалением ребра 
		CalculatedTreeNode calculate_reject_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_reject_tree_node_copy.markEdge(next_edge); //  удаляем ребро 
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
			//TODO: можно будет подумать, как переиспользовать матрицу, чтобы не создавать ненужный объект 
		}

		for (int i = 0; i < _matrix_size; i++)
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				if (!(_marked_edges_ajacency_matrix[i][j] && _adjacency_matrix[i][j]))
					unmarked_adjacency_matrix[i][j] = _adjacency_matrix[i][j];
			}
		}

		// TODO: проверка на нулёвость этой матрицы, если нулевая, то мы обошли весь граф 

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

		// сюда попадём, только если уже все рёбра перебрали и не нулевая матрица - ошибка 
	}
};
