#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

/*
Two strings are considered close if you can attain one from the other using the following operations:

    Operation 1: Swap any two existing characters.
        For example, abcde -> aecdb
    Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
        For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"

Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.

Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"

Constraints:

    1 <= word1.length, word2.length <= 105
    word1 and word2 contain only lowercase English letters.

Hint 1:
Operation 1 allows you to freely reorder the string.

Hint 2:
Operation 2 allows you to freely reassign the letters' frequencies.
*/

namespace leet {

using namespace std;

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        /* Idea: considering the two hints above,
         * we just need to compare the lists of unique
         * characters and occurences between the words */
        std::unordered_map<char, size_t> stat1, stat2;
        std::vector<char> keys1, keys2;
        std::vector<size_t> counts1, counts2;
        for (const auto& c : word1) {
            ++stat1[c];
        }
        for (const auto& c : word2) {
            ++stat2[c];
        }
        for (const auto& [c, n] : stat1) {
            keys1.push_back(c);
            counts1.push_back(n);
        }
        for (const auto& [c, n] : stat2) {
            keys2.push_back(c);
            counts2.push_back(n);
        }
        std::sort(keys1.begin(), keys1.end());
        std::sort(keys2.begin(), keys2.end());
        std::sort(counts1.begin(), counts1.end());
        std::sort(counts2.begin(), counts2.end());
        return keys1 == keys2 && counts1 == counts2;
    }
};

} // namespace leet

class DetermineIfTwoStringsAreClose : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(DetermineIfTwoStringsAreClose, Example1) {
    ASSERT_EQ(s.closeStrings("abc", "bca"), true);
}

TEST_F(DetermineIfTwoStringsAreClose, Example2) {
    ASSERT_EQ(s.closeStrings("a", "aa"), false);
}

TEST_F(DetermineIfTwoStringsAreClose, Example3) {
    ASSERT_EQ(s.closeStrings("cabbba", "abbccc"), true);
}
