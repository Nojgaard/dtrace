#include <bliss/graph.hh>
#include <vector>
#include <map>
#include "base.hpp"
#include "../range.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace graph {
namespace automorphism {

void callback(void *user_param, unsigned int n, 
		const unsigned int *aut) {
	vector<vector<vertex>> *raut = 
		static_cast<vector<vector<vertex>> *>(user_param);
	raut->push_back(vector<vertex>(n));
	for (size_t i = 0; i < n; i++) {
		raut->back()[i] = aut[i];
	}
}

void convert_to_bliss_graph(const graph_t &g, bliss::Graph &bg) {
	for (auto v : as_range(vertices(g))) {
		auto bv = bg.add_vertex();
		assert(bv == v);
	}
	for (auto e : as_range(edges(g))) {
		auto src = source(e,g);
		auto tar = target(e,g);
		bg.add_edge(src,tar);
	}
}

vector<vector<vertex>> find(const graph_t &g) {
	bliss::Graph bg;
	convert_to_bliss_graph(g,bg);
	vector<vector<vertex>> auts;
	bliss::Stats stats;
	bg.find_automorphisms(stats,callback,&auts);
	return auts;
}

}//automorphism
}//graph
