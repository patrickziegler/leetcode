class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        const size_t szWord1 = word1.length();
        const size_t szWord2 = word2.length();
        const size_t szMerged = szWord1 > szWord2 ? szWord1 : szWord2;
        stringstream ss;
        for (size_t i = 0; i < szMerged; ++i) {
            if (i < szWord1) {
                ss << word1[i];
            }
            if (i < szWord2) {
                ss << word2[i];
            }
        }
        return ss.str();
    }
};
