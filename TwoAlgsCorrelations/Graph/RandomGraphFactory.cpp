#include "RandomGraphFactory.h"

RandomGraphFactory::RandomGraphFactory(const double density) : density_(density){}

IGraphPtr RandomGraphFactory::CreateGraph(const unsigned size) {
	std::vector<std::vector<int>> adjacency_matrix(size);
	for (auto &row : adjacency_matrix)
	{
		row = std::vector<int>(size);
	}

	for (unsigned long i = 0; i < size; i++) {
		for (unsigned long j = 0; j < i; j++) {
			if (dis_(gen_) < density_) {
				/*adjacency_matrix[i][j] = adjacency_matrix[j][i] = true;*/
				adjacency_matrix[i][j] = j; //TODO: Доработка
			}
		}
	}
	return IGraphPtr(new Graph(adjacency_matrix));
}