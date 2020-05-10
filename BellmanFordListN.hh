#ifndef PROJEKT2_BELLMANFORDLISTN_HH
#define PROJEKT2_BELLMANFORDLISTN_HH

#include "graph_templ.hh"

namespace listOfN
{
    void BellmanFordDistances(graph<int, int>& Graph, int startVertID);
    void BellmanFordDistances(graph<int, int>& Graph, int startVertID, const std::string& fileName);
}



#endif //PROJEKT2_BELLMANFORDLISTN_HH
