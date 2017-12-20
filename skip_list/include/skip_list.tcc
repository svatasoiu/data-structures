#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "skip_list.hpp"

namespace skiplist {

template <class K, class V>
SkipList<K,V>::SkipList(double p, int numLevels) : max_level(numLevels - 1), p(p), max_used_level(0) {
    static_assert(std::is_integral<K>::value, "Key type must be integral");
    head = new SkipListNode<K,V>(0,0,max_level);
    memset(head->shortcuts, 0, sizeof(head->shortcuts));
}

template <class K, class V>
SkipList<K,V>::~SkipList() { 
    auto node = head;
    while (node != nullptr) {
        auto next = node->shortcuts[0];
        delete node;
        node = next;
    }
}

template <class K, class V>
std::experimental::optional<V> SkipList<K,V>::find(K key) const { 
    int level = max_used_level;
    auto currentNode = head;

    while (level >= 0) {
        while (currentNode->shortcuts[level] && (currentNode->shortcuts[level]->key <= key))
            currentNode = currentNode->shortcuts[level];

        if (currentNode->key == key)
            return currentNode->value;
        --level;
    }
    return {};
}

template <class K, class V>
void SkipList<K,V>::insert(K key, V value) { 
    int level = generate_level();
    int level_of_this_entry = level;
    max_used_level = std::max(max_used_level, level);
    auto newNode = new SkipListNode<K,V>(key, value, level);
    memset(newNode->shortcuts, 0, sizeof(newNode->shortcuts));
    auto currentNode = head;

    level = max_used_level;
    while (level >= 0) {
        while (currentNode->shortcuts[level] && (currentNode->shortcuts[level]->key <= key)) {
            currentNode = currentNode->shortcuts[level];
        }

        if (currentNode->key == key)
            break;
        
        if (level <= level_of_this_entry) {
            auto oldNext = currentNode->shortcuts[level];
            currentNode->shortcuts[level] = newNode;
            newNode->shortcuts[level] = oldNext;
        }
        --level;
    }
}

template <class K, class V>
void SkipList<K,V>::remove(K key) { 
    SkipListNode<K,V>* prevNode = nullptr;
    auto currentNode = head;
    int level = max_used_level;
    while (level >= 0) {
        while (currentNode->shortcuts[level] && (currentNode->shortcuts[level]->key <= key)) {
            prevNode = currentNode;
            currentNode = currentNode->shortcuts[level];
        }

        if (currentNode->key == key) {
            prevNode->shortcuts[level] = currentNode->shortcuts[level];
        }
        
        --level;
    }
    if (currentNode->key == key)
        delete currentNode;
}

template <class K, class V>
void SkipList<K,V>::print(std::ostream& os) const { 
    int level = max_level;

    while (level >= 0) {
        auto currentNode = head;
        os << "level " << level << ": ";
        do {
            os << "[" << currentNode->key << "," << currentNode->value << "] -> ";
            currentNode = currentNode->shortcuts[level];
        } while (currentNode);
        os << "NULL\n";
        --level;
    }
}

template <class K, class V>
int SkipList<K,V>::generate_level() const {
    int level = 0; 
    while ((((double) rand() / (RAND_MAX)) < p) && (level < max_level))
        level++;
    return level;
}

}