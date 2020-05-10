#include "graph_templ.hh"
#include <chrono>
#include <fstream>

#define INFTY 40000000

//oznaczenie osobnego wyświetlenia czasu do testów
#define TEST_DISP true

namespace listOfN {


    void BellmanFordDistances(graph<int, int> &Graph, int startVertID) {

        //tablice etykiet
        int distance[Graph.vertexList.front().showID() + 1];

        //! start timera
        auto pocz = std::chrono::high_resolution_clock::now();

        node<Vertex<int>> *v = Graph.vertexList.getHead();

        while (v) {
            if (v->getElem().showID() == startVertID)
                distance[v->getElem().showID()] = 0; // - Poczatkowe przypisanie odleglosci: 0 dla startowego
            else distance[v->getElem().showID()] = INFTY;                      //  niesk. dla pozostalych
            v = v->getNext();
        }

        //zmienne pomocnicze do iteracji
        Vertex<int> u, z;
        node<Edge<Vertex<int>, int>> *edgeIterNode;
        Edge<Vertex<int>, int> *edgeIter;
        //zmienna do wyliczania nowego dystansu
        int r;
        int stopV = Graph.vertexList.getHead()->showID();

        for (int j = 0; j <= stopV; ++j)
        {   //aktualizacja odległości i relaksacja krawędzi

            edgeIterNode = Graph.edgeList.getHead();
            edgeIter = &(edgeIterNode->getElem());
            while (edgeIter) {

                if (distance[edgeIter->Vert_1.showID()] < distance[edgeIter->Vert_2.showID()]) {
                    u = edgeIter->Vert_1;
                    z = edgeIter->Vert_2;
                } else {
                    u = edgeIter->Vert_2;
                    z = edgeIter->Vert_1;
                }
                r = distance[u.showID()] + edgeIter->elem;
                if (r < distance[z.showID()]) {
                    distance[z.showID()] = r;

                }

                edgeIterNode = edgeIterNode->getNext();
                edgeIter = &(edgeIterNode->getElem());
            }

        }

        //!koniec timera
        auto kon = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> czasTrwania = kon-pocz;

        std::cout <<std::endl<<std::endl
                  << "Algorytm Bellmana-Forda - graf z listą sąsiedztwa" << std::endl
                  << "Czas trwania [s]:" << czasTrwania.count() <<std::endl<<std::endl;

        std::cout << "Vert.:" << "  " << "Distance:" << std::endl;

        //wyświetlenie - iteracja po wierzchołkach
        v = Graph.vertexList.getHead();

        while (v) {
            std::cout <<v->getElem().showID() << "     "
            << distance[v->getElem().showID()] << std::endl;
            v = v->getNext();
        }
    }

    //Z zapisem do pliku
    void BellmanFordDistances(graph<int, int> &Graph, int startVertID, const std::string& fileName) {

        //tablice etykiet
        int distance[Graph.vertexList.front().showID() + 1];

        //! start timera
        auto pocz = std::chrono::high_resolution_clock::now();

        node<Vertex<int>> *v = Graph.vertexList.getHead();

        while (v) {
            if (v->getElem().showID() == startVertID)
                distance[v->getElem().showID()] = 0; // - Poczatkowe przypisanie odleglosci: 0 dla startowego
            else distance[v->getElem().showID()] = INFTY;                      //  niesk. dla pozostalych
            v = v->getNext();
        }

        //zmienne pomocnicze do iteracji
        Vertex<int> u, z;
        node<Edge<Vertex<int>, int>> *edgeIterNode;
        Edge<Vertex<int>, int> *edgeIter;
        //zmienna do wyliczania nowego dystansu
        int r;
        int stopV = Graph.vertexList.getHead()->showID();

        for (int j = 0; j <= stopV; ++j)
        {   //aktualizacja odległości i relaksacja krawędzi

            edgeIterNode = Graph.edgeList.getHead();
            edgeIter = &(edgeIterNode->getElem());
            while (edgeIter) {

                if (distance[edgeIter->Vert_1.showID()] < distance[edgeIter->Vert_2.showID()]) {
                    u = edgeIter->Vert_1;
                    z = edgeIter->Vert_2;
                } else {
                    u = edgeIter->Vert_2;
                    z = edgeIter->Vert_1;
                }
                r = distance[u.showID()] + edgeIter->elem;
                if (r < distance[z.showID()]) {
                    distance[z.showID()] = r;

                }

                edgeIterNode = edgeIterNode->getNext();
                edgeIter = &(edgeIterNode->getElem());
            }

        }

        //!koniec timera
        auto kon = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> czasTrwania = kon-pocz;

        if(TEST_DISP) std::cout << czasTrwania.count() <<std::endl;

        //Zapis do pliku

        std::ofstream file;
        file.open(fileName);
        if(file.good()) {
            file << "Algorytm Bellmana-Forda - graf z listą sąsiedztwa" << std::endl
                 << "Czas trwania [s]:" << czasTrwania.count() << std::endl << std::endl;

            file << "Vert.:" << "  " << "Distance:" << std::endl;

            //wyświetlenie - iteracja po wierzchołkach
            v = Graph.vertexList.getHead();

            while (v) {
                file << v->getElem().showID() << "     "
                          << distance[v->getElem().showID()] << std::endl;
                file.flush();
                v = v->getNext();
            }
        }
        else std::cout << "Brak dostępu do pliku!!" << std::endl;
    }
}

