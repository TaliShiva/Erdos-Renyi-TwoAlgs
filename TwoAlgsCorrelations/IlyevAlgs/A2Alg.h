#pragma once
#include <vector>

// TODO: нужен тип для матриц, и тогда они все будут _adjacency_matrix  и я их буду уже специализировать

class A2Alg
{
	std::vector<std::vector<bool>> _adjacency_matrix{};

	int _matrix_size = 0;
	int _cluster_size = 0; // p из алгоритма А2

	std::vector<std::vector<bool>> _m_graph{};
	std::vector<std::vector<bool>> _k_graph{};

	
public:
	A2Alg(const std::vector<std::vector<bool>>& adjacency_matrix, int matrix_size, int cluster_size,
	      const std::vector<std::vector<bool>>& m_graph, const std::vector<std::vector<bool>>& k_graph);

	void startCreateCluster(); // начинаем построение кластера - шаг 2 и 3 по сути
	void supplementMGraph(std::vector<std::vector<bool>>& k_graph);


	int getNeighbourIndex(); // получаем номер соседней вершины


	bool isPossibleClusterGraph();

	int checkNeighbours(int& diameter, std::vector<int> vertices);
private:
	bool checkPossibleContinue(); // проверка матрицы на пустоту - условие выхода из алгоритма
	int getClusterSize(std::vector<bool>& vertecises_set);
	bool findNeighbourVertex(std::vector<bool>& vertecises_array);
	bool jVertexHasEdgesWithAllOtherVertexInKraph(int j, std::vector<bool>& vertecises_set);
	void addNeighbourVertexToKGraph(std::vector<bool>& vertecises_set, std::vector<std::vector<bool>>& k_graph);
	bool notEqual();
	void getRandomVertexIfPossible(std::vector<bool>& vertecises_set);
};
