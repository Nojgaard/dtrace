#ifndef GRAPH_AUT_H
#define GRAPH_AUT_H
#include <vector>
#include "base.hpp"

namespace graph {
namespace automorphism {

typedef std::vector<vertex> aut_t;

std::vector<std::vector<vertex>> find(const graph_t &g);

}//automorphism
}//graph
#endif
