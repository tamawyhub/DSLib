#include <List.hpp>

template <typename T>
List<T>::List()
{
    _size=0;
    firstNode=lastNode=NULL;
}

template <typename T>
List<T>::List(List<T> &list)
{
    *this=list;
}

template <typename T>
List<T>::List(List<T> &&list)
{
    *this=list;
}

template <typename T>
List<T> &List<T>::operator = (List<T> &list)
{
    _size=size;
    Node<T> *src = list.firstNode;
    Node<T> *dst = this->firstNode;
    while (dst!=NULL && src!=NULL)
    {
        src->value = dst->value;
        src = src->next;
        dst = dst->next;
    }
    
    if (dst==NULL)
    {
        while (src!=NULL)
        {
            this->pushBack(src->value);
        }
    }
    else
    {
        const size_t diff = list.size - this->size;
        while (diff--){
            this->popBack();
        }
    }
    return *this;
}

template <typename T>
List<T> &List<T>::operator = (List<T> &&list)
{
    this->_size = list._size;
    this->firstNode = list.firstNode;
    this->lastNode = list.lastNode;
    list.firstNode = list.lastNode = NULL;
    return *this;
}

template <typename T>
T List<T>::front() const
{
    return firstNode->value; 
}

template <typename T>
const T List<T>::back() const
{
    return firstNode->value; 
}

template <typename T>
void pushFront(const T& value)
{

}

template <typename T>
void pushBack(const T& value)
{

}


template <typename T>
class List {
    public:
    List();
    List(const List<T>&);
    List(List<T>&&);
    ~List();

    const T front() const;
    const T back() const;
    void pushFront();
    void pushBack();
    T &&popFront();
    T &&popBack();
    T &popFront();
    T &popBack();
    size_t size();

    private:
    List<T>::Node *firstNode;
    List<T>::Node *lastNode;
    size_t _size;
    struct Node {
        T value;
        List<T>::Node *next;
    };
};
