#include "traverse.hpp"
#include "trace.hpp"
#include "prop.hpp"

using namespace std;

namespace graph  {
namespace dtrace {

vector<trace> find(const graph_t &g) {
	vector<property> props;
	props.push_back(is_full());
	props.push_back(has_one_repetition());
	props.push_back(has_two_repetition());
	vector<trace> out_traces;
	traverse_dfs(g,props,out_traces);
	return out_traces;
}

}//dtrace
}//graph
