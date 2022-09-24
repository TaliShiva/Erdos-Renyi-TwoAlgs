#pragma once

#include <memory>

/// <summary>
/// Интерфейс для фабрик графов, мы строим только случайные, однако подразумеваем, что можем не только такие
/// </summary>
class IGraphFactory {
public:
    virtual IGraphPtr CreateGraph(unsigned size) = 0;
};
