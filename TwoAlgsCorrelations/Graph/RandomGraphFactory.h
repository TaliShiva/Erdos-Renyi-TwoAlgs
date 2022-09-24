#pragma once

#include <random>

#include "Graph.h"
#include "IGraphFactory.h"

/// <summary>
/// Фабрика, создающая графы на основе модели Эрдёша-Реньи
/// </summary>
class RandomGraphFactory : IGraphFactory {
private:
    std::random_device rd_;
    std::default_random_engine gen_{rd_()};
    /// <summary>
    /// Формирует равномерное распределение (каждое значение одинаково вероятно)
    /// </summary>
    std::uniform_real_distribution<> dis_{0.0, 1.0};
    double density_; // плотность графа

public:
    explicit RandomGraphFactory(double density);

    IGraphPtr CreateGraph(unsigned size) override;
};
