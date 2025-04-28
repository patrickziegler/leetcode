#include <iostream>
#include <string>

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
