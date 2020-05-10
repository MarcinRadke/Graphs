#ifndef PROJEKT2_PLIKODCZYTZAPIS_HH
#define PROJEKT2_PLIKODCZYTZAPIS_HH

#include <iostream>
#include <fstream>
#include <string>
#include "graph_templ.hh"

bool loadGraph(const std::string& fileName, listOfN::graph<int,int>& emptyGraph, int& startVert);
bool loadGraph(const std::string& fileName, matrixOfN::graph<int,int>& emptyGraph, int& startVert);

#endif //PROJEKT2_PLIKODCZYTZAPIS_HH
