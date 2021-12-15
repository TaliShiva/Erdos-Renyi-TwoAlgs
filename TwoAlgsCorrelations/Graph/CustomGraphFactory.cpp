#include "CustomGraphFactory.h"


IGraphPtr CustomGraphFactory::CreateGraph(const unsigned size)
{
	std::vector<std::vector<bool>> adjacency_matrix(size);
	for (auto& row : adjacency_matrix)
	{
		row = std::vector<bool>(size, false);
	}
	// 5 вершинный граф домик
	/*adjacency_matrix[0][1] = true;
	adjacency_matrix[0][4] = true;
	adjacency_matrix[1][0] = true;
	adjacency_matrix[1][2] = true;
	adjacency_matrix[1][4] = true;
	adjacency_matrix[2][1] = true;
	adjacency_matrix[2][3] = true;
	adjacency_matrix[3][2] = true;
	adjacency_matrix[3][4] = true;
	adjacency_matrix[4][0] = true;
	adjacency_matrix[4][1] = true;
	adjacency_matrix[4][3] = true;*/

	// 6-вершинный: квадрат и цепочка из двух звеньев
	/*adjacency_matrix[0][3] = true;
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
	adjacency_matrix[5][2] = true;*/


	// 4 вершинный алмаз
	adjacency_matrix[0][1] = true;
	adjacency_matrix[0][2] = true;
	adjacency_matrix[0][3] = true;

	adjacency_matrix[1][0] = true;
	adjacency_matrix[1][2] = true;
	
	adjacency_matrix[2][0] = true;
	adjacency_matrix[2][1] = true;
	adjacency_matrix[2][3] = true;

	adjacency_matrix[3][0] = true;
	adjacency_matrix[3][2] = true;
	
	return IGraphPtr(new Graph(adjacency_matrix));
}
