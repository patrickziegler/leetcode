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
    bool isSubStr(const std::string& s1, const std::string& s2) {
        size_t j=0;
        for (size_t i=0; i < s1.size(); ++i) {
            if (s1[i] == s2[j] && ++j == s2.size()) {
                return true;
            }
        }
        return false;
    }
    int comp(const std::string& s1, const std::string& s2) {
        if (isSubStr(s1, s2)) {
            return s2.size();
        }
        int s = 0;
        for (size_t i=0; i < s2.size(); ++i) {
            std::string s3 = s2;
            s3.erase(i, 1);
            s = std::max(s, comp(s1, s3));
        }
        return  s;
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text2.size() < text1.size()) {
            return comp(text1, text2);
        } else {
            return comp(text2, text1);
        }
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
