/*
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

Example 1:

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:

Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

Constraints:

    1 <= intervals.length <= 10**5
    intervals[i].length == 2
    -5 * 104 <= starti < endi <= 5 * 10**4
*/

#include <algorithm>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });
        int n = 0, cur = intervals[0][0];
        for (const auto& interval : intervals) {
            if (interval[0] < cur) {
                ++n;
                // on overlap, "keep" the shorter interval
                cur = std::min(cur, interval[1]);
            } else {
                cur = interval[1];
            }
        }
        return n;
    }
};

} // namespace leet

class NonOverlappingIntervals : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(NonOverlappingIntervals, Example1) {
    std::vector<std::vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
    ASSERT_EQ(s.eraseOverlapIntervals(intervals), 1);
}

TEST_F(NonOverlappingIntervals, Example2) {
    std::vector<std::vector<int>> intervals = {{1,2},{1,2},{1,2}};
    ASSERT_EQ(s.eraseOverlapIntervals(intervals), 2);
}

TEST_F(NonOverlappingIntervals, Example3) {
    std::vector<std::vector<int>> intervals = {{1,2},{2,3}};
    ASSERT_EQ(s.eraseOverlapIntervals(intervals), 0);
}

TEST_F(NonOverlappingIntervals, Case13) {
    std::vector<std::vector<int>> intervals = {{1,2},{2,3},{3,4},{-100,-2},{5,7}};
    ASSERT_EQ(s.eraseOverlapIntervals(intervals), 0);
}

TEST_F(NonOverlappingIntervals, Case20) {
    std::vector<std::vector<int>> intervals = {{-52,31},{-73,-26},{82,97},{-65,-11},{-62,-49},{95,99},{58,95},{-31,49},{66,98},{-63,2},{30,47},{-40,-26}};
    ASSERT_EQ(s.eraseOverlapIntervals(intervals), 7);
}
