/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23

Constraints:

    1 <= piles.length <= 10**4
    piles.length <= h <= 10**9
    1 <= piles[i] <= 10**9
*/

#include <cmath>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    static int letKokoEat(const std::vector<int>& piles, int h, int k) {
        if (k <= 0) {
            return -1; // aka -inf
        }
        int duration = 0;
        for (const auto& pile : piles) {
            duration += static_cast<int>(std::ceil(static_cast<double>(pile) / static_cast<double>(k)));
        }
        return h - duration;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        // calculate borders of solution space k
        long long pileTotal = 0;
        int pileMax = piles[0]; // right border
        for (const auto& pile : piles) {
            pileTotal += pile;
            pileMax = std::max(pileMax, pile);
        }
        int k = pileTotal / h - 1; // left border
        // use binary search to find separation between 'good' and 'bad' in solutions space k
        int left = k, right = pileMax, middle;
        while (right - left > 1) {
            middle = left + (right - left) / 2;
            if (letKokoEat(piles, h, middle) < 0) {
                left = middle;
            } else {
                right = middle;
            }
        }
        return right;
    }
};

} // namespace leet

class KokoEatingBananas : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(KokoEatingBananas, Example1) {
    std::vector<int> piles = {3,6,7,11};
    ASSERT_EQ(s.minEatingSpeed(piles, 8), 4);
}

TEST_F(KokoEatingBananas, Example2) {
    std::vector<int> piles = {30,11,23,4,20};
    ASSERT_EQ(s.minEatingSpeed(piles, 5), 30);
}

TEST_F(KokoEatingBananas, Example3) {
    std::vector<int> piles = {30,11,23,4,20};
    ASSERT_EQ(s.minEatingSpeed(piles, 6), 23);
}

TEST_F(KokoEatingBananas, Case117) {
    std::vector<int> piles = {1000000000,1000000000};
    ASSERT_EQ(s.minEatingSpeed(piles, 3), 1000000000);
}

TEST_F(KokoEatingBananas, Case124) {
    std::vector<int> piles = {312884470};
    ASSERT_EQ(s.minEatingSpeed(piles, 968709470), 1);
}

TEST_F(KokoEatingBananas, Case125) {
    std::vector<int> piles = {1000000000};
    ASSERT_EQ(s.minEatingSpeed(piles, 2), 500000000);
}
