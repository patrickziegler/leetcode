// Example program
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

using namespace std;

   unordered_set<string> candidates(string s) {
        unordered_set<string> candidates;
        for (size_t n = s.length() - 1; n > 0; --n) {
            if (s.length() % n) {
                continue;
            }
            std::cout << "try: " << n << std::endl;
            for (size_t i = 0; i < s.length() - n + 1; ++i) {
                string sub = s.substr(i, n);
                stringstream c;
                std::cout << sub << std::endl;
                for (size_t m = 0; m < s.length() / n; ++m) {
                    c << sub;
                }
                if (c.str() == s) {
                    candidates.insert(sub);
                    std::cout << "found: " << sub << std::endl;
                }
            }
        }
        return candidates;
    }

int main()
{
    std::string test = "ABCABCABC";
    candidates(test);
}





class Solution {
public:
    vector<string> candidates(string s) {
        vector<string> candidates;
        for (size_t n = s.length() - 1; n > 0; --n) {
            if (s.length() % n) {
                continue;
            }
            for (size_t i = 0; i < n; ++i) {
                string sub = substr(i, n);
                stringstream c;
                for (size_t m = 0; m < s.length / n; ++m) {
                    c << sub;
                }
                if (c.str() == s) {
                    candidates.push_back(s);
                }
            }
        }
    }
    string gcdOfStrings(string str1, string str2) {

    }
};
