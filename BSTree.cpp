#include "BSTree.hpp"
template <typename T>
BSTree<T>::BSTree(const BSTree<T> &bst) {
	this->clone(bst);
}
template <typename T>
BSTree<T>::BSTree(const BSTree<T> &&bst) {
	this->ltree=bst.ltree;
	this->rtree=bst.rtree;
	this->value=bst.value;
	this->height=bst.height;

	this->ltree=NULL;
	this->rtree=NULL;
}
template <typename T>
BSTree<T>::~BSTree(){
	delete ltree;
	delete rtree;
}
template <typename T>
BSTree<T>& BSTree<T>::operator = (const BSTree<T> &bst) {	
	clone(bst);
	return *this;
}
template <typename T>
BSTree<T>& BSTree<T>::operator = (const BSTree<T> &&bst) {	
	this->ltree=bst.ltree;
	this->rtree=bst.rtree;
	this->value=bst.value;
	this->height=bst.height;

	this->ltree=NULL;
	this->rtree=NULL;

	return *this;
}
template <typename T>
void BSTree<T>::clone (const BSTree<T> &bst) {
	delete ltree;
	delete rtree;
	height=bst.height;
	if (isEmpty()) return;
	if (bst.ltree!=NULL) {
		ltree=new BSTree<T>();
		ltree->clone(*(bst.ltree));
	}
	else ltree=NULL;
	if (bst.rtree!=NULL) {
		rtree=new BSTree<T>();
		rtree->clone(*(bst.ltree));
	}
	else rtree=NULL;
	value=bst.value;
}
template <typename T>
void BSTree<T>::insert(const T &value) {
	if (isEmpty()) {
		this->value=value;
		height = 0;
		return;
	}

	BSTree<T> *cur=this, *pcur=NULL, *nxt;
	
	while (true) {
		if (value>cur->value) {
			nxt=cur->rtree;
			cur->rtree=pcur;
		}
		else if (value<cur->value) {
			nxt=cur->ltree;
			cur->ltree=pcur;
		}
		else break;
		pcur=cur;
		cur=nxt;	
		if (cur==NULL) {
			cur=new BSTree(value);
			break;
		}
	}
	
	while (true) {
		if (pcur==NULL) break;
		
		nxt = value > pcur->value ? pcur->rtree : pcur->ltree;
		(value > pcur->value ? pcur->rtree : pcur->ltree) = cur;

		pcur->height=0;
		if (pcur->ltree!=NULL)
			pcur->height=std::max(pcur->height, pcur->ltree->height+1);
		if (pcur->rtree!=NULL)
			pcur->height=std::max(pcur->height, pcur->rtree->height+1);
		
		cur=pcur;
		pcur=nxt;
	}
}
template <typename T>
void BSTree<T>::remove(const T &value) {
	if (isEmpty()) return;
	if (height==0){
		if (this->value==value) height--;
		return;
	}
	BSTree<T> *cur=this, *pcur=NULL, *nxt;

	while (true) {
		if (value>cur->value) {
			nxt=cur->rtree;
			cur->rtree=pcur;
		}
		else if (value<cur->value) {
			nxt=cur->ltree;
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
		BSTree<T> *tmp= (BSTree<T> *) ((unsigned long long) cur->rtree | (unsigned long long)cur->ltree);
		cur->rtree=tmp->rtree, cur->ltree=tmp->ltree, cur->value=tmp->value, cur->height=tmp->height;
		tmp->rtree=tmp->ltree=NULL;
		delete tmp;
	}
	else {
		BSTree<T> *inorder_successor=cur->rtree;
		while (inorder_successor->ltree!=NULL) inorder_successor=inorder_successor->ltree;
		T tmp=inorder_successor->value;
		cur->remove(tmp);
		cur->value=tmp;
	}

	while (true) {
		if (pcur==NULL) break;
		
		nxt = value > pcur->value ? pcur->rtree : pcur->ltree;
		(value > pcur->value ? pcur->rtree : pcur->ltree) = cur;

		pcur->height=0;
		if (pcur->ltree!=NULL)
			pcur->height=std::max(pcur->height, pcur->ltree->height+1);
		if (pcur->rtree!=NULL)
			pcur->height=std::max(pcur->height, pcur->rtree->height+1);
		
		cur=pcur;
		pcur=nxt;
	}
}
template <typename T>
int BSTree<T>::getHeight() const {
	return height;
}

template <typename T>
bool BSTree<T>::isEmpty() const {
	return height<0;
}

/*template <typename T>
void BSTree<T>::print(std::ostream &os,int depth) const {
	return print_t();
	if (isEmpty()) {
		std::cout << "empty tree!\n";
		return;
	}
	if (rtree != NULL) rtree->print(os,depth+1);
	for (int i = 0; i < depth; i++) os << "\t";
	os << value << std::endl << std::endl;
	if (ltree != NULL) ltree->print(os,depth+1);
}

template <typename T>
int BSTree<T>::_print_t(const BSTree<int> *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->value);

    int left  = _print_t(tree->ltree,  1, offset,                depth + 1, s);
    int right = _print_t(tree->rtree, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

template <typename T>
void BSTree<T>::print_t() const
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(this, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

template class BSTree<int>;
*/