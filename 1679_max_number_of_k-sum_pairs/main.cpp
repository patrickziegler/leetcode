#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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

int main(int argc, char** argv) {
    Solution s;
    std::vector<int> nums{3,1,3,4,3};
    int k = 6;
    std::cout << s.maxOperations(nums, k) << std::endl;
    return 0;
}
