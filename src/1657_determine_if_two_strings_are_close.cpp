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

    1 <= word1.length, word2.length <= 10**5
    word1 and word2 contain only lowercase English letters.

Hint 1:
Operation 1 allows you to freely reorder the string.

Hint 2:
Operation 2 allows you to freely reassign the letters' frequencies.
*/

#include <algorithm>
#include <unordered_set>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        /* Idea: considering the two hints above,
         * we just need to compare the lists of unique
         * characters and occurences between the words */
        std::unordered_map<char, size_t> stats1, stats2;
        for (const auto& c : word1) {
            stats1.try_emplace(c, 0);
            ++stats1[c];
        }
        for (const auto& c : word2) {
            stats2.try_emplace(c, 0);
            ++stats2[c];
        }
        std::unordered_set<char> chars1, chars2;
        std::vector<size_t> freqs1, freqs2; // occurences are not unique
        for (const auto& [k, v] : stats1) {
            chars1.insert(k);
            freqs1.push_back(v);
        }
        for (const auto& [k, v] : stats2) {
            chars2.insert(k);
            freqs2.push_back(v);
        }
        std::sort(freqs1.begin(), freqs1.end());
        std::sort(freqs2.begin(), freqs2.end());
        return chars1 == chars2 && freqs1 == freqs2;
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

TEST_F(DetermineIfTwoStringsAreClose, Case166) {
    ASSERT_EQ(s.closeStrings("aaabbbbccddeeeeefffff", "aaaaabbcccdddeeeeffff"), false);
}
