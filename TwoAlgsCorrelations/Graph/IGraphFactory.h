#pragma once

#include <memory>

/// <summary>
/// ��������� ��� ������ ������, �� ������ ������ ���������, ������ �������������, ��� ����� �� ������ �����
/// </summary>
class IGraphFactory {
public:
    virtual IGraphPtr CreateGraph(unsigned size) = 0;
};
