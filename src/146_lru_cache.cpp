/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

    LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    int get(int key) Return the value of the key if the key exists, otherwise return -1.
    void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

The functions get and put must each run in O(1) average time complexity.

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4

Constraints:

    1 <= capacity <= 3000
    0 <= key <= 104
    0 <= value <= 105
    At most 2 * 105 calls will be made to get and put.
*/

#include <list>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

template <typename K, typename V>
class GenericLRUCache {
public:
    GenericLRUCache(size_t capacity) : m_capacity{capacity} {
        m_cache.reserve(capacity);
    }

    auto set(K key, V value) noexcept -> std::optional<K> {
        std::optional<K> evicted;
        const auto it = m_cache.find(key);
        if (it != m_cache.end()) {
            it->second.second = value;
            m_order.splice(m_order.end(), m_order, it->second.first);
            it->second.first = std::prev(m_order.end());
        } else {
            if (m_order.size() == m_capacity) {
                evicted = std::move(*m_order.begin());
                m_order.pop_front();
                m_cache.erase(*evicted);
            }
            m_order.push_back(key);
            m_cache.emplace(key, std::make_pair(std::prev(m_order.end()), value));
        }
        return evicted;
    }

    auto get(K key) noexcept -> std::optional<V> {
        std::optional<V> result;
        const auto it = m_cache.find(key);
        if (it != m_cache.end()) {
            result = it->second.second;
            m_order.splice(m_order.end(), m_order, it->second.first);
            it->second.first = std::prev(m_order.end());
        }
        return result;
    }

private:
    std::list<K> m_order;
    std::unordered_map<K, std::pair<decltype(m_order.begin()), V>> m_cache;
    const size_t m_capacity;
};

class LRUCache {
public:
    LRUCache(int capacity) : m_cache{static_cast<size_t>(capacity)} {}

    int get(int key) {
        const auto ret = m_cache.get(key);
        return (ret) ? ret.value() : -1;
    }

    void put(int key, int value) {
        m_cache.set(key, value);
    }

private:
    GenericLRUCache<int, int> m_cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

} // namespace leet

class LRUCacheTest : public testing::Test {
};

TEST_F(LRUCacheTest, Example1) {
    leet::LRUCache cache{2};
    cache.put(1, 1); // cache is {1=1}
    cache.put(2, 2); // cache is {1=1, 2=2}
    ASSERT_EQ(cache.get(1), 1); // return 1
    cache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    ASSERT_EQ(cache.get(2), -1); // returns -1 (not found)
    cache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    ASSERT_EQ(cache.get(1), -1); // return -1 (not found)
    ASSERT_EQ(cache.get(3), 3); // return 3
    ASSERT_EQ(cache.get(4), 4); // return 4
}

TEST_F(LRUCacheTest, Basics) {
    leet::GenericLRUCache<std::string, int> cache{3};

    // nullopt shall be returned when key does not exist
    ASSERT_EQ(cache.get("a"), std::nullopt);

    // oldest key shall be evicted when capacity exceeded
    ASSERT_EQ(cache.set("a", 3), std::nullopt);
    ASSERT_EQ(cache.set("b", 4), std::nullopt);
    ASSERT_EQ(cache.set("c", 5), std::nullopt);
    ASSERT_EQ(cache.set("d", 6), "a");

    // 'get' shall properly update last usage
    ASSERT_EQ(cache.get("a"), std::nullopt);
    ASSERT_EQ(cache.get("b"), 4);
    ASSERT_EQ(cache.get("c"), 5);
    ASSERT_EQ(cache.set("e", 7), "d");

    // update of existing key shall never evict any other
    ASSERT_EQ(cache.set("e", 8), std::nullopt);
    ASSERT_EQ(cache.get("e"), 8);
}
