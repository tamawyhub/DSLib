#include <stdlib.h>
#include "BinHeap.hpp"
#include <utility>

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(size_t size) : nelements(0){
	this->resize(size);
}

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(const BinHeap<T,Comp> &x){
	this->nelements=x.nelements;
	if (this.resize(x.size)!=SUCCESS)
		return;
	memcpy(elements,x.elements,sizeof(T)*this->nelements);
}

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(const BinHeap<T,Comp> &&x) : nelements(x.nelements), size(x.size), elements(x.elements){
	x.elements=NULL;
}

template <typename T, typename Comp>
BinHeap<T,Comp>::~BinHeap(){free(elements);}

template <typename T, typename Comp>
int BinHeap <T, Comp> :: resize(size_t new_size){
	if ( ( this->elements = (T *) reallocarray (this->elements,sizeof(T),new_size)) == NULL )
		if (new_size!=0) return FAILED;
	this->size=new_size;
	return SUCCESS;
}

template <typename T, typename Comp>
int BinHeap<T,Comp>::insert(T& item){
	if (nelements==size)
		if (resize(size<<1)!=SUCCESS) return FAILED;
	auto idx = nelements;
	while (idx>0){
		size_t parent_idx = (idx-1)/2;
		if (comp.less(item,elements[parent_idx]))
			elements[idx]=elements[parent_idx], idx=parent_idx;
		else
			break;
	}
	elements[idx]=item;
	nelements++;
	return SUCCESS;
}

template <typename T, typename Comp>
int BinHeap<T,Comp>::deleteMin(T& minItem){
	if (nelements==0) return FAILED;
	minItem=std::move(elements[0]);
	size_t idx=0;
	T& lastItem=elements[nelements-1];

	while (true){
		size_t leftIdx=idx*2+1,
			   rightIdx=idx*2+2,
			   minOfThree=nelements-1;

		if (leftIdx < nelements-1){
			T& leftChild = elements[leftIdx];
			if (comp.less(leftChild,elements[minOfThree])){
				minOfThree=leftIdx;
			}
		}

		if (rightIdx < nelements-1){
			T& rightChild = elements[rightIdx];
			if (comp.less(rightChild,elements[minOfThree])){
				minOfThree=rightIdx;
			}
		}

		elements[idx]=std::move(elements[minOfThree]);
		if (minOfThree!=nelements-1){
			idx=minOfThree;
		}
		else{
			break;
		}
	}	
	
	nelements--;

	return SUCCESS;
}

template <typename T, typename Comp>
int BinHeap<T,Comp>::peekMin(T& minItem){
	if (nelements==0) return FAILED;
	minItem=elements[0];
	return SUCCESS;
}