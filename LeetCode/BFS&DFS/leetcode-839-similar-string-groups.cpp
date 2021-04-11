// LeetCode-839: https://leetcode.com/problems/similar-string-groups/
// InterviewDose soln: https://www.youtube.com/watch?v=WuBTG71yOek
/**
 * soln is simple DFS
 *  - but actually it works only because of constraints
 *  - expectedly, the performance isn't very impressive
 *    (LC submission speed 37%tile, memory 19%tile)
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<bool> createVisitedVec(int numStrs) {
        vector<bool> vec(numStrs, false);
        return vec;
    }

    bool areSimilar(string& str1, string& str2) {
        int diffs = 0;
        for (int i = 0; i < str1.size(); i++) {
            if (str1.at(i) != str2.at(i)) {
                diffs++;
                if (diffs > 2) {
                    return false;
                }
            }
        }

        return true;
    }

    void dfs(vector<bool>& visitedVec, vector<string>& strVec, string& str, int strIdx) {
        if (visitedVec[strIdx]) {
            return;
        }

        visitedVec[strIdx] = true;
        for (int i = 0; i < strVec.size(); i++) {
            if (i != strIdx) {
                string strCand = strVec[i];
                if (areSimilar(str, strCand)) {
                    dfs(visitedVec, strVec, strCand, i);
                }
            }
        }
    }

   public:
    int numSimilarGroups(vector<string>& strs) {
        int numStrs = strs.size();
        if (numStrs == 0) {
            return 0;
        }
        if (numStrs == 1) {
            return 1;
        }

        int strsLen = strs[0].size();
        vector<bool> visitedVec = createVisitedVec(numStrs);

        int numGroups = 0;
        for (int i = 0; i < strs.size(); i++) {
            string strCand = strs[i];
            if (!visitedVec[i]) {
                dfs(visitedVec, strs, strCand, i);
                ++numGroups;
            }
        }

        return numGroups;
    }
};
