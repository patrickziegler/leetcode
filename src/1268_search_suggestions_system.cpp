/*
You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of searchWord is typed.

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
After typing mou, mous and mouse the system suggests ["mouse","mousepad"].

Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Explanation: The only word "havana" will be always suggested while typing the search word.

Constraints:

    1 <= products.length <= 1000
    1 <= products[i].length <= 3000
    1 <= sum(products[i].length) <= 2 * 10**4
    All the strings of products are unique.
    products[i] consists of lowercase English letters.
    1 <= searchWord.length <= 1000
    searchWord consists of lowercase English letters.
*/

#include <algorithm>
#include <stack>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

constexpr static const size_t MAX_SUGGESTIONS = 3;

struct Trie {
    Trie() = delete;
    explicit Trie(const char& character) : c{character} {}
    explicit Trie(const std::vector<std::string>& words) {
        for (const auto& w : words) {
            insert(w);
        }
    }
    bool operator==(char other) const {
        return c == other;
    }
    void insert(const std::string& word) {
        Trie *ptr = this, *prev = nullptr;
        std::vector<Trie>::iterator it;
        for (const auto& c : word) {
            it = std::find(ptr->children.begin(), ptr->children.end(), c);
            if (it != ptr->children.end()) {
                ptr = &(*it);
            } else {
                ptr->children.emplace_back(c);
                if (ptr->children.size() > 1) {
                    prev = ptr;
                    std::sort(prev->children.begin(), prev->children.end(), [](const Trie& a, const Trie& b) {
                        return a.c > b.c;
                    });
                    it = std::find(prev->children.begin(), prev->children.end(), c);
                    ptr = &(*it);
                } else {
                    ptr = &(ptr->children.back());
                }
            }
        }
        ptr->end = true;
    }
    std::vector<std::string> getSuggestion(std::string prefix, size_t n) const {
        std::vector<std::string> res;
        std::stack<std::pair<const Trie*, std::string>> s; // depth-first search
        s.push({this, prefix});
        while (!s.empty() && res.size() < n) {
            auto [ptr, word] = s.top();
            s.pop();
            word += ptr->c;
            for (const auto& child : ptr->children) {
                s.push({&child, word});
            }
            if (ptr->end || ptr->children.size() == 0) {
                res.push_back(word);
            }
        }
        return res;
    }
    char c = ' ';
    bool end = false;
    std::vector<Trie> children;
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        std::vector<std::vector<std::string>> res;
        Trie t{products};
        const Trie *ptr = &t;
        for (size_t i=0; i < searchWord.size(); ++i) {
            const auto& it = std::find(ptr->children.begin(), ptr->children.end(), searchWord[i]);
            if (it == ptr->children.end()) {
                break;
            }
            ptr = &(*it);
            res.push_back(ptr->getSuggestion(searchWord.substr(0, i), MAX_SUGGESTIONS));
        }
        while (res.size() < searchWord.size()) {
            res.push_back({});
        }
        return res;
    }
};

} // namespace leet

class SearchSuggestionsSystem : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(SearchSuggestionsSystem, Example1) {
    std::vector<std::string> products = {"mobile", "mouse", "moneypot", "monitor", "mousepad"};
    std::vector<std::vector<std::string>> result = {
        {"mobile", "moneypot", "monitor"},
        {"mobile", "moneypot", "monitor"},
        {"mouse", "mousepad"},
        {"mouse", "mousepad"},
        {"mouse", "mousepad"}
    };
    ASSERT_EQ(s.suggestedProducts(products, "mouse"), result);
}

TEST_F(SearchSuggestionsSystem, Example2) {
    std::vector<std::string> products = {"havana"};
    std::vector<std::vector<std::string>> result = {
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}
    };
    ASSERT_EQ(s.suggestedProducts(products, "havana"), result);
}

TEST_F(SearchSuggestionsSystem, Case5) {
    std::vector<std::string> products = {"havana"};
    std::vector<std::vector<std::string>> result = {
        {}, {}, {}, {}, {}, {}, {}
    };
    ASSERT_EQ(s.suggestedProducts(products, "tatiana"), result);
}
