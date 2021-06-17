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

	void PreliminaryGreedyMatchBuilding(const IGraphPtr& graph) {
		std::vector<bool> tagged_vertices{};
		int graph_size = (*graph).Size();
		for (short vertex_num = 0; vertex_num < graph_size; vertex_num++) {
			tagged_vertices.push_back(false);
		}

		for (size_t i = 0; i < graph_size; i++) {
			if (tagged_vertices[i] == false) { // если эта вершина ещЄ не помечена
				for (auto neighbour:(*graph).GetNeighbours(i))
				{
					if (tagged_vertices[neighbour] == false) {// если соседн€€ нода ещЄ не помечена
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