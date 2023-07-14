#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

#include "BSTree.hpp"
template <typename T>
class SplayTree : public BSTree<T> {
	public:
	SplayTree(): BSTree<T>(){}
	SplayTree (const T &v): BSTree<T>(v){} //empty constructor
	SplayTree (const BSTree<T> &bst): BSTree<T>(bst) {}; //copy constructor
	SplayTree<T>& operator = (const BSTree<T> &bst) {BSTree<T>::operator=(bst);}
	void insert(const T &value);
	void remove(const T &value);
	private:
	void rotateWithLeftChild();
	void rotateWithRightChild();
	void doubleWithLeftChild();
	void doubleWithRightChild();
};

#endif
