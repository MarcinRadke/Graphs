#ifndef PROJEKT2_BELLMANFORDMATRIX_HH
#define PROJEKT2_BELLMANFORDMATRIX_HH

#include "graph_templ.hh"

namespace matrixOfN
{
    void BellmanFordDistances(graph<int, int>& Graph, int startVertID);
    void BellmanFordDistances(graph<int, int>& Graph, int startVertID, const std::string& fileName);
}

#endif //PROJEKT2_BELLMANFORDMATRIX_HH
