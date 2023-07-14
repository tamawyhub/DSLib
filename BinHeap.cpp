#include <stdlib.h>
#include <BinHeap.hpp>
template <typename T, typename Comp>
int BinHeap <T, Comp> :: resize(size_t new_size){
	if ( ( this->elements = (T *) reallocarray (this->elements,sizeof(T),new_size)) == NULL )
		if (new_size!=0) return FAILED;
	this->size=new_size;
	return SUCCESS;
}

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(size_t size) : nelements(0){
	this->resize(size);
}

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(const BinHeap<T,Comp> &x){
	this->nelements=x.nelements;
	if (this.resize(x.size)!=SUCCESS)
		return FAILED;
	memcpy(elements,x.elements,sizeof(T)*this->nelements);
	return SUCCESS;
}

template <typename T, typename Comp>
BinHeap<T,Comp>::BinHeap(const BinHeap<T,Comp> &&x) : nelements(x.nelements), size(x.size), elements(x.elements){
	x.elements=NULL;
}

template <typename T, typename Comp>
BinHeap<T,Comp>::~BinHeap(){free(elements);}

template <typename T, typename Comp>
int BinHeap<T,Comp>::insert(T& item){
	if (nelements==size)
		if (resize(size<<1)!=SUCCESS) return FAILED;
	auto x = nelements-1;
	while (x!=0){
		if (comp.less(item,elements[x/2]))
			elements[x]=elements[x/2],x/=2;
		else
			break;
	}
	elements[x]=item;
	nelements++;
}
