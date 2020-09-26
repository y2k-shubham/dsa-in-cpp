// LeetCode-712: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
// it is a simple modification of leetcode-72: minimum edit distance

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int getStringAsciiSum(string str) {
    int sum = 0;
    for (int i = 0; i < str.size(); i++) {
        sum += (int)str.at(i);
    }
    return sum;
}

/**
 * @brief this function has been taken from leetcode-72 minimum edit distance
 * and modified as per this question
 * 
 * @param str1 
 * @param str2 
 * @return int minimum ascii sum of deleted chars to make both strings equal
 */
int minDeleteSumSpaceOpt(string str1, string str2) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (len1 == 0 && len2 == 0) {
        // if both strings are zero, min ascii sum of deleted chars is 0
        // (since nothing has to be deleted)
        return 0;
    } else if (len1 == 0) {
        // if string1 is empty, then ascii sum of deleted chars is equal to ascii
        // sum of all chars of string2 (all chars of string2 will have to be deleted)
        return getStringAsciiSum(str2);
    } else if (len2 == 0) {
        // if string2 is empty, then ascii sum of deleted chars is equal to ascii
        // sum of all chars of string1 (all chars of string1 will have to be deleted)
        return getStringAsciiSum(str1);
    }

    vector<int> prevVec(len2 + 1);
    for (int j = 0; j <= len2; j++) {
        if (j == 0) {
            prevVec[j] = 0;
        } else {
            // instead of storing j here, we store the ascii sum of chars of string2
            // (which is placed along horizontal dimension of matrix) seen so far
            prevVec[j] = prevVec[j - 1] + ((int)str2.at(j - 1));
        }
    }

    vector<int> crrVec(len2 + 1, INT_MAX);
    for (int i = 1; i <= len1; i++) {
        char ch1 = str1.at(i - 1);

        fill(crrVec.begin(), crrVec.end(), INT_MAX);
        // here again instead of storing i here, we store the ascii sum of chars of string1
        // (which is placed along vertical dimension of matrix) seen so far
        crrVec[0] = prevVec[0] + ((int)ch1);

        for (int j = 1; j <= len2; j++) {
            char ch2 = str2.at(j - 1);

            if (ch1 == ch2) {
                // if chars are same, then take diagonally previous sum
                crrVec[j] = prevVec[j - 1];
            } else {
                // otherwise take the minimum sum required to delete last char from either string
                crrVec[j] = min((prevVec[j] + ((int)ch1)), (crrVec[j - 1] + ((int)ch2)));
            }
        }

        prevVec = crrVec;
    }

    return crrVec[len2];
}

int minimumDeleteSum(string s1, string s2) {
    return minDeleteSumSpaceOpt(s1, s2);
}
