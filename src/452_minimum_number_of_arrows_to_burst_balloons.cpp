/*
There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array points, return the minimum number of arrows that must be shot to burst all balloons.

Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

Example 2:

Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.

Example 3:

Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].

Constraints:

    1 <= points.length <= 10**5
    points[i].length == 2
    -2**31 <= xstart < xend <= 2**31 - 1
*/

#include <algorithm>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        std::sort(points.begin(), points.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });
        int n = 1, cur = points[0][1];
        for (const auto& pt : points) {
            if (pt[0] <= cur) {
                cur = std::min(cur, pt[1]);
            } else {
                ++n;
                cur = pt[1];
            }
        }
        return n;
    }
};

} // namespace leet

class MinimumNumberOfArrowsToBurstBallon : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(MinimumNumberOfArrowsToBurstBallon, Example1) {
    std::vector<std::vector<int>> points = {{10,16},{2,8},{1,6},{7,12}};
    ASSERT_EQ(s.findMinArrowShots(points), 2);
}

TEST_F(MinimumNumberOfArrowsToBurstBallon, Example2) {
    std::vector<std::vector<int>> points = {{1,2},{3,4},{5,6},{7,8}};
    ASSERT_EQ(s.findMinArrowShots(points), 4);
}

TEST_F(MinimumNumberOfArrowsToBurstBallon, Example3) {
    std::vector<std::vector<int>> points = {{1,2},{2,3},{3,4},{4,5}};
    ASSERT_EQ(s.findMinArrowShots(points), 2);
}
