#pragma once

#include <random>

#include "Graph.h"
#include "IGraphFactory.h"

/// <summary>
/// ‘абрика, создающа€ графы на основе модели ЁрдЄша-–еньи
/// </summary>
class RandomGraphFactory : IGraphFactory {
private:
    std::random_device rd_;
    std::default_random_engine gen_{rd_()};
    /// <summary>
    /// ‘ормирует равномерное распределение (каждое значение одинаково веро€тно)
    /// </summary>
    std::uniform_real_distribution<> dis_{0.0, 1.0};
    double density_; // плотность графа

public:
    explicit RandomGraphFactory(double density);

    IGraphPtr CreateGraph(unsigned size) override;
};
