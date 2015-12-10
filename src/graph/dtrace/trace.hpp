#ifndef GRAPH_DTRACE_TRACE_H
#define GRAPH_DTRACE_TRACE_H
#include "../base.hpp"
#include <vector>

namespace graph {
namespace dtrace {

class trace {
public:
	trace(const trace &ct);
	trace(vertex v, const graph_t &g);
	void extend(edge e);
	vertex head_vertex() const;
	vertex tail_vertex() const;
	vertex get_extension_vertex(edge e) const;
	edge get_extension_edge(vertex v) const;
	std::vector<vertex> get_vertex_trace() const;
	const edge & operator [] (std::size_t idx) const;
	const graph_t & get_graph() const;
	std::size_t size() const;
	std::size_t tar_size() const;
	edge back() const;
private:
	std::vector<edge> t;
	vertex head,tail;
	const graph_t &g;
};
}//dtrace
}//dtrace
#endif

