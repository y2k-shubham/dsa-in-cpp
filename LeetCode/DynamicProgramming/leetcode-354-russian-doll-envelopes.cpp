// LeetCode-354: https://leetcode.com/problems/russian-doll-envelopes/

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
   // barely accepted; LC-submission: speed 5 %tile, memory 19 %tile
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());

        int len = envelopes.size();
        vector<int> memoVec(len, 1);

        int maxEnvAns = 1;
        for (int i = 1; i < len; i++) {
            vector<int> crrEnvelope = envelopes[i];
            int crrEnvAns = 1;

            for (int j = 0; j < i; j++) {
                if (
                    (envelopes[j][0] < crrEnvelope[0]) &&
                    (envelopes[j][1] < crrEnvelope[1]) &&
                    ((memoVec[j] + 1) > crrEnvAns)) {
                    crrEnvAns = memoVec[j] + 1;
                }
            }

            memoVec[i] = crrEnvAns;
            maxEnvAns = max(maxEnvAns, crrEnvAns);
        }

        return maxEnvAns;
    }
};
