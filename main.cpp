#include <iostream>
#include "graph_templ.hh"
#include "BellmanFordListN.hh"
#include "BellmanFordMatrix.hh"
#include "graphGenerating.hh"
#include "readGraphFromFile.hh"


int main() {

    //ilości wierzchołków: 50, 100, 150, 200, 250
    //stopnie wypełnienia: 25, 50, 75, 100

    //test działania - program wczytuje z pliku graf
    // zrealizowany przez listę sąsiedztwa
    // po czym korzystając z algorytmu Bellmana-Forda
    // wylicza najkrótsze ścieżki i zapisuje wyniki
    // do pliku test2.txt

    int startVert ;//= 0// jezeli tworzenie losowego grafu
    listOfN::graph<int,int> graf1;
    //graf1 = listOfN::generateGraph(250,100); //tworzenie losowego grafu (ilosc wierzcholkow,gestosc)
    //losowy graf z macierzy listOfN zmienic na matrixOfN
    if(loadGraph("graf.txt",graf1,startVert))
    {
        listOfN::BellmanFordDistances(graf1,startVert,"test2.txt");
    }



    return 0;

}
