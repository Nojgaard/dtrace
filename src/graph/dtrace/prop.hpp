#ifndef GRAPH_DTRACE_PROP_H
#define GRAPH_DTRACE_PROP_H
#include "../base.hpp"
#include "trace.hpp"
namespace graph  {
namespace dtrace {

class property {
public:
	virtual bool operator () (edge e, const trace &t) const
		{return true;}
};

struct is_full : property {
	bool operator () (edge e, const trace &t) const;
};

struct has_one_repetition : property {
	bool operator () (edge e, const trace &t) const;
};

struct has_two_repetition : property {
	bool operator () (edge e, const trace &t) const;
};

}//dtrace
}//graph
#endif
