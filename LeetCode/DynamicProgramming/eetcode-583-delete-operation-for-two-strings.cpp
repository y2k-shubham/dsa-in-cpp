// LeetCode-583: https://leetcode.com/problems/delete-operation-for-two-strings/submissions/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3734/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void showVec(vector<int>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    int findLcsLen(string& str1, string& str2) {
        int len1 = str1.size();
        int len2 = str2.size();

        vector<int> lcsTab1(len2 + 1, 0);
        vector<int> lcsTab2(len2 + 1, 0);

        vector<int> lcsTabPrev = lcsTab1;
        vector<int> lcsTabCrr = lcsTab2;
        for (int i = 1; i <= len1; i++) {
            // printf("\n------i=%d-begin------\n", i);
            // showVec(lcsTabPrev, "lcsTabPrev");
            // printf("\n");

            char ch1 = str1.at(i - 1);

            for (int j = 1; j <= len2; j++) {
                char ch2 = str2.at(j - 1);
                if (ch1 == ch2) {
                    lcsTabCrr[j] = lcsTabPrev[j - 1] + 1;
                } else {
                    lcsTabCrr[j] = max(lcsTabCrr[j - 1], lcsTabPrev[j]);
                }
            }

            vector<int> lcsTabTmp = lcsTabPrev;
            lcsTabPrev = lcsTabCrr;
            lcsTabCrr = lcsTabTmp;

            // printf("\n");
            // showVec(lcsTabPrev, "lcsTabPrev");
            // printf("\n------i=%d-end------\n", i);
        }

        return lcsTabPrev[len2];
    }

   public:
    int minDistance(string word1, string word2) {
        int lcsLen = findLcsLen(word1, word2);
        // printf("\nlcsLen = %d\n", lcsLen);

        int len1 = word1.size();
        int len2 = word2.size();

        return (len1 - lcsLen) + (len2 - lcsLen);
    }
};
