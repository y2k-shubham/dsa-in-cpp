// LeetCode-997: https://leetcode.com/problems/find-the-town-judge/
// pretty dumb problem; skip

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findJudge(int N, vector<vector<int>>& trust) {
        unordered_map<int, int> trustsCount;
        unordered_map<int, int> trustedByCount;

        for (int i = 0; i < trust.size(); i++) {
            // read trust relation
            vector<int> crrTrust = trust[i];
            int truster = crrTrust[0];
            int trustee = crrTrust[1];

            // update the counter of truster (the person who trusts a person)
            if (trustsCount.find(truster) == trustsCount.end()) {
                trustsCount[truster] = 1;
            } else {
                trustsCount[truster] += 1;
            }

            // update the counter of trustee (the person who is trusted by another person)
            if (trustedByCount.find(trustee) == trustedByCount.end()) {
                trustedByCount[trustee] = 1;
            } else {
                trustedByCount[trustee] += 1;
            }
        }

        for (int i = 1; i <= N; i++) {
            bool trustsNobody = trustsCount.find(i) == trustsCount.end();
            bool trustedByEverybody = trustedByCount[i] == (N - 1);
            if (trustsNobody && trustedByEverybody) {
                return i;
            }
        }

        return -1;
    }
};
