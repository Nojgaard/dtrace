#include "prop.hpp"

namespace graph  {
namespace dtrace {

bool is_full::operator () (edge e, const trace &t) const {
	if (t.size() <= 1) return true;
	int count = 0;
	for (size_t i = 0; i < t.size(); i++) {
		if (t[i] == e) {
			count++;
		}
	}
	return (count < 2);
}

bool has_one_repetition::operator () (edge e, const trace &t) const {
	if (t.size() == 0) return true;
	if (t.back() == e) return false;
	if (t.tar_size()-1 == t.size()&&t[0]==e) return false;
	return true;
}

bool has_two_repetition::operator () (edge e2, const trace &t) const {
	if (t.size() <= 1) return true;
	edge e1 = t.back();
	for (size_t i = 0; i <t.size()-1; i++) {
		if (t[i] == e1 && t[i+1] == e2) return false;
		if (t[i] == e2 && t[i+1] == e1) return false;
	}
	return true;
}

}//dtrace
}//graph
