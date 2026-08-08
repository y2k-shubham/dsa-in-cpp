// LeetCode-277: https://leetcode.com/problems/find-the-celebrity/
// Premium
// Companies: [Hubspot][LinkedIn][Amazon][Toast][Microsoft][Meta][Google][Nvidia][Apple][TikTok][Uber]

#include <unordered_map>
#include <vector>

using namespace std;

/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
private:
    vector<int> knowsFreqMapVec;
    vector<int> isKnownByFreqMapVec;
    bool knows(int a, int b);

    void initMapVecs(int n) {
        knowsFreqMapVec.resize(n, 0);
        isKnownByFreqMapVec.resize(n, 0);
    }

    void populateMapVecs(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool iKnowsJ = knows(i, j);
                if (iKnowsJ) {
                    knowsFreqMapVec[i]++;
                    isKnownByFreqMapVec[j]++;
                }

                bool jKnowsJ = knows(j, i);
                if (jKnowsJ) {
                    knowsFreqMapVec[j]++;
                    isKnownByFreqMapVec[i]++;
                }
            }
        }
    }

    int findCelebrityHelper(int n) {
        for (int i = 0; i < n; i++) {
            bool knowsNobody = knowsFreqMapVec[i] == 0;
            bool isKnownByEverybody = isKnownByFreqMapVec[i] == (n - 1);

            if (knowsNobody && isKnownByEverybody) {
                return i;
            }
        }

        return -1;
    }

public:
    int findCelebrity(int n) {
        initMapVecs(n);
        populateMapVecs(n);
        return findCelebrityHelper(n);
    }
};
