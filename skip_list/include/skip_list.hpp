#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <experimental/optional>

namespace skiplist {

template <class K, class V>
class SkipList {
public:
	SkipList();
	~SkipList();

	std::experimental::optional<V> find(K key);
	void insert(K key, V value);
	void remove(K key);
private:
	//
};

}

#include "skip_list.tcc"

#endif
