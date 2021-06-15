#pragma once

#include <memory>

/// <summary>
/// ��������� ��� ������ ������, �� ������ ������ ���������, ������ �������������, ��� ����� �� ������ �����
/// </summary>
class IGraphFactory {
public:
	virtual IGraphPtr CreateGraph(const unsigned size) = 0;
};
