/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

    For example, "ace" is a subsequence of "abcde".

A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:

Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

Constraints:

    1 <= text1.length, text2.length <= 1000
    text1 and text2 consist of only lowercase English characters.
*/

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // TODO: reduce to O(n) memory footprint, add explaination
        std::vector<std::vector<int>> dp(text1.size()+1, std::vector<int>(text2.size()+1, 0));
        for (size_t i=1; i <= text1.size(); ++i) {
            for (size_t j=1; j <= text2.size(); ++j) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }
};

} // namespace leet

class LongestCommonSubsequence : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(LongestCommonSubsequence, Example1) {
    ASSERT_EQ(s.longestCommonSubsequence("abcde", "ace"), 3);
}

TEST_F(LongestCommonSubsequence, Example2) {
    ASSERT_EQ(s.longestCommonSubsequence("abc", "abc"), 3);
}

TEST_F(LongestCommonSubsequence, Example3) {
    ASSERT_EQ(s.longestCommonSubsequence("abc", "def"), 0);
}

TEST_F(LongestCommonSubsequence, Case5) {
    ASSERT_EQ(s.longestCommonSubsequence("psnw", "vozsh"), 1);
}
