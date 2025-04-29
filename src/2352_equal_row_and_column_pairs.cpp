#include <map>
#include <vector>

#include "gtest/gtest.h"

/*
Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.

A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).

Example 1:

Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
Output: 1
Explanation: There is 1 equal row and column pair:
- (Row 2, Column 1): [2,7,7]

Example 2:

Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
Output: 3
Explanation: There are 3 equal row and column pairs:
- (Row 0, Column 0): [3,1,2,2]
- (Row 2, Column 2): [2,4,2,2]
- (Row 3, Column 2): [2,4,2,2]

Constraints:

    n == grid.length == grid[i].length
    1 <= n <= 200
    1 <= grid[i][j] <= 105
*/

namespace leet {

using namespace std;

class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        std::map<std::vector<int>, size_t> target;
        for (const auto& row : grid) {
            ++target[row];
        }
        std::vector<int> column;
        size_t n = grid[0].size();
        size_t c = 0;
        for (size_t i=0; i < n; ++i) {
            for (size_t j=0; j < n; ++j) {
                column.push_back(grid[j][i]);
            }
            const auto& it = target.find(column);
            if (it != target.end()) {
                c += it->second;
            }
            column.clear();
        }
        return static_cast<int>(c);
    }
};

} // namespace leet

class EqualRowAndColumnPairs : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(EqualRowAndColumnPairs, Example1) {
    std::vector<std::vector<int>> grid = {
        {3, 2, 1},
        {1, 7, 6},
        {2, 7, 7}
    };
    ASSERT_EQ(s.equalPairs(grid), 1);
}

TEST_F(EqualRowAndColumnPairs, Example2) {
    std::vector<std::vector<int>> grid = {
        {3, 1, 2, 2},
        {1, 4, 4, 5},
        {2, 4, 2, 2},
        {2, 4, 2, 2}
    };
    ASSERT_EQ(s.equalPairs(grid), 3);
}
