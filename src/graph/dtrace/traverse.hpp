#ifndef GRAPH_DTRACE_TRAVERSE_H
#define GRAPH_DTRACE_TRAVERSE_H
#include "../base.hpp"
#include "prop.hpp"
#include "trace.hpp"
#include <vector>

namespace graph  {
namespace dtrace {

void traverse_dfs(const graph_t &g, 
		const std::vector<property> &props,
		std::vector<trace> &out);

}//dtrace
}//graph
#endif
