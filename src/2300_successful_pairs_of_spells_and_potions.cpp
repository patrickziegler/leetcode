/*
You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.

You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.

Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.

Example 1:

Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Example 2:

Input: spells = [3,1,2], potions = [8,5,8], success = 16
Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
Thus, [2,0,2] is returned.

Constraints:

    n == spells.length
    m == potions.length
    1 <= n, m <= 10**5
    1 <= spells[i], potions[i] <= 10**5
    1 <= success <= 1010
*/

#include <algorithm>
#include <cmath>
#include <thread>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
    static size_t countGood(const std::vector<int>& v, long long lim) {
        size_t a = 0, b = v.size() - 1, g;
        if (v.back() < lim) {
            return 0;
        } else if (v.front() > lim) {
            return v.size();
        }
        while (true) {
            if (b - a == 1) {
                if (v[a] == lim) {
                    b = a;
                }
                break;
            }
            g = a + (b - a) / 2;
            if (v[g] > lim) {
                b = g;
            } else if (v[g] < lim) {
                a = g;
            } else if (g > 0 && v[g-1] == v[g]) { // because of duplicates
                b = g;
            } else {
                b = g;
                break;
            }
        }
        return v.size() - b;
    }
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        std::vector<int> res;
        std::sort(potions.begin(), potions.end());
        long long lim;
        for (const auto& s : spells) {
            lim = static_cast<long long>(std::ceil(static_cast<double>(success) / static_cast<double>(s)));
            res.push_back(countGood(potions, lim));
        }
        return res;
    }
};

} // namespace leet

class SuccessfulParisOfSpellsAndPotions : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(SuccessfulParisOfSpellsAndPotions, Example1) {
    std::vector<int> spells{5,1,3};
    std::vector<int> potions{1,2,3,4,5};
    std::vector<int> result{4,0,3};
    ASSERT_EQ(s.successfulPairs(spells, potions, 7), result);
}

TEST_F(SuccessfulParisOfSpellsAndPotions, Example2) {
    std::vector<int> spells{3,1,2};
    std::vector<int> potions{8,5,8};
    std::vector<int> result{2,0,2};
    ASSERT_EQ(s.successfulPairs(spells, potions, 16), result);
}

TEST_F(SuccessfulParisOfSpellsAndPotions, Case31) {
    std::vector<int> spells{15,39,38,35,33,25,31,12,40,27,29,16,22,24,7,36,29,34,24,9,11,35,21,3,33,10,9,27,35,17,14,3,35,35,39,23,35,14,31,7};
    std::vector<int> potions{25,19,30,37,14,30,38,22,38,38,26,33,34,23,40,28,15,29,36,39,39,37,32,38,8,17,39,20,4,39,39,7,30,35,29,23};
    std::vector<int> result{28,33,33,33,33,33,33,23,34,33,33,29,32,33,0,33,33,33,33,13,22,33,31,0,33,17,13,33,33,30,27,0,33,33,33,33,33,27,33,0};
    ASSERT_EQ(s.successfulPairs(spells, potions, 317), result);
}
