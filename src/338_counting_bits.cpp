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
        std::vector<int> ans(n+1, 0);
        for (size_t i=0; i <= n; ++i) {
            if (i == 0) {
                ans[i] = 0;
            } else if (i == 1) {
                ans[i] = 1;
            } else if (i == 2) {
                ans[i] = 1;
            } else if (i % 2 != 0) {
                // for odd numbers, the result is an increment of the previous (which is already calculated)
                ans[i] = ans[i-1] + 1;
            } else {
                // for even numbers, the result is the same as of their half (which is already calculated)
                ans[i] = ans[i/2];
            }
        }
        return ans;
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
