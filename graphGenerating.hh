#ifndef PROJEKT2_GRAPHGENERATING_HH
#define PROJEKT2_GRAPHGENERATING_HH

#include "graph_templ.hh"

/*
 * Zakresy generacji liczb losowych
 * do tworzenia wag
 */
#define MIN 0
#define MAX 20000


/*
 * Generacja grafów
 * dla obydwu implementacji
 */

namespace listOfN
{
    graph<int,int> generateGraph(int size, int wypPercent);
    graph<int,int> generateGraphPos(int size, int wypPercent);
}

namespace matrixOfN
{
    graph<int,int> generateGraph(int size, int wypPercent);
    graph<int,int> generateGraphPos(int size, int wypPercent);
}

#endif //PROJEKT2_GRAPHGENERATING_HH
