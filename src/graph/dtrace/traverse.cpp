#include "../base.hpp"
#include "../aut.hpp"
#include "../../range.hpp"
#include "node.hpp"
#include "trace.hpp"
#include "prop.hpp"
#include <vector>

using namespace std;

namespace graph {
namespace dtrace {

namespace aut = automorphism;

vector<size_t> reference_auts(
		const vector<aut::aut_t> &auts) {
	vector<size_t> ref_auts(auts.size());
	for (size_t i = 0; i < auts.size(); i++) {
		ref_auts[i] = i;
	}
	return ref_auts;
}

vector<vertex> valid_extensions(const trace &t,
		const vector<property> &props) {
	vector<vertex> valid_vertices;
	for (auto e : 
			as_range(out_edges(t.head_vertex(),t.get_graph()))) {
		bool valid = true;
		for (auto &prop : props) {
			if (!prop(e,t)) {
				valid = false;
				break;
			}
		}
		if (valid) {
			valid_vertices.push_back(t.get_extension_vertex(e));
		}
	}
	return valid_vertices;

}

bool is_canonical(edge e, const trace &t) {
	if (t.size() == 0) return true;
	vertex v = t.get_extension_vertex(e);
	if (t.tail_vertex() != v) return true;
	
	vector<vertex> vt = t.get_vertex_trace();
	vertex minv = vt[0];
	vector<int> pp;
	for (size_t i = 0; i < vt.size(); i++) {
		if (vt[i] == minv) {
			pp.push_back(i);
		}
	}
	for (int p : pp) {
		//check backward
		for (size_t i = 0; i < vt.size(); i++) {
			int j = p-i;
			if (j <= 0) j = abs(j);
			if (vt[i] < vt[j]) {
				break;
			} else if (vt[i] > vt[j]) {
				return false;
			}
		}
		if (p == 0) continue;
		//check forward
		for (size_t i = 0; i < vt.size(); i++) {
			int j = (p+i);
			if (j >= (int)vt.size()) {
				j = (j)%vt.size();
			}
			if (vt[i] < vt[j]) {
				break;
			} else if (vt[i] > vt[j]) {
				return false;
			}
		}
	}
	return true;
}

void expand_node(const node &n, const vector<property> &props,
		vector<node> &cand_nodes) {
	auto valid_v = valid_extensions(n.get_trace(),props);
	vector<vertex> canon_v;
	n.canon_extensions(valid_v,canon_v);
	for (auto v : canon_v) {
		auto e = n.get_trace().get_extension_edge(v);
		if (is_canonical(e,n.get_trace()))
			cand_nodes.push_back(n.extend(e));
	}
}

void traverse_dfs(const graph_t &g, const vector<property> &props,
		vector<trace> &out) {
	auto global_auts = aut::find(g);
	assert(boost::edge(0,1,g).second);
	edge e = boost::edge(0,1,g).first;
	auto ref_auts = reference_auts(global_auts);
	vector<node> cand_nodes;
	cand_nodes.push_back(node(e,g,ref_auts,global_auts));
	while (!cand_nodes.empty()) {
		node n = cand_nodes.back();
		cand_nodes.pop_back();
		if (n.get_trace().size() == n.get_trace().tar_size()) {
			out.push_back(n.get_trace());
		} else {
			expand_node(n,props,cand_nodes);
		}
	}
}

}//dtrace
}//graph
