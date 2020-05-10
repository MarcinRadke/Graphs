#include "readGraphFromFile.hh"


bool loadGraph(const std::string& fileName, listOfN::graph<int,int>& emptyGraph, int& startVert)
{
    std::ifstream file; //strumień wejściowy z pliku
    file.open(fileName);

    //zmienne do wczytania grafu
    int edges = 0;
    int vertices = 0;

    //zmienne do wczytywania krawędzi
    int v1Elem;
    int v2Elem;
    int edgeWeight;

    //sprawdzenie czy graf jest pusty
    if((!emptyGraph.vertexList.isEmpty())||(!emptyGraph.edgeList.isEmpty()))
        return false;

    //sprawdzenie poprawności adresu pliku
    if(!file.good())
        return false;

    file >> edges >> vertices >> startVert;

    //sprawdzenie poprawności odczytu i ilości krawędzi
    if(file.fail() || edges > ((vertices*(vertices-3))/2)) return false;

    //dodanie wierzchołków
    for(int i = 0; i<vertices; ++i)
        emptyGraph.insertVertex(i);

    //dodawanie krawędzi
    for(int a=0; a<edges; ++a)
    {
        file >> v1Elem >> v2Elem >> edgeWeight;
        if(file.fail()) return false;
        //dodanie krawędzi
        emptyGraph.insertEdge(emptyGraph.getVfromElem(v1Elem),emptyGraph.getVfromElem(v2Elem),edgeWeight);
    }
    return true;
}

bool loadGraph(const std::string& fileName, matrixOfN::graph<int,int>& emptyGraph, int& startVert)
{
    std::ifstream file; //strumień wejściowy z pliku
    file.open(fileName);

    //zmienne do wczytania grafu
    int edges = 0;
    int vertices = 0;

    //zmienne do wczytywania krawędzi
    int v1Elem;
    int v2Elem;
    int edgeWeight;

    //sprawdzenie czy graf jest pusty
    if((!emptyGraph.vertexList.isEmpty())||(!emptyGraph.edgeList.isEmpty()))
        return false;

    //sprawdzenie poprawności adresu pliku
    if(!file.good())
        return false;

    file >> edges >> vertices >> startVert;

    //sprawdzenie poprawności odczytu i ilości krawędzi
    if(file.fail() || edges > ((vertices*(vertices-3))/2)) return false;

    //dodanie wierzchołków
    for(int i = 0; i<vertices; ++i)
        emptyGraph.insertVertex(i);

    //dodawanie krawędzi
    for(int a=0; a<edges; ++a)
    {
        file >> v1Elem >> v2Elem >> edgeWeight;
        if(file.fail()) return false;
        //dodanie krawędzi
        emptyGraph.insertEdge(emptyGraph.getVfromElem(v1Elem),emptyGraph.getVfromElem(v2Elem),edgeWeight);
    }
    return true;
}
