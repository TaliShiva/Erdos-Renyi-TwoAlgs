#include "CustomGraphFactory.h"


IGraphPtr CustomGraphFactory::CreateGraph(const unsigned size) {
	std::vector<std::vector<int>> adjacency_matrix(size);
	for (auto& row : adjacency_matrix)
	{
		row = std::vector<int>(size,-1);
	}

	/*
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
	*/
	adjacency_matrix[0][2] = 2;
	adjacency_matrix[0][3] = 3;
	adjacency_matrix[1][2] = 2;
	adjacency_matrix[2][3] = 3;

	adjacency_matrix[2][0] = 0;
	adjacency_matrix[3][0] = 0;
	adjacency_matrix[2][1] = 1;
	adjacency_matrix[3][2] = 2;

	return IGraphPtr(new Graph(adjacency_matrix));
}