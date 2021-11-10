#pragma once
#include <vector>

// TODO: нужен тип для матриц, и тогда они все будут _adjacency_matrix  и я их буду уже специализировать

class A2Alg
{
	std::vector<std::vector<bool>> _adjacency_matrix{};

	int _matrix_size = 0;
	int _cluster_size = 0; // p из алгоритма А2

	std::vector<std::vector<bool>> _m_graph{}; //TODO: надо ли мне для алгоритма хранить отдельно вершины как-то
	// при этом отдельно исходные и итоговоый M граф

};

