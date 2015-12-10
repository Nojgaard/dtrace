#ifndef GRAPH_DTRACE_NODE_H
#define GRAPH_DTRACE_NODE_H
#include "../aut.hpp"
#include "../base.hpp"
#include "trace.hpp"
#include <vector>

namespace graph  {
namespace dtrace {

class node {
public:
	node(edge e, const graph_t &g,
			const std::vector<size_t> &ref_auts,
			const std::vector<automorphism::aut_t> &auts);
	node(const trace &t, 
			const std::vector<automorphism::aut_t> &auts);
	node extend(edge e) const;

	void canon_extensions(const std::vector<vertex> &in, 
			std::vector<vertex> &out) const;
	const trace & get_trace() const;
private:
	void prune_auts(vertex v, const std::vector<size_t> &cand_auts);

	trace t;
	std::vector<size_t> ref_auts;
	const std::vector<automorphism::aut_t> &auts;
};

}//dtrace
}//graph
#endif
