#include "RandomGraphFactory.h"

IGraphPtr RandomGraphFactory::CreateGraph(const unsigned size) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double density = 0.5; // плотность графа

    std::vector<std::vector<bool>> adjacency_matrix(size);
    for (auto &row: adjacency_matrix) {
        row = std::vector<bool>(size);
    }

    for (unsigned long i = 0; i < size; i++) {
        for (unsigned long j = 0; j < i; j++) {
            if (dis(gen) < density) {
                adjacency_matrix[i][j] = adjacency_matrix[j][i] = true;
                //adjacency_matrix[i][j] = j; //TODO: Доработка
            }
        }
    }
    return IGraphPtr(new Graph(adjacency_matrix));
}
