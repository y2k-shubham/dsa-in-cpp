// LeetCode-2645: https://leetcode.com/problems/minimum-additions-to-make-valid-string/

#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <string, int> strNumInsertionsMap;

    void init() {
        strNumInsertionsMap = {
            // starting with a
            {"a", 2},
            {"ab", 1},
            {"ac", 1},
            {"abc", 0},
            // starting with b
            {"b", 2},
            {"bc", 1},
            // starting with c
            {"c", 2}
        };
    }

    pair <string, int> swallowCharsTillLongestMapKeyFound(string& str, int startIdx) {
        string longestPrefix = "";

        string crrPrefix = "";
        int i;
        for (i = startIdx; i < str.size(); i++) {
            char ch = str.at(i);

            crrPrefix += ch;
            if (strNumInsertionsMap.find(crrPrefix) == strNumInsertionsMap.end()) {
                break;
            }

            if (crrPrefix.size() > longestPrefix.size()) {
                longestPrefix = crrPrefix;
            }
        }

        return {longestPrefix, i};
    }

public:
    int addMinimum(string word) {
        init();

        int numInsertions = 0;
        int i = 0;
        while (i < word.size()) {
            pair <string, int> prefixNextIdx = swallowCharsTillLongestMapKeyFound(word, i);
            numInsertions += strNumInsertionsMap[prefixNextIdx.first];
            i = prefixNextIdx.second;
        }

        return numInsertions;
    }
};
