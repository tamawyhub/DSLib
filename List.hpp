#ifndef _LIST_HPP_
#define _LIST_HPP_

template <typename T>
class List {
    public:
    List();
    List(const List<T>&);
    List(List<T>&&);
    List<T>& operator = (List<T>&);
    List<T>& operator = (List<T>&&);
    ~List();

    T front() const;
    T back() const;
    void pushFront(const T&);
    void pushBack(const T&);
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

#endif