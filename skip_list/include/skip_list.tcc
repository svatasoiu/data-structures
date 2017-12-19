#include "skip_list.hpp"

namespace skiplist {

template <class K, class V>
SkipList<K,V>::SkipList() { }

template <class K, class V>
SkipList<K,V>::~SkipList() { }

template <class K, class V>
std::experimental::optional<V> SkipList<K,V>::find(K key) { }

template <class K, class V>
void SkipList<K,V>::insert(K key, V value) { }

template <class K, class V>
void SkipList<K,V>::remove(K key) { }

}