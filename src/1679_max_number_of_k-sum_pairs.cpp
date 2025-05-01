/*
You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.

Return the maximum number of operations you can perform on the array.

Example 1:

Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.

Example 2:

Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.

Constraints:

    1 <= nums.length <= 10**5
    1 <= nums[i] <= 10**9
    1 <= k <= 10**9
*/

#include <algorithm>
#include <cmath>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {

        // sort array to be able to create group stats
        std::sort(nums.begin(), nums.end());

        // calculate groups stats
        std::unordered_map<int, int> stat;
        int current = nums[0], count = 0;
        for (const int n : nums) {
            if (n != current) {
                stat[current] = count;
                current = n;
                count = 1;
            } else {
                ++count;
            }
        }
        stat[current] = count;

        // calculate number of operations
        double ops = 0.0;
        int disj;
        for (const auto& [i, n] : stat) {
            disj = k - i;
            if (stat.find(disj) != stat.end()) {
                if (2 * i == k) {
                    ops += std::floor(stat[i] / 2.0);
                } else {
                    ops += std::min(stat[i], stat[disj]) / 2.0;
                }
            }
        }

        return ops;
    }
};

} // namespace leet

class MaxNumberOfKsumPairs : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(MaxNumberOfKsumPairs, Example1) {
    std::vector<int> nums{1,2,3,4};
    int k = 5;
    ASSERT_EQ(s.maxOperations(nums, k), 2);
}

TEST_F(MaxNumberOfKsumPairs, Example2) {
    std::vector<int> nums{3,1,3,4,3};
    int k = 6;
    ASSERT_EQ(s.maxOperations(nums, k), 1);
}
