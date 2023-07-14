#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <iostream>
#include <stdlib.h>
template <typename T>
class BSTree {
	public:
	BSTree(): ltree(NULL), rtree(NULL), height(-1){}
	BSTree (const T &v): value(v), ltree(NULL), rtree(NULL), height(0) {} //empty constructor
	BSTree (const BSTree<T> &); //copy constructor
	~BSTree();
	BSTree<T>& operator = (const BSTree<T> &);
	void clone (const BSTree<T> &);
	virtual void insert(const T &value);
	virtual void remove(const T &value);
	int getHeight() const;
	void print(std::ostream &os=std::cout,int depth=0) const;
	bool isEmpty() const;
	protected:
	T value;
	int height;
	BSTree<T> *ltree,*rtree;
	void print_t() const;
	static inline int _height(BSTree<T> *t) { return (t?t->height:-1);}
	private:
	static int _print_t(const BSTree<int> *, int, int, int, char [20][255]);
};

#endif
