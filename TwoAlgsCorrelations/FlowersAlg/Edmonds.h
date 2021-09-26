#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include "IGraph.h"


class CalculatedTreeNode;

class Edmonds
{
public:
	std::vector<std::vector<bool>> _matches_matrix{};
	std::vector<int> _base{};
	std::vector<bool> _match = {};
	std::vector<int> p = {};

	Edmonds(int size)
	{
		for (int i = 0; i < size; i++)
		{
			_matches_matrix.push_back(std::vector<bool>(size));
		}
	}

	/*std::vector<std::pair<int, int>> BipartiteMatching(const IGraphPtr& graph) {
		std::vector<short> partner{};

	};*/

	/// <summary>
	/// ������������, ��� �������� �������� � ���������� ������ � ������� ������ ��� ���� ��� �������������
	/// </summary>
	/*void KhunAlgorithm(const IGraphPtr& graph, const int firstGraphFraction, const int secondGraphFraction)
	{
		auto graph_size = (*graph).Size();
		if ((*graph).Size() % 2 == 1)
		{
			std::cerr << "This graph not biparticipate";
			throw exception("This graph not biparticipate");
		}
	}

	int FindAugmentPath(const IGraphPtr& graph)
	{
		std::vector<bool> used_vertexes = {}; // ������ ��� �������������� ������
		std::vector<bool> used_odd_vertexes = {}; // ������ ��� ������������� �������� ������
		std::vector<int> base = {};
		std::vector<int> q = {};

		auto graph_size = (*graph).Size();
		//int n; ������� ����� ��������, ��� �����
		//int MAXN = 6; ���� �� ���, ����������� ��������� ������ �����
		//vector<int> g[MAXN];
		//int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
		//bool used[MAXN], blossom[MAXN];

		for (int i = 0; i < graph_size; ++i)
			base[i] = i;

		int root = (*graph).GetRoot();
		used_vertexes[root] = true;
		int qh = 0, qt = 0; // �����-�� ��������� ��������
		q[qt++] = root; //

		while (qh < qt)
		{
			int v = q[qh++];
			for (size_t i = 0; i < g[v].size(); ++i)
			{
				int to = g[v][i];
				if (base[v] == base[to] || match[v] == to) continue;
				if (to == root || match[to] != -1 && p[match[to]] != -1)
				{
					int curbase = FlowerCompressor(v, to);
					memset(blossom, 0, sizeof blossom);
					mark_path(v, curbase, to);
					mark_path(to, curbase, v);
					for (int i = 0; i < n; ++i)
						if (blossom[base[i]])
						{
							base[i] = curbase;
							if (!used[i])
							{
								used[i] = true;
								q[qt++] = i;
							}
						}
				}
				else if (p[to] == -1)
				{
					p[to] = v;
					if (match[to] == -1)
						return to;
					to = match[to];
					used[to] = true;
					q[qt++] = to;
				}
			}
		}
		return -1;
	}

	/// <summary>
	/// ������� ������� ������
	///
	/// </summary>
	/// <param name="a">������ ������� � � �������� �����, �� ������� ����� ������</param>
	/// <param name="b">������ ������� b � �������� �����, ������� �������� root ��� ����������� � ������������� � ������ ����� </param>
	/// <returns>�������� �������, ����� ������</returns>
	int FlowerCompressor(int a, int b)
	{
		std::vector<int> used = {};
		// ����������� �� ������� a �� �����, ������� ��� ������ �������
		for (;;)
		{
			a = _base[a];
			used[a] = true;
			if (match[a] == -1) // ����� �� �����
			{
				break;
			}
			a = p[match[a]];
		}
		// ����������� �� ������� b, ���� �� ����� ���������� �������
		for (;;)
		{
			b = _base[b];
			if (used[b]) return b;
			b = p[match[b]];
		}
	}*/


	void PreliminaryGreedyMatchBuilding(const IGraphPtr& graph)
	{
		int graph_size = (*graph).Size();
		for (short vertex_num = 0; vertex_num < graph_size; vertex_num++)
		{
			_match.push_back(false);
		}

		for (size_t i = 0; i < graph_size; i++)
		{
			if (_match[i] == false)
			{
				// ���� ��� ������� ��� �� ��������
				/*auto neighbour : (*graph).GetNeighbours(i)#1#
				for (size_t j = 0; j < (*graph).) // TODO: �������� ������ �����, �� ����� ��� ����������
				{
					if (_match[neighbour] == false)
					{
						// ���� �������� ���� ��� �� ��������
						_matches_matrix[i][neighbour] = true; // �������� �������������
						_matches_matrix[neighbour][i] = true; // �������� �������������
						_match[_matches_matrix[i][neighbour]] = i; //�������� ������ �������
						_match[i] = _matches_matrix[i][neighbour]; //�������� ������
						break;
					}
				}*/
			}
		}
	}
}


	