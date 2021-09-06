#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include "IGraph.h"


class Edmonds{
public:
	std::vector<std::vector<bool>> _matches_matrix{};



	Edmonds(int size) {
		for (int i = 0; i < size; i++) {
			_matches_matrix.push_back(std::vector<bool>(size));
		}
	}

	/*std::vector<std::pair<int, int>> BipartiteMatching(const IGraphPtr& graph) {
		std::vector<short> partner{};

	};*/

	/// <summary>
	/// Предполагаем, что алгоритм работает с двудольным графом и находит именно для него эти паросочетания
	/// </summary>
	void KhunAlgorithm(const IGraphPtr& graph, const int firstGraphFraction, const int secondGraphFraction) {
		auto graph_size = (*graph).Size();
		if ((*graph).Size() % 2 == 1) {
			std::cerr << "This graph not biparticipate";
			throw exception("This graph not biparticipate");
		}
	}

	int FindAugmentPath(const IGraphPtr& graph) {
		std::vector<bool> used_vertexes; // массив для использованных вершин
		std::vector<bool> used_odd_vertexes; // массив для просмотренных нечётных вершин
		std::vector<int> base;
		std::vector<int> q;
		std::vector<int> match;
		auto graph_size = (*graph).Size();
		//int n; размеры графа наверное, хуй знает
		//int MAXN = 6; тоже не ебу, максимально возможный размер графа
		//vector<int> g[MAXN];
		//int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
		//bool used[MAXN], blossom[MAXN];

		for (int i = 0; i < graph_size; ++i)
			base[i] = i;
		
		int root = (*graph).GetRoot();
		used_vertexes[root] = true;
		int qh = 0, qt = 0; // какие-то обоссаные счётчики
		q[qt++] = root;//

		while (qh < qt) { 
			int v = q[qh++];
			for (size_t i = 0; i < g[v].size(); ++i) {
				int to = g[v][i];
				if (base[v] == base[to] || match[v] == to)  continue;
				if (to == root || match[to] != -1 && p[match[to]] != -1) {
					int curbase = lca(v, to);
					memset(blossom, 0, sizeof blossom);
					mark_path(v, curbase, to);
					mark_path(to, curbase, v);
					for (int i = 0; i < n; ++i)
						if (blossom[base[i]]) {
							base[i] = curbase;
							if (!used[i]) {
								used[i] = true;
								q[qt++] = i;
							}
						}
				}
				else if (p[to] == -1) {
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

	void PreliminaryGreedyMatchBuilding(const IGraphPtr& graph) {
		std::vector<bool> tagged_vertices{};
		int graph_size = (*graph).Size();
		for (short vertex_num = 0; vertex_num < graph_size; vertex_num++) {
			tagged_vertices.push_back(false);
		}

		for (size_t i = 0; i < graph_size; i++) {
			if (tagged_vertices[i] == false) { // если эта вершина ещё не помечена
				for (auto neighbour:(*graph).GetNeighbours(i))
				{
					if (tagged_vertices[neighbour] == false) {// если соседняя нода ещё не помечена
						_matches_matrix[i][neighbour] = true; // помечаем паросочетание
						_matches_matrix[neighbour][i] = true; // помечаем паросочетание
						tagged_vertices[i] = true; //отмечаем первую вершину
						tagged_vertices[neighbour] = true; //отмечаем вторую
						break;
					}
				}
			}
		}
	}



	std::string ToJson() const {
		std::stringstream ss;
		ss << "\"graph\": " << "[" << std::endl;
		unsigned row_idx = 0;
		for (const auto& row : _matches_matrix) {
			row_idx++;
			ss << "[";
			unsigned elem_idx = 0;
			for (const auto elem : row) {
				elem_idx++;
				ss << elem;
				if (elem_idx != row.size()) {
					ss << ",";
				}
			}
			if (row_idx != _matches_matrix.size()) {
				ss << "],";
			}
			else {
				ss << "]";
			}
			ss << std::endl;
		}
		ss << "]";
		return ss.str();
	}
};