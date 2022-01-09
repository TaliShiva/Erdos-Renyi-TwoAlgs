#pragma once


#include "Graph.h"
#include "IGraphFactory.h"

class CustomGraphFactory
{
private:
	static void adjMatrixInit(int size, std::vector<std::vector<bool>>& adjacency_matrix);
public:
	static IGraphPtr CreateHouseGraph();
	static IGraphPtr CreateSquareWithShortChain();
	static IGraphPtr CreateDiamondGraph();
	static int GetGraphSize();
};
