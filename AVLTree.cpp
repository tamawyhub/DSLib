#include "AVLTree.hpp"

template <typename T>
void AVLTree<T>::insert(const T &value){
	if (this->isEmpty()) {
		this->value=value;
		this->height = 0;
		return;
	}

	AVLTree<T> *cur=this, *pcur=NULL, *nxt;
	
	bool rotated_once = false;
	while (true) {
		if (value>cur->value) {
			nxt=(AVLTree<T>*)(cur->rtree);
			cur->rtree=pcur;
		}
		else if (value<cur->value) {
			nxt=(AVLTree<T>*)(cur->ltree);
			cur->ltree=pcur;
		}
		else { rotated_once=true; break; }
		
		pcur=cur;
		cur=nxt;	
		if (cur==NULL) {
			cur=new AVLTree(value);
			break;
		}
	}
	
	while (true) {
		if (!pcur) break;
		nxt = (AVLTree<T> *)(value > pcur->value ? pcur->rtree : pcur->ltree);
		(value > pcur->value ? pcur->rtree : pcur->ltree) = cur;

		pcur->height=std::max(this->_height(pcur->ltree), this->_height(pcur->rtree)) + 1;
		if (rotated_once) ;
		else if (this->_height(pcur->ltree)-this->_height(pcur->rtree) == 2 &&
		    this->_height(cur->ltree) > this->_height(cur->rtree)){
			pcur->rotateWithLeftChild();
			rotated_once=true;
		}
		else if (this->_height(pcur->ltree)-this->_height(pcur->rtree) == 2 &&
			 this->_height(cur->rtree) > this->_height(cur->ltree)){
			pcur->doubleWithLeftChild();
			rotated_once=true;
		}
		else if (this->_height(pcur->rtree)-this->_height(pcur->ltree) == 2 &&
			 this->_height(cur->ltree) > this->_height(cur->rtree)){
			pcur->doubleWithRightChild();
			rotated_once=true;
		}
		else if (this->_height(pcur->rtree)-this->_height(pcur->ltree) == 2 &&
		    this->_height(cur->rtree) > this->_height(cur->ltree)){
			pcur->rotateWithRightChild();
			rotated_once=true;
		}

		cur=pcur;
		pcur=nxt;
	}

}

template <typename T>
void AVLTree<T>::remove(const T &value){
	//BSTree<T>::remove(value);
	if (this->isEmpty()) return;
	if (this->height==0){
		if (this->value==value) this->height--;
		return;
	}
	AVLTree<T> *cur=this, *pcur=NULL, *nxt;

	while (true) {
		if (value>cur->value) {
			nxt=(AVLTree<T>*)(cur->rtree);
			cur->rtree=pcur;
		}
		else if (value<cur->value) {
			nxt=(AVLTree<T>*)(cur->ltree);
			cur->ltree=pcur;
		}
		else break;
		pcur=cur;
		cur=nxt;
		if (cur==NULL) break;
	}

	if (cur==NULL);
	else if (cur->rtree==NULL && cur->ltree==NULL){
		delete cur;
		cur=NULL;
	}
	else if ( (cur->rtree==NULL) ^ (cur->ltree==NULL) ){
		AVLTree<T> *tmp= (AVLTree<T> *) ((unsigned long long) cur->rtree | (unsigned long long)cur->ltree);
		cur->rtree=tmp->rtree, cur->ltree=tmp->ltree, cur->value=tmp->value, cur->height=tmp->height;
		tmp->rtree=tmp->ltree=NULL;
		delete tmp;
	}
	else {
		AVLTree<T> *inorder_successor=(AVLTree<T>*)(cur->rtree);
		while (inorder_successor->ltree!=NULL) inorder_successor=(AVLTree<T>*)(inorder_successor->ltree);
		T tmp=inorder_successor->value;
		cur->remove(tmp);
		cur->value=tmp;
	}

	while (true) {
		if (pcur==NULL) break;
		
		nxt = (AVLTree<T>*)(value > pcur->value ? pcur->rtree : pcur->ltree);
		(value > pcur->value ? pcur->rtree : pcur->ltree) = cur;

		pcur->height=std::max(this->_height(pcur->ltree), this->_height(pcur->rtree))+1;
		
		if (this->_height(pcur->ltree)-this->_height(pcur->rtree) == 2 &&
		    this->_height( ((AVLTree<T>*)(pcur->ltree))->ltree) >= this->_height( ((AVLTree<T>*)(pcur->ltree))->rtree)){
			pcur->rotateWithLeftChild();
		}
		else if (this->_height(pcur->ltree)-this->_height(pcur->rtree) == 2 &&
			 this->_height( ((AVLTree<T>*)(pcur->ltree))->rtree) > this->_height( ((AVLTree<T>*)(pcur->ltree))->ltree)){
			pcur->doubleWithLeftChild();
		}
		else if (this->_height(pcur->rtree)-this->_height(pcur->ltree) == 2 &&
			 this->_height( ((AVLTree<T>*)(pcur->rtree))->ltree) > this->_height( ((AVLTree<T>*)(pcur->rtree))->rtree)){
		
			pcur->doubleWithRightChild();
		}
		else if (this->_height(pcur->rtree)-this->_height(pcur->ltree) == 2 &&
			 this->_height( ((AVLTree<T>*)(pcur->rtree))->rtree) >= this->_height( ((AVLTree<T>*)(pcur->rtree))->ltree)){
	   
			pcur->rotateWithRightChild();
		}

		cur=pcur;
		pcur=nxt;
	}


}

template <typename T>
void AVLTree<T>::rotateWithLeftChild(){
	AVLTree<T> *k2=this,
		   *k1 = (AVLTree<T>*)(k2->ltree),
		   *x = (AVLTree<T>*)(k1->ltree),
		   *y = (AVLTree<T>*)(k1->rtree),
		   *z = (AVLTree<T>*)(k2->rtree);
	k2->ltree=x;
	k2->rtree=k1;
	k1->ltree=y;
	k1->rtree=z;
	std::swap(k1->value, k2->value);
	k1->height=std::max(this->_height(k1->ltree),this->_height(k1->rtree))+1;
	k2->height=std::max(this->_height(k2->ltree),this->_height(k2->rtree))+1;
}

template <typename T>
void AVLTree<T>::doubleWithLeftChild(){
	AVLTree<T> *k1=(AVLTree<T>*)(this->ltree),
		   *k2=(AVLTree<T>*)(k1->rtree),
		   *k3=this,
		   *a=(AVLTree<T>*)(k1->ltree),
		   *b=(AVLTree<T>*)(k2->ltree),
		   *c=(AVLTree<T>*)(k2->rtree),
		   *d=(AVLTree<T>*)(k3->rtree);
	k3->ltree=k1;
	k3->rtree=k2;
	k1->ltree=a;
	k1->rtree=b;
	k2->ltree=c;
	k2->rtree=d;
	std::swap(k2->value, k3->value);
	k1->height=std::max(this->_height(a),this->_height(b))+1;
	k2->height=std::max(this->_height(c),this->_height(d))+1;
	k3->height=std::max(k1->height,k2->height)+1;
}

template <typename T>
void AVLTree<T>::doubleWithRightChild(){
	AVLTree<T> *k3=(AVLTree<T>*)(this->rtree),
		   *k2=(AVLTree<T>*)(k3->ltree),
		   *k1=this,
		   *a=(AVLTree<T>*)(k1->ltree),
		   *b=(AVLTree<T>*)(k2->ltree),
		   *c=(AVLTree<T>*)(k2->rtree),
		   *d=(AVLTree<T>*)(k3->rtree);
	k1->ltree=k2;
	k1->rtree=k3;
	k2->ltree=a;
	k2->rtree=b;
	k3->ltree=c;
	k3->rtree=d;
	std::swap(k1->value, k2->value);
	k2->height=std::max(this->_height(a),this->_height(b))+1;
	k3->height=std::max(this->_height(c),this->_height(d))+1;
	k1->height=std::max(k2->height,k3->height)+1;

}

template <typename T>
void AVLTree<T>::rotateWithRightChild(){
	AVLTree<T> *k1=this,
		   *k2 = (AVLTree<T>*)(k1->rtree),
		   *x = (AVLTree<T>*)(k1->ltree),
		   *y = (AVLTree<T>*)(k2->ltree),
		   *z = (AVLTree<T>*)(k2->rtree);
	k1->rtree=z;
	k1->ltree=k2;
	k2->ltree=x;
	k2->rtree=y;
	std::swap(k1->value, k2->value);
	k2->height=std::max(this->_height(k2->ltree),this->_height(k2->rtree))+1;
	k1->height=std::max(this->_height(k1->ltree),this->_height(k1->rtree))+1;
}

template class AVLTree<int>;
