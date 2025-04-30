/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 105.

Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Constraints:

    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in s are in the range [1, 300].
*/

#include "gtest/gtest.h"

namespace leet {

using namespace std;

static bool isNumeric(const char& c) {
    // ascii: 48 == '0' .. 57 == '9'
    return 48 <= c && c <= 57;
}

class Solution {
public:
    string decodeString(string s) {
        std::string result, buf, n;
        int depth = 0;
        for (const auto& c : s) {
            if (c == '[') {
                ++depth;
            }
            if (c == ']'){
                --depth;
            }
            if (depth > 0) {
                if (!(buf.empty() && c == '[')) {
                    buf += c;
                }
            } else if (isNumeric(c)) {
                n += c;
            } else if (c == ']') {
                buf = decodeString(buf);
                for (int i=0; i < std::stoi(n); ++i) {
                    result += buf;
                }
                buf.clear();
                n.clear();
            } else {
                result += c;
            }
        }
        return result;
    }
};

} // namespace leet

class DecodeString : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(DecodeString, Example1) {
    ASSERT_EQ(s.decodeString("3[a]2[bc]"), "aaabcbc");
}

TEST_F(DecodeString, Example2) {
    ASSERT_EQ(s.decodeString("3[a2[c]]"), "accaccacc");
}

TEST_F(DecodeString, Example3) {
    ASSERT_EQ(s.decodeString("2[abc]3[cd]ef"), "abcabccdcdcdef");
}

TEST_F(DecodeString, Case29) {
    ASSERT_EQ(s.decodeString("100[leetcode]"), "leetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcode");
}
