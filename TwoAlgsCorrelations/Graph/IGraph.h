#pragma once

#include <memory>
#include <string>
#include <vector>

class IGraph
{
public:
	/// <summary>
	/// �������� �� ��, ��������� �� �����-�� ��� �������
	/// </summary>
	virtual bool IsJoined(unsigned i, unsigned j) const = 0;
	virtual ~IGraph() = default;
	/// <summary>
	/// ������ ����� ����������
	/// </summary>
	virtual unsigned Size() const = 0;

	virtual std::string ToJson() const = 0;

	virtual std::vector<short> GetNeighbours(short i) = 0;

	virtual int GetRoot() const = 0;

	virtual std::vector<std::vector<bool>> GetCopyOfAdjacencyMatrix() const = 0;
};

using IGraphPtr = std::shared_ptr<IGraph>;

