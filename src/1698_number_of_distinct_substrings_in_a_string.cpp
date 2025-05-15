/*
Given a string s, return the number of distinct substrings of s.

A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string and any number (possibly zero) from the back of the string.

Example 1:

Input: s = "aabbaba"
Output: 21
Explanation: The set of distinct strings is ["a","b","aa","bb","ab","ba","aab","abb","bab","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba","aabbaba"]

Example 2:

Input: s = "abcdefg"
Output: 28

Constraints:

    1 <= s.length <= 500
    s consists of lowercase English letters.

Follow up: Can you solve this problem in O(n) time complexity?
*/

#include <unordered_set>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    size_t numberOfSubstrings(const std::string& input)
    {
        // TODO: compare with https://leetcode.ca/2020-07-24-1698-Number-of-Distinct-Substrings-in-a-String/
        size_t hash, i, j, n = input.size();
        auto calculate_hash = std::hash<std::string>();
        std::unordered_set<size_t> hashes;
        hashes.reserve((n * n + n) / 2); // max. number of substrings
        for (i = 0; i < n; ++i) {
            for (j = n - i; j > 0; --j) {
                hash = calculate_hash(input.substr(i, j));
                if (hashes.insert(hash).second == false) {
                    break;
                }
            }
        }
        return hashes.size();
    }
};

} // namespace leet

class NumberOfDistinctSubstringsInAString : public testing::Test {
public:
    leet::Solution s;
    std::string input;
};

TEST_F(NumberOfDistinctSubstringsInAString, Example1) {
    input = "aabbaba";
    ASSERT_EQ(s.numberOfSubstrings(input), 21);
}

TEST_F(NumberOfDistinctSubstringsInAString, Example2) {
    input = "abcdefg";
    ASSERT_EQ(s.numberOfSubstrings(input), 28);
}

TEST_F(NumberOfDistinctSubstringsInAString, HackerRankReference1) {
    input = "abcde";
    ASSERT_EQ(s.numberOfSubstrings(input), 15);
}

TEST_F(NumberOfDistinctSubstringsInAString, HackerRankReference2) {
    input = "kincenvizh";
    ASSERT_EQ(s.numberOfSubstrings(input), 53);
}

TEST_F(NumberOfDistinctSubstringsInAString, ShorterTextTest) {
    input = "Same an quit most an. Admitting an mr disposing sportsmen. Tried on cause no spoil arise plate. Longer ladies valley get esteem use led six. Middletons resolution advan.";
    ASSERT_EQ(s.numberOfSubstrings(input), 14141);
}

TEST_F(NumberOfDistinctSubstringsInAString, LongerTextTest) {
    input = "Remember outweigh do he desirous no cheerful. Do of doors water ye guest. We if prosperous comparison middletons at. Park we in lose like at no. An so to preferred convinced distrusts he determine. In musical me my placing clothes comfort pleased hearing. Any residence you satisfied and rapturous certainty two. Procured outweigh as outlived so so. On in bringing graceful proposal blessing of marriage outlived. Son rent face our loud near.";
    ASSERT_EQ(s.numberOfSubstrings(input), 97084);
}

TEST_F(NumberOfDistinctSubstringsInAString, RepetitiveLongerTextTest) {
    input = "abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc";
    ASSERT_EQ(s.numberOfSubstrings(input), 4605);
}
