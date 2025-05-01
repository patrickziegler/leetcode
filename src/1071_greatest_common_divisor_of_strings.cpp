/*
For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).

Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.

Example 1:

Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

Example 2:

Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

Example 3:

Input: str1 = "LEET", str2 = "CODE"
Output: ""

Constraints:

    1 <= str1.length, str2.length <= 1000
    str1 and str2 consist of English uppercase letters.
*/

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    bool isDivisor(const string& str1, const string& gcd) {
        for (size_t j = 0; j < str1.size(); j += gcd.size()) {
            if (str1.substr(j, gcd.size()) != gcd) {
                return false;
            }
        }
        return true;
    }
    string gcdOfStrings(string str1, string str2) {
        for (size_t i = std::min(str1.size(), str2.size()); i > 0; --i) {
            if (str1.size() % i || str2.size() % i) {
                continue;
            }
            const auto gcd = str1.substr(0, i);
            if (!isDivisor(str1, gcd) || !isDivisor(str2, gcd)) {
                continue;
            }
            return gcd;
        }
        return "";
    }
};

} // namespace leet

class GreatestCommonDivisorOfStrings : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(GreatestCommonDivisorOfStrings, Example1) {
    ASSERT_EQ(s.gcdOfStrings("ABCABCABC", "ABCABC"), "ABC");
}

TEST_F(GreatestCommonDivisorOfStrings, Example2) {
    ASSERT_EQ(s.gcdOfStrings("ABABAB", "ABAB"), "AB");
}

TEST_F(GreatestCommonDivisorOfStrings, Example3) {
    ASSERT_EQ(s.gcdOfStrings("LEET", "CODE"), "");
}
