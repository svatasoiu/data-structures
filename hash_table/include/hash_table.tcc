#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "hash_table.hpp"

namespace hashtable {

template <typename T>
constexpr bool is_power_of_2(const T x) { 
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");
    return ~(x & (x - 1)); 
}

template <class K, class V, class Hash>
HashTable<K,V,Hash>::HashTable(int initial_size) : _hasher(Hash()), _size(0) {
    _table = std::make_unique<std::vector<std::list<std::pair<K,V>>>>(initial_size);
}

template <class K, class V, class Hash>
HashTable<K,V,Hash>::~HashTable() { }

template <class K, class V, class Hash>
std::experimental::optional<V> HashTable<K,V,Hash>::find(K key) const { 
    const std::list<std::pair<K,V>>& list = _table->at(compute_bucket(key));
    auto res = std::find_if(list.begin(), list.end(), 
        [&key](const std::pair<K,V>& p) { 
            return std::get<0>(p) == key; 
        }
    );

    if (res != list.end())
        return { std::get<1>(*res) };
    return {};  
}

template <class K, class V, class Hash>
void HashTable<K,V,Hash>::insert(K key, V value) { 
    std::list<std::pair<K,V>>& list = _table->at(compute_bucket(key));
    auto res = std::find_if(list.begin(), list.end(), 
        [&key](const std::pair<K,V>& p) { 
            return std::get<0>(p) == key; 
        }
    );

    if (res != list.end())
        return;

    list.push_back({key, value});
    ++_size;

    double load_factor = _size / (double)_table->size();
    if (load_factor > 0.75) {
        auto newTable = std::make_unique<std::vector<std::list<std::pair<K,V>>>>(_table->size() * 2);
        for (const std::list<std::pair<K,V>>& list : *_table) {
            for (const std::pair<K,V>& p : list) {
                newTable->at(compute_bucket(key)).push_back(p);
            }
        }
        _table = std::move(newTable);
    }
}

template <class K, class V, class Hash>
void HashTable<K,V,Hash>::remove(K key) { 
    std::list<std::pair<K,V>>& list = _table->at(compute_bucket(key));
    auto res = std::find_if(list.begin(), list.end(), 
        [&key](const std::pair<K,V>& p) { 
            return std::get<0>(p) == key; 
        }
    );

    if (res != list.end()) {
        list.erase(res);
        --_size;
    }
}

template <class K, class V, class Hash>
size_t HashTable<K,V,Hash>::compute_bucket(K key) const { 
    assert(is_power_of_2(_table->size()) && "hash table size must be power of 2");
    return _hasher(key) & (_table->size() - 1);
}

template <class K, class V, class Hash>
void HashTable<K,V,Hash>::print(std::ostream& os) const { 
}

}