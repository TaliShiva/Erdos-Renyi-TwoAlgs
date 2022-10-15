#pragma once

#include <random>

#include "Graph.h"
#include "IGraphFactory.h"

/// <summary>
/// Фабрика, создающая графы на основе модели Эрдёша-Реньи
/// </summary>
class RandomGraphFactory {
private:

public:
    static IGraphPtr CreateGraph(unsigned size);
};
