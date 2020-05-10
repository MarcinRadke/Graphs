#ifndef PROJEKT2_MATRIX_TEMPLATE_HH
#define PROJEKT2_MATRIX_TEMPLATE_HH

template <class elem_t>
class Vector2D
{
private:

    int size;
    int ilElem;
    elem_t* vector;

public:

    Vector2D()
    {
        vector = new elem_t[1];
        size = 1;
        ilElem = 0;
    }
    //dodawanie ze sprawdzeniem rozmiaru i powiększeniem
    //jeżeli jest konieczne
    void add(elem_t);
    //pokazuje wart. rozmiaru
    int showSize() const { return size;}
    //zwiększa rozmiar (o 7)
    void increaseSize();

    const elem_t& operator [] (const int iX) const {return vector[iX];}
    elem_t& operator [] (const int iX) {return vector[iX];}

};

template <class elem_t>
void Vector2D<elem_t>::increaseSize()
{
    //kopiowanie
    elem_t copyOfOld[size];
    for(int i=0;i<size;++i) copyOfOld[i]=vector[i];
    //usuniecie starego wektora
    delete[] vector;
    //nowa alokacja - zmiana rozmiaru
    int oldSize = size;
    ++this->size;
    this->vector = new elem_t[size];
    //wpisanie starych wartości
    for(int j=0;j<oldSize;++j) vector[j]=copyOfOld[j];
}

template <class elem_t>
void Vector2D<elem_t>::add(elem_t elem)
{
    ++ilElem;
    if(size<ilElem) increaseSize();
    vector[ilElem-1] = elem;
}

//Macierz kwadratowa
template <class elem_t>
class Matrix2D
{
    Vector2D<Vector2D<elem_t>> matrix;

public:

    Matrix2D() = default;
    Matrix2D(const Matrix2D& sndMatrix);

    int showSize() const { return matrix.showSize();}
    const  Vector2D<elem_t>& operator [] (const int iX) const {return matrix[iX];};
    Vector2D<elem_t>& operator [] (const int iX) {return matrix[iX];};
    void increaseSize();
};

template <class elem_t>
void Matrix2D<elem_t>::increaseSize()
{


    //zwiększenie ilości wierszy
    this->matrix.increaseSize();
    //powiększenie każdej kolumny - zw. il. kolumn
    for(int i=0;i<this->showSize();++i)
    {
        while(matrix[i].showSize()<matrix.showSize())
            this->matrix[i].increaseSize();
    }

}

template <class elem_t>
Matrix2D<elem_t>::Matrix2D(const Matrix2D& sndMatrix)
{
    while(this->showSize()<sndMatrix.showSize()) increaseSize();
    for(int i=0;i<this->showSize();++i)
    {
        for(int j=0;j<this->showSize();++j)
        {
            (*this)[i][j]=sndMatrix[i][j];
        }
    }
}

#endif //PROJEKT2_MATRIX_TEMPLATE_HH
