/*	Binary Heap DS
 * Generic implementation of binary heap data structure.
 * It supports insertion, deletion of minimum element and
 * changing the key.
 * Developed and maintained by: Ahmed Magdy
 */

#ifndef _BINHEAP_H_
#define _BINHEAP_H_

#define DEFAULT_HEAP_SIZE 128
#define SUCCESS 0
#define FAILED 1

template <typename T, typename Comp>
class BinHeap {
private:
	T *elements;
	size_t size;
	size_t nelements;
	Comp comp;
	void heapify(void);
public: 
	BinHeap <T, Comp> (size_t size=DEFAULT_HEAP_SIZE);
	BinHeap <T, Comp> (const BinHeap <T, Comp> &);
	BinHeap <T, Comp> (const BinHeap <T, Comp> &&);
	~BinHeap <T, Comp> ();
	int resize(size_t new_size);
	int insert(T& item);
	int deleteMin(void);
	const T& peekMin(void);
};

#endif
