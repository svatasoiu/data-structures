#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <experimental/optional>
#include <list>
#include <iostream>
#include <ostream>
#include <vector>

namespace skiplist {

template <class T>
struct blocked_allocator {
	typedef T value_type;

	blocked_allocator(int BlockSize=1024) noexcept : _freeList(BlockSize, nullptr), _numFree(0), _blockSize(BlockSize) {}
	template <class U> blocked_allocator (const blocked_allocator<U>&) noexcept {}

	T* allocate (std::size_t n) {
		// n /= sizeof(T);
		if (_numFree == 0) {
			void *block = malloc(_blockSize * sizeof(T));
			for (size_t i = 0; i < _blockSize; ++i)
				_freeList[i] = reinterpret_cast<T*>(static_cast<char*>(block) + i * sizeof(T));
			_numFree = _blockSize;
		}
		return _freeList[--_numFree];
	}

	void deallocate (T* p, std::size_t n) { 
		// for (size_t i = 0; i < n; ++i)
		// 	_freeList.push_back(static_cast<T*>(static_cast<char*>(p) + i * sizeof(T)));
	}

private:
	int _numFree;
	int _blockSize;
	std::vector<T*> _freeList;
};

// template <class K, class V> class SkipListNode;
// blocked_allocator<SkipListNode<uint64_t,uint64_t>> allocator;

template <class K, class V>
class SkipListNode {
public:
	SkipListNode(K k, V v, size_t level) : key(k), value(v) {}
	~SkipListNode() {}

	// static void *operator new(size_t size) {
	// 	return allocator.allocate(size);
	// }
	// static void operator delete(void *block) { 
	// 	// allocator.deallocate(block, size);
    // }

	// shortcuts[i] points to shortcut on level i
	SkipListNode<K,V>* shortcuts[16];
	K key;
	V value;
};

template <class K, class V>
class SkipList {
public:
	SkipList(double prob = 0.5, int max_levels = 16);
	~SkipList();

	std::experimental::optional<V> find(K key) const;
	void insert(K key, V value);
	void remove(K key);
	void print(std::ostream& os) const;
private:
	double p;
	int max_level;
	int max_used_level;
	int generate_level() const;
	SkipListNode<K,V>* head;
};

}

#include "skip_list.tcc"

#endif
