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
    /* imagine a tree where each node represents state of vector v, depth-first search combined with immediately
     * moving to the next path as soon as conditions are not met (i.E. sum is too big) is called backtracing */
    void bt(std::vector<std::vector<int>>& vv, std::vector<int>& v, int k, int n, int j) {
        for (int i=j+1; i<=9 && (n-i)>=0; ++i) {
            if (k > 1) {
                v.push_back(i);
                bt(vv, v, k-1, n-i, i);
                v.pop_back();
            } else if (n - i == 0) {
                v.push_back(i);
                vv.emplace_back(v);
                v.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> vv;
        std::vector<int> v; // path for depth-first search
        bt(vv, v, k, n, 0);
        return vv;
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
