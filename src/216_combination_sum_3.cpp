/*
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

    Only numbers 1 through 9 are used.
    Each number is used at most once.

Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:

Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Example 3:

Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.

Constraints:

    2 <= k <= 9
    1 <= n <= 60
*/

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    vector<vector<int>> helper(int k, int n) {
        if (k == 1) {
            std::vector<std::vector<int>> v;
            for (int i = 1; i <= std::min(n - k + 1, 9); ++i) {
                v.push_back(std::vector<int>(1, i));
            }
            return v;
        } else {
            std::vector<std::vector<int>> v;
            for (const auto& e : helper(k - 1, n)) {
                for (int i = e.back() + 1; i <= std::min(n - k + 1, 9); ++i) {
                    int s = 0;
                    for (const auto& p : e) {
                        s += p;
                    }
                    if (s + i <= n) {
                        v.push_back(e);
                        v.back().push_back(i);
                    }
                }
            }
            return v;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        /* TODO: solution was accepted but is rather slow, pls improve it by:
         * - preventing all these (re)allocations of vectors
         * - don't recalculate full sum on every layer, reuse results
         * - don't add sequences with wrong sum in the final layer that would need to be filtered out again */
        std::vector<std::vector<int>> v;
        auto o = helper(k, n);
        for (const auto& e : o) {
            int s = 0;
            for (const auto& p : e) {
                s += p;
            }
            if (s == n) {
                v.push_back(e);
            }
        }
        return v;
    }
};

} // namespace leet

class CombinationSum3 : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(CombinationSum3, Example1) {
    std::vector<std::vector<int>> result = {{1,2,4}};
    ASSERT_EQ(s.combinationSum3(3, 7), result);
}

TEST_F(CombinationSum3, Example2) {
    std::vector<std::vector<int>> result = {{1,2,6},{1,3,5},{2,3,4}};
    ASSERT_EQ(s.combinationSum3(3, 9), result);
}

TEST_F(CombinationSum3, Example3) {
    std::vector<std::vector<int>> result = {};
    ASSERT_EQ(s.combinationSum3(4, 1), result);
}

TEST_F(CombinationSum3, Case10) {
    std::vector<std::vector<int>> result = {};
    ASSERT_EQ(s.combinationSum3(2, 18), result);
}

TEST_F(CombinationSum3, Case19) {
    std::vector<std::vector<int>> result = {{1,5},{2,4}};
    ASSERT_EQ(s.combinationSum3(2, 6), result);
}
