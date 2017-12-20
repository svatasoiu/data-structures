#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <experimental/optional>
#include <list>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>

namespace hashtable {

template <class K, class V, class Hash = std::hash<K>>
class HashTable {
public:
	HashTable(int initial_size = 1024);
	~HashTable();

	std::experimental::optional<V> find(K key) const;
	void insert(K key, V value);
	void remove(K key);
	void print(std::ostream& os) const;
private:
	size_t compute_bucket(K key) const;

	std::unique_ptr<std::vector<std::list<std::pair<K,V>>>> _table;
	Hash _hasher;
	size_t _size;
};

}

#include "hash_table.tcc"

#endif
