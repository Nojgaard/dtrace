#include "trace.hpp"
#include "prop.hpp"
#include "../base.hpp"
#include <vector>
#include <cassert>
#include <iostream>
#include "../../range.hpp"

using namespace std;
namespace graph  {
namespace dtrace {

trace::trace(const trace &ct) 
	: t(ct.t),head(ct.head),tail(ct.tail),g(ct.g){}

trace::trace(vertex v, const graph_t &g) : g(g) {
	head = v;
	tail = v;
}

void trace::extend(edge e) {
	auto src = source(e,g);
	auto tar = target(e,g);
	assert(src==head||tar==head);
	head = (src==head)?tar:src;
	t.push_back(e);
}

vertex trace::head_vertex() const {
	return head;
}

vertex trace::tail_vertex() const {
	return tail;
}

vertex trace::get_extension_vertex(edge e) const {
	auto src = source(e,g);
	auto tar = target(e,g);
	assert(src==head || tar==head);
	return (src==head)?tar:src;
}

edge trace::get_extension_edge(vertex v) const {
	auto p = boost::edge(head,v,g);
	assert(p.second);
	return p.first;
}

vector<vertex> trace::get_vertex_trace() const {
	vector<vertex> vt;
	vt.push_back(tail);
	for (auto e : t) {
		auto src = source(e,g);
		auto tar = target(e,g);
		vertex to = (src == vt.back())?tar:src;
		vt.push_back(to);
	}

	return vt;
}

const graph_t & trace::get_graph() const {
	return g;
}

const edge & trace::operator[](size_t idx) const {
	assert(idx >= 0 && idx < t.size());
	return t[idx];
}

edge trace::back() const {
	return t.back();
}

size_t trace::size() const {
	return t.size();
}

size_t trace::tar_size() const {
	return num_edges(g) * 2;
}

}//dtrace
}//graph
