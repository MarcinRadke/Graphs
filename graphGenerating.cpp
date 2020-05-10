#include "graphGenerating.hh"
#include <random>




namespace listOfN
{
    //z wagami ujemniymi
    graph<int,int> generateGraph(int size, int wypPercent)
    {
        graph<int,int> generatedGraph;
        bool tab[size][size]; //tablica do oznaczania powstałych krawędzi
        // - wykorzystywana tylko część nad przekątną

        for(int g=0;g<size;++g){
            for(int h=0;h<size;++h)
                tab[g][h] = false;
        }


        //zmienne do liczenia krawędzi do osiągnięcia zadanego wypełnienia
        int edges = 0;
        int maxEdges = (size*(size-3)*wypPercent)/200; //wzór na ilość kraw. - (n(n-3))/2 i wyliczenie procentowe

        //Silnik do generowania liczb losowych
        std::random_device rDevice;
        std::mt19937 gen(rDevice());
        std::uniform_int_distribution<> dystr(MIN,MAX);

        for(int a=0;a<size;++a)
        {
            generatedGraph.insertVertex(a);
        }

        //dodanie krawędzie między wszystkimi wierzchołkami - graf na pewno ciągły
        for(int b=1;b<size;++b) //b od 1, ze względu na użycie b-1
        {
            //wagi -10 do 19
            generatedGraph.insertEdge(generatedGraph.getVfromElem(b-1),generatedGraph.getVfromElem(b),(dystr(gen)%30)-10);
            tab[b-1][b] = true; //zaznaczenie istnienia krawędzi
            ++edges;
        }

        //pozostałe krawędzie dodatnie, o większych wartościach niż 10,
        // by zapewnić brak ujemnych cykli
        // wagi 10 do (MAX+10)
        while (edges<maxEdges) {
            for (int i = 1; i < size && edges < maxEdges; ++i) {
                for (int j = 0; j < i && edges < maxEdges; ++j)
                    if (!tab[j][i]) //jeśli nie ma krawędzi - dodaj
                    {
                        generatedGraph.insertEdge(generatedGraph.getVfromElem(j), generatedGraph.getVfromElem(i),
                                                  dystr(gen) + 10);
                        tab[j][i] = true;
                        ++edges;
                    }
            }
        }
        return generatedGraph;
    }

    //dla tylko dodatnich wag
    graph<int,int> generateGraphPos(int size, int wypPercent)
    {
        graph<int,int> generatedGraph;
        bool tab[size][size]; //tablica do oznaczania powstałych krawędzi
        // - wykorzystywana tylko część nad przekątną

        for(int g=0;g<size;++g){
            for(int h=0;h<size;++h)
                tab[g][h] = false;
        }


        //zmienne do liczenia krawędzi do osiągnięcia zadanego wypełnienia
        int edges = 0;
        int maxEdges = (size*(size-3)*wypPercent)/200; //wzór na ilość kraw. - (n(n-3))/2 i wyliczenie procentowe

        //Silnik do generowania liczb losowych
        std::random_device rDevice;
        std::mt19937 gen(rDevice());
        std::uniform_int_distribution<> dystr(MIN,MAX);

        for(int a=0;a<size;++a)
        {
            generatedGraph.insertVertex(a);
        }

        //dodanie krawędzie między wszystkimi wierzchołkami - graf na pewno ciągły
        for(int b=1;b<size;++b) //b od 1, ze względu na użycie b-1
        {
            generatedGraph.insertEdge(generatedGraph.getVfromElem(b-1),generatedGraph.getVfromElem(b),dystr(gen));
            tab[b-1][b] = true; //zaznaczenie istnienia krawędzi
            ++edges;
        }

        //wypełnienie
        while (edges<maxEdges) {
            for (int i = 1; i < size && edges < maxEdges; ++i) {
                for (int j = 0; j < i && edges < maxEdges; ++j)
                    if (!tab[j][i]) //jeśli nie ma krawędzi - dodaj
                    {
                        generatedGraph.insertEdge(generatedGraph.getVfromElem(j), generatedGraph.getVfromElem(i),dystr(gen));
                        tab[j][i] = true;
                        ++edges;
                    }
            }
        }
        return generatedGraph;
    }


}//end of namespace listOfN

namespace matrixOfN
{
    //z wagami ujemniymi
    graph<int,int> generateGraph(int size, int wypPercent)
    {
        graph<int,int> generatedGraph;
        bool tab[size][size]; //tablica do oznaczania powstałych krawędzi
        // - wykorzystywana tylko część nad przekątną

        //zmienne do liczenia krawędzi do osiągnięcia zadanego wypełnienia
        int edges = 0;
        int maxEdges = (size*(size-1)*wypPercent)/200; //wzór na ilość kraw. - (n(n-3))/2 i wyliczenie procentowe

        for(int g=0;g<size;++g){
            for(int h=0;h<size;++h)
                tab[g][h] = false;
        }

        //Silnik do generowania liczb losowych
        std::random_device rDevice;
        std::mt19937 gen(rDevice());
        std::uniform_int_distribution<> dystr(MIN,MAX);

        for(int a=0;a<size;++a)
        {
            generatedGraph.insertVertex(a);
        }

        //dodanie krawędzie między wszystkimi wierzchołkami - graf na pewno ciągły
        for(int b=1;b<size;++b) //b od 1, ze względu na użycie b-1
        {
            //wagi -10 do 19
            generatedGraph.insertEdge(generatedGraph.getVfromElem(b-1),generatedGraph.getVfromElem(b),(dystr(gen)%30)-10);
            tab[b-1][b] = true; //zaznaczenie istnienia krawędzi
            ++edges;
        }

        //pozostałe krawędzie dodatnie, o większych wartościach niż 10,
        // by zapewnić brak ujemnych cykli
        // wagi 10 do (MAX+10)
        while (edges<maxEdges) {
            for (int i = 1; i < size && (edges < maxEdges); ++i) {
                for (int j = 0; j < i && (edges < maxEdges); ++j)
                    if (!tab[j][i]) //jeśli nie ma krawędzi - dodaj
                    {
                        generatedGraph.insertEdge(generatedGraph.getVfromElem(j), generatedGraph.getVfromElem(i),
                                                  dystr(gen) + 10);
                        tab[j][i] = true;
                        ++edges;
                    }
            }
        }
        return generatedGraph;
    }

    //dla tylko dodatnich wag
    graph<int,int> generateGraphPos(int size, int wypPercent)
    {
        graph<int,int> generatedGraph;
        bool tab[size][size]; //tablica do oznaczania powstałych krawędzi
        // - wykorzystywana tylko część nad przekątną

        //zmienne do liczenia krawędzi do osiągnięcia zadanego wypełnienia
        int edges = 0;
        int maxEdges = (size*(size-3)*wypPercent)/200; //wzór na ilość kraw. - (n(n-3))/2 i wyliczenie procentowe

        //Silnik do generowania liczb losowych
        std::random_device rDevice;
        std::mt19937 gen(rDevice());
        std::uniform_int_distribution<> dystr(MIN,MAX);

        for(int a=0;a<size;++a)
        {
            generatedGraph.insertVertex(a);
        }

        //dodanie krawędzie między wszystkimi wierzchołkami - graf na pewno ciągły
        for(int b=1;b<size;++b) //b od 1, ze względu na użycie b-1
        {
            generatedGraph.insertEdge(generatedGraph.getVfromElem(b-1),generatedGraph.getVfromElem(b),dystr(gen));
            tab[b-1][b] = true; //zaznaczenie istnienia krawędzi
            ++edges;
        }

        //wypełnienie
        while (edges<maxEdges) {
            for (int i = 1; i < size && edges < maxEdges; ++i) {
                for (int j = 0; j < i && edges < maxEdges; ++j)
                    if (!tab[j][i]) //jeśli nie ma krawędzi - dodaj
                    {
                        generatedGraph.insertEdge(generatedGraph.getVfromElem(j), generatedGraph.getVfromElem(i),dystr(gen));
                        tab[j][i] = true;
                        ++edges;
                    }
            }
        }
        return generatedGraph;
    }

}
