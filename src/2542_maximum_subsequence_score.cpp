/*
You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k. You must choose a subsequence of indices from nums1 of length k.

For chosen indices i0, i1, ..., ik - 1, your score is defined as:

    The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
    It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).

Return the maximum possible score.

A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by deleting some or no elements.

Example 1:

Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
Output: 12
Explanation:
The four possible subsequence scores are:
- We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
- We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6.
- We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12.
- We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
Therefore, we return the max score, which is 12.

Example 2:

Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
Output: 30
Explanation:
Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the maximum possible score.

Constraints:

    n == nums1.length == nums2.length
    1 <= n <= 10**5
    0 <= nums1[i], nums2[j] <= 10**5
    1 <= k <= n
*/

#include <algorithm>
#include <queue>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        const size_t n = nums1.size();
        // sort nums2 in descending order, so that it is guaranteed that for a given nums2[i], which implicitly will be i0,
        // all other indices i1, ..., ik - 1 will be found to the left and nums2[idx[i]] is min(nums2[0], .., nums2[i])
        std::vector<size_t> idx(n);
        for (size_t i=0; i < n; ++i) {
            idx[i] = i;
        }
        std::sort(idx.begin(), idx.end(), [&nums2](const size_t& a, const size_t& b) -> bool {
            return nums2[a] > nums2[b]; // sort by descending key
        });
        // min heap to keep track of smallest element contained in sum so that we can remove it on each iteration
        std::priority_queue<int, std::vector<int>, std::greater<int>> q;
        long long scoreMax = 0, s = 0;
        // fill the heap with k-1 elements
        for (size_t i=0; i < k-1; ++i) {
            s += nums1[idx[i]];
            q.push(nums1[idx[i]]);
        }
        // iterate over all possible indices i0 = nums2[i]
        for (size_t i=k-1; i < n; ++i) {
            s += nums1[idx[i]];
            q.push(nums1[idx[i]]);
            scoreMax = std::max(scoreMax, s * nums2[idx[i]]);
            s -= q.top();
            q.pop();
        }
        return scoreMax;
    }
};

} // namespace leet

class MaximumSubsequenceScore : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(MaximumSubsequenceScore, Example1) {
    std::vector<int> nums1{1,3,3,2};
    std::vector<int> nums2{2,1,3,4};
    ASSERT_EQ(s.maxScore(nums1, nums2, 3), 12);
}

TEST_F(MaximumSubsequenceScore, Example2) {
    std::vector<int> nums1{4,2,3,1,1};
    std::vector<int> nums2{7,5,10,9,6};
    ASSERT_EQ(s.maxScore(nums1, nums2, 1), 30);
}
