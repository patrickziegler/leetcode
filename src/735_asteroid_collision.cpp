#include <deque>
#include <vector>

#include "gtest/gtest.h"

/*
We are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod in the array represent their relative position in space.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

Example 1:

Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

Example 2:

Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.

Example 3:

Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

Constraints:

    2 <= asteroids.length <= 104
    -1000 <= asteroids[i] <= 1000
    asteroids[i] != 0
*/

namespace leet {

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        std::deque<int> survivors;
        for (const auto& a : asteroids) {
            if (a >= 0 || survivors.empty() || survivors.back() < 0) { // no conflict
                survivors.push_back(a);
            } else if (survivors.back() == std::abs(a)) { // conflict, but both of same size
                survivors.pop_back();
            } else {
                while (true) {
                    if (survivors.empty()) {
                        survivors.push_back(a);
                        break;
                    } else if (survivors.back() > std::abs(a)) {
                        break; // asteroid destroyed
                    } else if (survivors.back() == std::abs(a)) {
                        survivors.pop_back();
                        break; // asteroid destroyed
                    } else if (survivors.back() >= 0) {
                        survivors.pop_back(); // asteroid wins
                    } else {
                        survivors.push_back(a);
                        break;
                    }
                }
            }
        }
        std::vector<int> result;
        for (const auto& s : survivors) {
            result.push_back(s);
        }
        return result;
    }
};

} // namespace leet

class AsteroidCollision : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(AsteroidCollision, Example1) {
    std::vector<int> asteroids = {5, 10, -5};
    std::vector<int> result = {5, 10};
    ASSERT_EQ(s.asteroidCollision(asteroids), result);
}

TEST_F(AsteroidCollision, Example2) {
    std::vector<int> asteroids = {8, -8};
    std::vector<int> result = {};
    ASSERT_EQ(s.asteroidCollision(asteroids), result);
}

TEST_F(AsteroidCollision, Example3) {
    std::vector<int> asteroids = {10, 2, -5};
    std::vector<int> result = {10};
    ASSERT_EQ(s.asteroidCollision(asteroids), result);
}

TEST_F(AsteroidCollision, Case187) {
    std::vector<int> asteroids = {-2, -2, 1, -1};
    std::vector<int> result = {-2, -2};
    ASSERT_EQ(s.asteroidCollision(asteroids), result);
}

TEST_F(AsteroidCollision, Case259) {
    std::vector<int> asteroids = {-2, 2, 1, -2};
    std::vector<int> result = {-2};
    ASSERT_EQ(s.asteroidCollision(asteroids), result);
}
