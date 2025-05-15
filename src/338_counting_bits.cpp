/*
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

Constraints:

    0 <= n <= 105

Follow up:

    It is very easy to come up with a solution with a runtime of O(n log n). Can you do it in linear time O(n) and possibly in a single pass?
    Can you do it without using any built-in function (i.e., like __builtin_popcount in C++)?
*/

#include <cmath>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        if (n == 0) {
            return {0};
        }
        const std::vector<int> base = {0,1,1,2};
        const int m = std::ceil(std::log(n)/std::log(4));
        std::vector<int> res(n+1, 0);
        int r;
        for (size_t i=0; i <= n; ++i) {
            r = 0;
            for (size_t j=0; j <= m; ++j) {
                r += base[i / static_cast<size_t>(std::pow(4, j)) % 4];
            }
            res[i] = r;
        }
        return res;
    }
};

} // namespace leet

class CountingBits : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(CountingBits, Example1) {
    std::vector<int> result = {0,1,1};
    ASSERT_EQ(s.countBits(2), result);
}

TEST_F(CountingBits, Example2) {
    std::vector<int> result = {0,1,1,2,1,2};
    ASSERT_EQ(s.countBits(5), result);
}

TEST_F(CountingBits, Example3) {
    std::vector<int> result = {0,1,1,2,1};
    ASSERT_EQ(s.countBits(4), result);
}

TEST_F(CountingBits, Case7) {
    std::vector<int> result = {0};
    ASSERT_EQ(s.countBits(0), result);
}
