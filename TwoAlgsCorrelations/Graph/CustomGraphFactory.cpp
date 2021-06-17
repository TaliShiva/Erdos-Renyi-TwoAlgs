#include "CustomGraphFactory.h"


IGraphPtr CustomGraphFactory::CreateGraph(const unsigned size) {
	std::vector<std::vector<bool>> adjacency_matrix(6);
	for (auto& row : adjacency_matrix)
	{
		row = std::vector<bool>(6);
	}

	adjacency_matrix[0][3] = true;
	adjacency_matrix[0][4] = true;
	adjacency_matrix[1][3] = true;
	adjacency_matrix[1][4] = true;
	adjacency_matrix[1][5] = true;
	adjacency_matrix[2][5] = true;
	
	adjacency_matrix[3][0] = true;
	adjacency_matrix[4][0] = true;
	adjacency_matrix[3][1] = true;
	adjacency_matrix[4][1] = true;
	adjacency_matrix[5][1] = true;
	adjacency_matrix[5][2] = true;

	return IGraphPtr(new Graph(adjacency_matrix));
}