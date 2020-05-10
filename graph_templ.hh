#ifndef PROJEKT2_GRAPH_TEMPL_HH
#define PROJEKT2_GRAPH_TEMPL_HH

#include <iostream>
#include "list_template.hh"
#include "matrix_template.hh"



/*
 * przestrzen nazw dla grafów realizowanych
 * przez schemat listy sąsiedztwa
 *
 * parametry:
 * elem_t - typ elementów dla wierzcholków
 * edgeElem_t - typ elementów dla krawędzi
 */

namespace listOfN {


    template <class vert_t, class edgeElem_t>
    struct Edge
    {

        Edge(vert_t& V1, vert_t& V2): listOfNeighbours_1(V1.listOfNeighbours), listOfNeighbours_2(V2.listOfNeighbours) {}
        //Edge(const Edge& copiedEdge): listOfNeighbours_1(copiedEdge.listOfNeighbours_1), listOfNeighbours_2(copiedEdge.listOfNeighbours_2),
        //Vert_1(copiedEdge.Vert_1), Vert_2(copiedEdge.Vert_2), elem(copiedEdge.elem) {}

        //node<Edge>& position;

        vert_t Vert_1;
        list<Edge&>& listOfNeighbours_1;

        vert_t Vert_2;
        list<Edge&>& listOfNeighbours_2;

        edgeElem_t elem;
    };


    template <class elem_t>
    struct Vertex
    {

        Vertex() : listOfNeighbours() {}
        //Vertex(const Vertex& sndV): position(sndV.position), listOfNeighbours(sndV.listOfNeighbours), elem(sndV.elem) {}

        node<Vertex>* position;
        list<Edge<Vertex,elem_t>&> listOfNeighbours;
        elem_t elem;

        //porównanie - kryterium to zgodność pozycji i elementu
        bool operator== (Vertex<elem_t> sndVert) {return (this->position==sndVert.position && this->elem == sndVert.elem);}

    private:
        int _idNum = 0;
    public:
        int showID() const { return _idNum;}
        void setID(int newID) {_idNum = newID;}

    };


    /*
     * funkcje wyswietlajace i wczytujace krawedzie i wierzcholki za pomoca iostream
     *
     * Warunki wstepne:
     * Funkcje zakladaja, ze istnieje przeciazenie ostream dla typow elem_t i edgeElem_t
     */
    template <class elem_t>
    std::ostream& operator<< (std::ostream& out, const Vertex<elem_t>& vert)
    {
        out << vert.position->showID() << "-" << vert.elem << " ";
        return out;
    }

    template <class elem_t, class edgeElem_t>
    std::ostream& operator<< (std::ostream& out, const Edge<Vertex<elem_t>,edgeElem_t>& edge)
    {
        out << edge.position->showID() << " "
        << "V1: " << edge.Vert_1
        << "V2: " << edge.Vert_2
        << edge.elem << std::endl;
        return out;
    }

    template <class elem_t>
    std::istream& operator>> (std::istream& input, Vertex<elem_t>& vert)
    {
        input >> vert.elem;
        return input;
    }

    template <class elem_t, class edgeElem_t>
    std::istream& operator>> (std::istream& input, Edge<Vertex<elem_t>,edgeElem_t>& edge)
    {
        input >> edge.Vert_1 >> edge.Vert_2 >> edge.elem;
        return input;
    }

    template <class elem_t, class edgeElem_t>
    class graph {

        int _numOfVert = 0;

    public:

        list<Vertex<elem_t>>               vertexList;
        list<Edge<Vertex<elem_t>,edgeElem_t>>  edgeList;

        //dodawanie i usuwanie
        void insertVertex(elem_t elem);
        void insertEdge(Vertex<elem_t>& startV, Vertex<elem_t>& endV, edgeElem_t elem);

        void removeVertex(Vertex<elem_t>&);
        void removeEdge(Edge<Vertex<elem_t>,edgeElem_t>&);

        //metody dostepu
        Vertex<elem_t>* endVertices(Edge<Vertex<elem_t>,edgeElem_t>&) const;      //tablica wierzcholkow koncowych krawedzi
        Vertex<elem_t>& opposite(Edge<Vertex<elem_t>,edgeElem_t>&,Vertex<elem_t>&);//referencja do przeciwleglego wierzcholka
        bool areAdjacent(Vertex<elem_t>&, Vertex<elem_t>&) const;
            //- zamiana elementow
        void replace(Vertex<elem_t>& Vert, elem_t);
        void replace(Edge<Vertex<elem_t>,edgeElem_t>&, edgeElem_t);

        /*
         * Metody wyszukujace od konca pierwszy wierzcholek/ pierwsza krawedz
         * z podanym elementem i zwracajace jego numer ID, przyznany przez liste
         *
         *  -1 oznacza nie znaleziene na liscie danego elementu
         */
        int getVertexID(elem_t elem) const;
        int getEdgeID(edgeElem_t elem) const;

        //znajdowanie wierzchołków
        Vertex<elem_t>& getVfromElem(elem_t searchedElem);


    };

    template <class elem_t, class edgeElem_t>
    void listOfN::graph<elem_t,edgeElem_t>::insertVertex(elem_t elem)
    {
        Vertex<elem_t> newVert; //metoda dodania do listy sama tworzy instancje
        newVert.elem = elem;
        this->vertexList.addFront(newVert);
        vertexList.front().position = vertexList.getHead();
        vertexList.front().setID(vertexList.front().position->showID());
        ++_numOfVert;
    }

    template <class elem_t, class edgeElem_t>
    void listOfN::graph<elem_t,edgeElem_t>::insertEdge(listOfN::Vertex<elem_t>& startV, listOfN::Vertex<elem_t>& endV,edgeElem_t elem)
    {
        Edge<Vertex<elem_t>,edgeElem_t> newEdge(startV,endV); //metoda dodania do listy sama tworzy instancje
        newEdge.Vert_1 = startV;
        newEdge.listOfNeighbours_1 = startV.listOfNeighbours;
        newEdge.Vert_2 = endV;
        newEdge.listOfNeighbours_2 = endV.listOfNeighbours;
        newEdge.elem = elem;

        this->edgeList.addFront(newEdge);

        //edgeList.front().position = edgeList.getHead();//przypisanie pozycji
        //dodanie do list sasiedztwa
        startV.listOfNeighbours.addFront(edgeList.getHead()->getElem());
        endV.listOfNeighbours.addFront(edgeList.getHead()->getElem());
    }


    template <class elem_t,class edgeElem_t>
    void graph<elem_t,edgeElem_t>::removeEdge(Edge<Vertex<elem_t>, edgeElem_t>& edgeToRm)
    {
        //usuwanie z listy sasiedztwa
        edgeToRm.listOfNeighbours_1.removeElem(edgeToRm);
        edgeToRm.listOfNeighbours_2.removeElem(edgeToRm);

        //usuwanie z listy krawedzi
        this->edgeList.removeElem(edgeToRm);
        --_numOfVert;
    }

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::removeVertex(Vertex<elem_t>& vertToRm)
    {

        //usuwanie przyleglych krawedzi
        while(!vertToRm.listOfNeighbours.isEmpty())
            this->removeEdge(vertToRm.listOfNeighbours.front());

        //usuwanie wierzcholka
        this->vertexList.removeElem(vertToRm);
    }

    template <class elem_t, class edgeElem_t>
    Vertex<elem_t>* graph<elem_t,edgeElem_t>::endVertices(Edge<Vertex<elem_t>, edgeElem_t>& edge) const
    {
        Vertex<elem_t> endVert[2];
        endVert[0] = edge.Vert_1;
        endVert[1] = edge.Vert_2;
        return endVert;
    }

    template <class elem_t,class edgeElem_t>
    Vertex<elem_t>& graph<elem_t,edgeElem_t>::opposite(Edge<Vertex<elem_t>, edgeElem_t>& edge, Vertex<elem_t>& firstVert)
    {
        if(edge.Vert_1==firstVert) return edge.Vert_2;
        if(edge.Vert_2==firstVert) return edge.Vert_1;
        return edge.Vert_2;//todo: zamiana na obsluge bledu, gdy wierzcholek nie nalezy do krawedzi.
    }

    template <class elem_t, class edgeElem_t>
    bool graph<elem_t,edgeElem_t>::areAdjacent(Vertex<elem_t>& firstVert, Vertex<elem_t>& sndVert) const
    {
        Edge<Vertex<elem_t>,edgeElem_t> edgeIterator = firstVert.listOfNeighbours.getHead();
        while(edgeIterator) //iteruj do osiagniecia nullptr
        {
            if((edgeIterator.Vert_1==firstVert&&edgeIterator.Vert_2=sndVert)||(edgeIterator.Vert_1==sndVert&&edgeIterator.Vert_2==firstVert))
                return true;
        }
        return false;//jesli nie znaleziono krawedzi, zwroc false
    }

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::replace(Vertex<elem_t>& vert, elem_t newElem)
    {
        vert.elem=newElem;
    }
    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::replace(Edge<Vertex<elem_t>, edgeElem_t> & edge, edgeElem_t newElem)
    {
        edge.elem=newElem;
    }

    template <class elem_t, class edgeElem_t>
    int graph<elem_t,edgeElem_t>::getVertexID(elem_t searchedElem) const
    {
        if(!vertexList.isEmpty()) {
            //rozpoczecie od sczytu
            node<Vertex<elem_t>> *searchPtr = vertexList.getHead();
            while (searchPtr) //do momentu dotarcia do konca
            {
                if (searchPtr->getElem().elem == searchedElem) return searchPtr->showID();
                searchPtr = searchPtr->getNext();
            }
        }

        //jesli nie znaleziono lub lista pusta
        return -1;
    }

    template <class elem_t, class edgeElem_t>
    Vertex<elem_t>& graph<elem_t,edgeElem_t>::getVfromElem(elem_t searchedElem)
    {
        if(!vertexList.isEmpty()) {
            //rozpoczecie od sczytu
            node<Vertex<elem_t>> *searchPtr = vertexList.getHead();
            while (searchPtr) //do momentu dotarcia do konca
            {
                if (searchPtr->getElem().elem == searchedElem) return searchPtr->getElem();
                searchPtr = searchPtr->getNext();
            }
        }
        return vertexList.front(); //nie znaleziono todo: wyrzucić wyjątek
    }

    template <class elem_t, class edgeElem_t>
    int graph<elem_t,edgeElem_t>::getEdgeID(edgeElem_t searchedElem) const
    {
        if(!edgeList.isEmpty()) {
            //rozpoczecie od sczytu
            node<Vertex<elem_t>> *searchPtr = vertexList.getHead();
            while (searchPtr) //do momentu dotarcia do konca
            {
                if (searchPtr->getElem().elem == searchedElem) return searchPtr->showID();
                searchPtr = searchPtr->getNext();
            }
        }

        //jesli nie znaleziono lub lista pusta
        return -1;
    }

}


namespace matrixOfN {

    template <class vert_t, class edgeElem_t>
    struct Edge
    {
        vert_t Vert_1;
        vert_t Vert_2;

        edgeElem_t elem;
    };


    template <class elem_t>
    struct Vertex
    {
        int ixKey; //index (integer key)
        //node<Vertex>* position;
        elem_t elem;

        //Vertex(): position(nullptr) {}

        //porównanie - kryterium to zgodność klucza i elementu
        bool operator== (Vertex<elem_t> sndVert) {return (this->ixKey==sndVert.ixKey && this->elem == sndVert.elem);}

    };

    /*
     * funkcje wyswietlajace i wczytujace krawedzie i wierzcholki za pomoca iostream
     *
     * Warunki wstepne:
     * Funkcje zakladaja, ze istnieje przeciazenie ostream dla typow elem_t i edgeElem_t
     */
    template <class elem_t>
    std::ostream& operator<< (std::ostream& out, const Vertex<elem_t>& vert)
    {
        out << vert.ixKey << "-" << vert.elem << " ";
        return out;
    }

    template <class elem_t, class edgeElem_t>
    std::ostream& operator<< (std::ostream& out, const Edge<Vertex<elem_t>,edgeElem_t>& edge)
    {
        out << "V1: " << edge.Vert_1
            << "V2: " << edge.Vert_2
            << edge.elem << std::endl;
        return out;
    }

    template <class elem_t>
    std::istream& operator>> (std::istream& input, Vertex<elem_t>& vert)
    {
        input >> vert.elem;
        return input;
    }

    template <class elem_t, class edgeElem_t>
    std::istream& operator>> (std::istream& input, Edge<Vertex<elem_t>,edgeElem_t>& edge)
    {
        input >> edge.Vert_1 >> edge.Vert_2 >> edge.elem;
        return input;
    }



    template <class elem_t, class edgeElem_t>
    class graph {
    public:

        list<Vertex<elem_t>>                    vertexList;
        list<Edge<Vertex<elem_t>,edgeElem_t>>   edgeList;

        Matrix2D<Edge<Vertex<elem_t>,edgeElem_t>*> matrixOfNeighbours;

        //dodawanie i usuwanie
        void insertVertex(elem_t elem);
        void insertEdge(Vertex<elem_t>& startV, Vertex<elem_t>& endV, edgeElem_t elem);

        void removeVertex(Vertex<elem_t>&);
        void removeEdge(Edge<Vertex<elem_t>,edgeElem_t>&);

        //metody dostepu
        Vertex<elem_t>* endVertices(Edge<Vertex<elem_t>,edgeElem_t>&) const;      //tablica wierzcholkow koncowych krawedzi
        Vertex<elem_t> opposite(Edge<Vertex<elem_t>,edgeElem_t>&,Vertex<elem_t>&);//referencja do przeciwleglego wierzcholka
        bool areAdjacent(Vertex<elem_t>&, Vertex<elem_t>&) const;
        //zamiana elementow
        void replace(Vertex<elem_t>& Vert, elem_t);
        void replace(Edge<Vertex<elem_t>,edgeElem_t>&, edgeElem_t);

        Vertex<elem_t>& getVfromElem(elem_t searchedElem);

        //metody iterujace


    };

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::insertVertex(elem_t elem)
    {
        Vertex<elem_t> newVert; //metoda dodania do listy sama tworzy instancje
        newVert.elem = elem;

        //nadawanie klucza
        if(vertexList.isEmpty()) newVert.ixKey=0;
        else newVert.ixKey = vertexList.getHead()->getElem().ixKey + 1; //poprzedni +1
        //wpisanie na listę
        this->vertexList.addFront(newVert);
        //        vertexList.front().position = vertexList.getHead();
        //jeśli trzeba - powiększenie macierzy
        if((matrixOfNeighbours.showSize())<=vertexList.getHead()->getElem().ixKey)
            matrixOfNeighbours.increaseSize();

    }

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::insertEdge(Vertex<elem_t>& startV, Vertex<elem_t>& endV, edgeElem_t elem)
    {
        Edge<Vertex<elem_t>,edgeElem_t> newEdge; //metoda dodania do listy sama tworzy instancje
        newEdge.Vert_1 = startV;
        newEdge.Vert_2 = endV;
        newEdge.elem = elem;

        this->edgeList.addFront(newEdge);

        //"zerowanie" powiększonej części macierzy
        for(int j=0;j<matrixOfNeighbours.showSize();++j) {
            matrixOfNeighbours[matrixOfNeighbours.showSize() - 1][j] = nullptr;
            matrixOfNeighbours[j][matrixOfNeighbours.showSize() - 1] = nullptr;
        }

        //edgeList.front().position = edgeList.getHead();//przypisanie pozycji
        //wpisanie do macierzy
        Edge<Vertex<elem_t>,edgeElem_t>* ptr = &(edgeList.front());
        matrixOfNeighbours[startV.ixKey][endV.ixKey] = &(edgeList.front());
        matrixOfNeighbours[endV.ixKey][startV.ixKey] = &(edgeList.front());
    }


    template <class elem_t,class edgeElem_t>
    void graph<elem_t,edgeElem_t>::removeEdge(Edge<Vertex<elem_t>, edgeElem_t>& edgeToRm)
    {
        //usuwanie z macierzy
        matrixOfNeighbours[edgeToRm.Vert_1.ixKey][edgeToRm.Vert_2.ixKey] = nullptr;
        matrixOfNeighbours[edgeToRm.Vert_2.ixKey][edgeToRm.Vert_1.ixKey] = nullptr;

        //usuwanie z listy krawedzi
        this->edgeList.removeElem(edgeToRm);
    }

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::removeVertex(Vertex<elem_t>& vertToRm)
    {
        Edge<Vertex<elem_t>,edgeElem_t>* edgeIter;

        //usuwanie przyleglych krawedzi
        for(int i=0; i<=vertexList.getHead()->getElem().ixKey;++i)
        {
            edgeIter = matrixOfNeighbours[vertToRm.ixKey][i];
            if(edgeIter) removeEdge(&edgeIter);
        }

        //usuwanie wierzcholka
        this->vertexList.removeElem(vertToRm);
    }

    template <class elem_t, class edgeElem_t>
    Vertex<elem_t>* graph<elem_t,edgeElem_t>::endVertices(Edge<Vertex<elem_t>, edgeElem_t>& edge) const
    {
        Vertex<elem_t> endVert[2];
        endVert[0] = edge.Vert_1;
        endVert[1] = edge.Vert_2;
        return endVert;
    }

    template <class elem_t,class edgeElem_t>
    Vertex<elem_t> graph<elem_t,edgeElem_t>::opposite(Edge<Vertex<elem_t>, edgeElem_t>& edge, Vertex<elem_t>& firstVert)
    {
        if(edge.Vert_1==firstVert) return edge.Vert_2;
        if(edge.Vert_2==firstVert) return edge.Vert_1;
        return edge.Vert_1;//todo: zamiana na obsluge bledu, gdy wierzcholek nie nalezy do krawedzi.
    }

    template <class elem_t, class edgeElem_t>
    bool graph<elem_t,edgeElem_t>::areAdjacent(Vertex<elem_t>& firstVert, Vertex<elem_t>& sndVert) const
    {
        Edge<Vertex<elem_t>,edgeElem_t> edgeIter;

        for(int i=0; i<=vertexList.getHead()->getElem().ixKey;++i)
        {
            edgeIter = matrixOfNeighbours[firstVert.ixKey][i];
            if(edgeIter)//osobny warunek, dla unikniecia operacji na NULL
                if(edgeIter.Vert_1 == sndVert || edgeIter.Vert_2 == sndVert) return true;
        }
        return false;
    }

    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::replace(Vertex<elem_t>& vert, elem_t newElem)
    {
        vert.elem=newElem;
    }
    template <class elem_t, class edgeElem_t>
    void graph<elem_t,edgeElem_t>::replace(Edge<Vertex<elem_t>, edgeElem_t> & edge, edgeElem_t newElem)
    {
        edge.elem=newElem;
    }

    template <class elem_t, class edgeElem_t>
    Vertex<elem_t>& graph<elem_t,edgeElem_t>::getVfromElem(elem_t searchedElem)
    {
        if(!vertexList.isEmpty()) {
            //rozpoczecie od sczytu
            node<Vertex<elem_t>> *searchPtr = vertexList.getHead();
            while (searchPtr) //do momentu dotarcia do konca
            {
                if (searchPtr->getElem().elem == searchedElem) return searchPtr->getElem();
                searchPtr = searchPtr->getNext();
            }
        }
        return vertexList.front(); //nie znaleziono todo: wyrzucić wyjątek
    }

}

#endif //PROJEKT2_GRAPH_TEMPL_HH
