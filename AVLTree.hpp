#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "BSTree.hpp"
template <typename T>
class AVLTree : public BSTree<T> {
	public:
	AVLTree(): BSTree<T>(){}
	AVLTree (const T &v): BSTree<T>(v){} //empty constructor
	AVLTree (const BSTree<T> &bst): BSTree<T>(bst) {}; //copy constructor
	AVLTree<T>& operator = (const BSTree<T> &bst) {BSTree<T>::operator=(bst);}
	void insert(const T &value);
	void remove(const T &value);
	private:
	void rotateWithLeftChild();
	void rotateWithRightChild();
	void doubleWithLeftChild();
	void doubleWithRightChild();
};

#endif
