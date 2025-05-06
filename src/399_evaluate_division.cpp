/*
You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation:
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0

Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]

Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]

Constraints:

    1 <= equations.length <= 20
    equations[i].length == 2
    1 <= Ai.length, Bi.length <= 5
    values.length == equations.length
    0.0 < values[i] <= 20.0
    1 <= queries.length <= 20
    queries[i].length == 2
    1 <= Cj.length, Dj.length <= 5
    Ai, Bi, Cj, Dj consist of lower case English letters and digits.
*/

#include <queue>
#include <unordered_set>

#include "gtest/gtest.h"

namespace leet {

using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // collect list of distinct keys
        std::unordered_map<std::string, size_t> keys;
        for (const auto& eq : equations) {
            if (keys.find(eq[0]) == keys.end()) {
                keys[eq[0]] = keys.size();
            }
            if (keys.find(eq[1]) == keys.end()) {
                keys[eq[1]] = keys.size();
            }
        }
        // create cost matrix
        std::vector<std::vector<double>> mat(keys.size(), std::vector<double>(keys.size(), 0));
        size_t a, b;
        for (size_t i=0; i < equations.size(); ++i) {
            a = keys[equations[i][0]];
            b = keys[equations[i][1]];
            mat[a][b] = values[i];
            mat[b][a] = 1 / values[i];
        }
        // calculate results
        std::vector<double> results;
        for (const auto& query : queries) {
            if (keys.find(query[0]) == keys.end() || keys.find(query[1]) == keys.end()) {
                results.push_back(-1);
                continue;
            }
            a = keys[query[0]]; // start node
            b = keys[query[1]]; // end node
            // bfs
            std::queue<std::pair<size_t, double>> q;
            std::unordered_set<size_t> visited; // prevents endless loops
            q.push({a, 1});
            visited.insert(a);
            double result = -1;
            while (!q.empty()) {
                auto [i, prod] = q.front();
                q.pop();
                if (i == b) {
                    result = prod;
                    break;
                }
                for (size_t j=0; j < keys.size(); ++j) {
                    if (mat[i][j] == 0 || visited.find(j) != visited.end()) {
                        continue;
                    }
                    q.push({j, prod * mat[i][j]});
                }
                visited.insert(i);
            }
            results.push_back(result);
        }
        return results;
    }
};

} // namespace leet

class EvaluateDivision : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(EvaluateDivision, Example1) {
    std::vector<std::vector<std::string>> equations = {{"a", "b"}, {"b", "c"}};
    std::vector<double> values = {2, 3};
    std::vector<std::vector<std::string>> queries = {
        {"a", "c"},
        {"b", "a"},
        {"a", "e"},
        {"a", "a"},
        {"x", "x"}
    };
    std::vector<double> result = {6,0.5,-1,1,-1};
    ASSERT_EQ(s.calcEquation(equations, values, queries), result);
}

TEST_F(EvaluateDivision, Case26) {
    std::vector<std::vector<std::string>> equations = {{"a", "b"}, {"c", "d"}};
    std::vector<double> values = {1, 1};
    std::vector<std::vector<std::string>> queries = {
        {"a", "c"}, // interesting, no valid path exists even though keys are present in equations!
        {"b", "d"}, // same as above
        {"b", "a"},
        {"d", "c"}
    };
    std::vector<double> result = {-1, -1, 1, 1};
    ASSERT_EQ(s.calcEquation(equations, values, queries), result);
}
