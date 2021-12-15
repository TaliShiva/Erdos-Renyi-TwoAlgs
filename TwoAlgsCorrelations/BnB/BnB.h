#pragma once
#include <functional>
#include <string>
#include "BnBTreeNode.h"
#include "MatrixCoordinate.h"
#include "../Common/MatrixWriter.h"


/// <summary>
/// Класс для рассчёта кластеров в графах, с размером кластера не больше трёх 
/// </summary>
class BranchAndBounds
{
	std::vector<std::vector<bool>> _marked_edges_ajacency_matrix{};
	std::vector<std::vector<bool>> _adjacency_matrix{};
	int _matrix_size = 0;
	int _general_best_distance = INT_MAX;
	MatrixWriter* _mw;
	int _step = 0;
	std::vector<std::vector<std::vector<bool>>> _answers{};
public:
	BranchAndBounds(int size, const IGraphPtr& graph)
	{
		_adjacency_matrix = (*graph).GetCopyOfAdjacencyMatrix();
		_matrix_size = size;
		_general_best_distance = INT_MAX;
		std::vector<std::vector<bool>> blank(_matrix_size, std::vector<bool>(_matrix_size));
		_marked_edges_ajacency_matrix = blank;

		_mw = new MatrixWriter();
	}

	void startCalclulating()
	{
		CalculatedTreeNode startTreeNode = CalculatedTreeNode(_adjacency_matrix, _marked_edges_ajacency_matrix,
		                                                      _matrix_size);
		CalculateTree(startTreeNode);
		
		std::cout << _general_best_distance;
		for(int i = 0; i < _answers.size(); i++)
		{
			std::cout << (*_mw).ToJson(_answers[i], "result") << std::endl;
		}
	}

	~BranchAndBounds()
	{
		delete _mw;
	}

	/// <summary>
	/// Рекурсивный спуск по дереву к листьям алгоритма ветвей и границ
	/// по симуляции мы передаём внутрь текущую ноду симуляции
	/// Возвращаем число обозначающее лучшее расстоения из ноды
	/// </summary>
	/// <param name="treeNode"></param>
	/// <returns></returns>
	int CalculateTree(CalculatedTreeNode& treeNode)
	{
		std::cout << "step " <<  _step << std::endl;
		_step++;
		std::cout << (*_mw).ToJson(treeNode._current_node_marked_matrix, "_current_node_marked_matrix") << std::endl;
		std::cout << (*_mw).ToJson(treeNode._current_node_adjacency_matrix, "_current_node_adjacency_matrix") << std::endl;
		std::cout << "_general_best_distance " << _general_best_distance << std::endl;
		std::cout << "_current_node_adjacency_matrix " << treeNode.getCurrentDistance() << std::endl;
		if (_general_best_distance < (treeNode).getCurrentDistance())
		{
			return _general_best_distance;
		}

		if (treeNode.checkEmptySubGraph()) // получился пустой граф 
		{
			return _general_best_distance; // по идее не должны сюда попадать 
		}

		if (treeNode.checkFullMarking()) // если это уже полностью размеченный граф 
		{
			if (!treeNode.isPossibleClusterGraph(true)) // ситуация, в которой финальный граф оказался не корректным
			{
				return _general_best_distance;
			}
			//Todo: добавить проверку итогового графа
			auto current_distance = treeNode.getCurrentDistance();
			_general_best_distance = current_distance;
			_answers.push_back(treeNode._current_node_marked_matrix);
			return current_distance; // вот оно решение
		}

		if (!treeNode.isPossibleClusterGraph(false))
			// Проверка ситуаций, в допустимую ноду дерева мы попали или нет, может ли быть такой граф
		{
			return _general_best_distance;
		}

		
		


		// иначе делим на две ветки, где по одной ветке маркируется выбранное ребро, а в другой ветке оно удаляется из графа,
		// проверка маркированной матрицы, по идее, включает в себя просмотр маркированной матрицы, а удаление ребра увеличивает дистанцию 

		MatrixCoordinate next_edge = GetNextEdge(treeNode);
		// получаем следующее ребро, которое будет маркировано, либо удалено 

		// сперва проведём симуляцию по ветке с маркировкой рёбер 
		CalculatedTreeNode calculate_marked_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_marked_tree_node_copy.markEdge(next_edge); //  отмечаем новое ребро 
		CalculateTree(calculate_marked_tree_node_copy);

		// теперь проведём симуляцию по ветке с удалением ребра 
		CalculatedTreeNode calculate_reject_tree_node_copy = CalculatedTreeNode(treeNode, _general_best_distance);
		calculate_reject_tree_node_copy.rejectEdge(next_edge); //  удаляем ребро 
		calculate_reject_tree_node_copy.incCurDistance();
		CalculateTree(calculate_reject_tree_node_copy);
	}

	MatrixCoordinate GetNextEdge(CalculatedTreeNode& treeNode)
	{
		std::vector<std::vector<bool>> unmarked_adjacency_matrix;
		int size = treeNode._current_node_adjacency_matrix.size();
		for (int i = 0; i < size; i++)
		{
			unmarked_adjacency_matrix.push_back(std::vector<bool>(size));
			//TODO: можно будет подумать, как переиспользовать матрицу, чтобы не создавать ненужный объект
			// Создаём сразу в конструкторе и когда помечаем, перегрузив оператор - вычитаем из ajacency маркированную
		}

		//todo: вынести в оператор [-]
		for (int i = 0; i < _matrix_size; i++)
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				if (!treeNode._current_node_marked_matrix[i][j])
					unmarked_adjacency_matrix[i][j] = treeNode._current_node_adjacency_matrix[i][j];
			}
		}

		// TODO: проверка на нулёвость этой матрицы, если нулевая, то мы обошли весь граф 

		for (int i = 0; i < _matrix_size; i++)
		{
			for (int j = 0; j < _matrix_size; j++)
			{
				if (unmarked_adjacency_matrix[i][j] != false)
				{
					const MatrixCoordinate matrix_coordinate{i, j};
					return matrix_coordinate;
				}
			}
		}

		// сюда попадём, только если уже все рёбра перебрали и не нулевая матрица - ошибка 
	}
};
