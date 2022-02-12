// LeetCode-567: https://leetcode.com/problems/permutation-in-string/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define NUM_ALPHAS 26

class Solution {
   private:
    vector<vector<int> > buildFreqMat(string str) {
        int len = str.size();

        vector<vector<int> > charsFreqMat(NUM_ALPHAS);
        for (int i = 0; i < NUM_ALPHAS; i++) {
            char crrChar = (char)('a' + i);
            vector<int> freqVec(len);

            if (str.at(0) == crrChar) {
                freqVec[0] = 1;
            }
            for (int i = 1; i < len; i++) {
                if (str.at(i) == crrChar) {
                    freqVec[i] = freqVec[i - 1] + 1;
                } else {
                    freqVec[i] = freqVec[i - 1];
                }
            }

            charsFreqMat[i] = freqVec;
        }

        return charsFreqMat;
    }

    vector<int> buildFreqVec(string str) {
        vector<int> freqVec(NUM_ALPHAS);

        for (int i = 0; i < str.size(); i++) {
            freqVec[str.at(i) - 'a']++;
        }

        return freqVec;
    }

    bool hasPerm(
        int iLo,
        int iHi,
        vector<vector<int> >& freqMat,
        vector<int>& freqVec) {
        for (int i = 0; i < NUM_ALPHAS; i++) {
            int freqInMat = freqMat[i][iHi] - ((iLo > 0) ? freqMat[i][iLo - 1] : 0);
            int freqInVec = freqVec[i];
            if (freqInMat != freqInVec) {
                return false;
            }
        }

        return true;
    }

   public:
    bool checkInclusion(string strSmall, string strBig) {
        int lenBig = strBig.size();
        int lenSmall = strSmall.size();
        if (lenBig < lenSmall) {
            return false;
        }

        vector<vector<int> > freqMat = buildFreqMat(strBig);
        vector<int> freqVec = buildFreqVec(strSmall);

        for (int i = 0; (i + lenSmall - 1) < lenBig; i++) {
            if (hasPerm(i, i + lenSmall - 1, freqMat, freqVec)) {
                return true;
            }
        }

        return false;
    }
};
