#include "node.hpp"
#include "../aut.hpp"
#include "trace.hpp"
#include <map>

using namespace std;

namespace graph  {
namespace dtrace {

namespace aut = automorphism;

node::node(edge e, const graph_t &g, 
		const vector<size_t> &ref_auts,
		const vector<aut::aut_t> &auts)
	: t(0,g), ref_auts(ref_auts), auts(auts){
		t.extend(e);
	}

node::node(const trace &t, 
		const std::vector<aut::aut_t> &auts):t(t),auts(auts){}

node node::extend(edge e) const {
	node n(t,auts);
	n.t.extend(e);
	n.prune_auts(n.t.head_vertex(),ref_auts);
	return n;
}

void node::canon_extensions(const vector<vertex> &in
		,vector<vertex> &out) const {
	assert(out.size() == 0);
	if (ref_auts.size() <= 1) {
		for (auto e : in) {
			out.push_back(e);
		}
		return;
	}
	map<vertex,bool> visited;
	for (auto v : in) {
		if (visited.find(v) != visited.end()) continue;
		auto min_v = v;
		for (auto i : ref_auts) {
			visited[auts[i][v]] = true;
			if (auts[i][v] < min_v) {
				min_v = auts[i][v];
			}
		}
		out.push_back(min_v);
	}
}

const trace & node::get_trace() const {
	return t;
}

void node::prune_auts(vertex v,const vector<size_t> &cand_auts) {
	for (auto i : cand_auts) {
		if (auts[i][v] == v) ref_auts.push_back(i);
	}
}

}//dtrace
}//graph
