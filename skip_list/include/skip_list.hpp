#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <experimental/optional>
#include <list>
#include <iostream>
#include <ostream>
#include <vector>

namespace skiplist {

template <class K, class V>
class SkipListNode {
public:
	SkipListNode(K k, V v, size_t level) : key(k), value(v) {}
	~SkipListNode() {}

	// shortcuts[i] points to shortcut on level i
	SkipListNode<K,V>* shortcuts[30];
	K key;
	V value;
};

template <class K, class V>
class SkipList {
public:
	SkipList(double prob = 0.5, int max_levels = 30);
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
