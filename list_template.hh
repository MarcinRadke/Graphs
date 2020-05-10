#ifndef PROJEKT2_LIST_TEMPLATE_HH
#define PROJEKT2_LIST_TEMPLATE_HH

template <class elem_t>
class node
{
    elem_t elem;
    node<elem_t>* nextNode = nullptr;
    int _idNum = 0;

public:

    node() = default;
    explicit node(elem_t el): elem(el) {}

    //dostep
    elem_t& getElem() {return elem;}
    const node& getNext() const  {return nextNode;}
    node* getNext()  {return nextNode;}
    const int showID() { return _idNum;}

    //modyfikacja
    void setElem(elem_t newElem) {elem=newElem;}
    void setNext(node<elem_t>* newNext) {nextNode=newNext;}

    void setID(int id) {this->_idNum=id;}//nadawanie numeru - uzywane glownie przy tworzeniu
};

template <class elem_t>
class list
{
    node<elem_t>* head;

public:
    list();
    ~list() = default;

    //tworzenie i usuwanie
    void addFront(elem_t);
    void removeFront();
    void removeElem(elem_t); //usuniecie wezla z danym elementem

    //sprawdzanie czy lista jest pusta
    bool isEmpty() const {return !(head);}

    //dostep
    elem_t& front() {return head->getElem();}
    node<elem_t>* getHead() { return head;} //do tworzenia referencji do pozycji

};

/*
 * konstruktor - tworzenie pustej listy
 */
template <class elem_t>
list<elem_t>::list()
    :head(nullptr) {};

template <class elem_t>
void list<elem_t>::removeFront()
{
    node<elem_t>* old = head;
    this->head = old->getNext();
    delete old;

}

/*
 * Dodawanie elementu
 */
template <class elem_t>
void list<elem_t>::addFront(elem_t newElem)
{
    auto nodeToAdd = new node<elem_t>(newElem);
    if(head) nodeToAdd->setNext(this->head);
    this->head = nodeToAdd;

    //nadanie numeru id wezla
    if(head->getNext()) head->setID(head->getNext()->showID()+1);
    else head->setID(0);
}

/*
 * Dodawanie elementu
 */
template <class elem_t>
void list<elem_t>::removeElem(elem_t elemToRm)
{
    node<elem_t>* prevNode;
    node<elem_t>* nextNode;

    if(this->head().getElem()!=elemToRm)//jeśli jest z przodu listy
        this->removeFront();            //usun przod
    else
    {
        prevNode = this->head().getNext();
        while (!prevNode->getNext().getElem()!=elemToRm)//znajdz poprzedni
            prevNode = prevNode->getNext();
        nextNode = prevNode->getNext().getNext();       //znajdz nastepny

        delete prevNode->getNext();                     //usun
        prevNode->setNext(nextNode);                    //polacz poprzedi i nastepny
    }
}



#endif //PROJEKT2_LIST_TEMPLATE_HH
