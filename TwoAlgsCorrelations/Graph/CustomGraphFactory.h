#pragma once


#include "Graph.h"
#include "IGraphFactory.h"
class CustomGraphFactory : IGraphFactory
{
	public:
		IGraphPtr CreateGraph(const unsigned size) override;
};