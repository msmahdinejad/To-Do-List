#ifndef LINKLIST_H
#define LINKLIST_H



template <typename T>
class node {
private:
    T * data;
    node<T> * next;
public:
    node(T * d);
    T * getData();
    void setNext(node<T> * next);
    node<T> * getNext();
};

template <typename T> node<T>::node(T * d)
{
    data = d;
    next = nullptr;
}
template <typename T> T * node<T>::getData()
{
    return data;
}
template <typename T> void node<T>::setNext(node<T> * Next)
{
    next = Next;
}
template <typename T> node<T> * node<T>::getNext()
{
    return next;
}
template <typename Z>
class LinkList
{
private:
    node<Z> * head;
    int size ;

public:
    LinkList();
    ~LinkList();
    void deleteList();
    void push_front(Z * Data);
    node<Z> * getHead();
    void setNode(node<Z> * A, node<Z> * B);
    void setSize(int Size);
    int & getSize();
};
template <typename Z> void LinkList<Z>::setNode(node<Z> * A, node<Z> * B)
{
    A = B;
}
template <typename Z> void LinkList<Z>::setSize(int Size)
{
    size = Size;
}
template <typename Z> LinkList<Z>::LinkList(){head = nullptr; size = 0;}
template <typename Z> LinkList<Z>::~LinkList()
{
    node<Z> * tmp = this->head;

    while(tmp != 0)
    {
        node<Z> * tmp2 = tmp->getNext();
        delete tmp;
        tmp = tmp2;
    }
    this->head = nullptr ;
    this->size = 0 ;
}
template <typename Z> void LinkList<Z>::deleteList()
{
    node<Z> * tmp = this->head;

    while(tmp != 0)
    {
        node<Z> * tmp2 = tmp->getNext();
        delete tmp;
        tmp = tmp2;
    }
    this->head = nullptr ;
    this->size = 0 ;
}
template <typename Z> void LinkList<Z>::push_front(Z * Data)
{
    node<Z> * tmp = new node<Z>(Data);
    tmp->setNext(this->head);
    this->head = tmp;
    this->size++;
}
template <typename Z> node<Z> * LinkList<Z>::getHead(){return head;}
template <typename Z> int & LinkList<Z>::getSize(){return size;}
#endif // LINKLIST_H
