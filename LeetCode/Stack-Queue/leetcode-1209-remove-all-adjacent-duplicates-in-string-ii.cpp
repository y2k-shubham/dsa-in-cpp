// LeetCode-1209: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/595/week-3-april-15th-april-21st/3710/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
   private:
    void popK(stack<pair<char, int> >& stk, int k) {
        for (int i = 1; i <= k; i++) {
            stk.pop();
        }
    }

    string convertToStr(stack<pair<char, int> >& stk) {
        ostringstream oss;
        while (!stk.empty()) {
            pair<char, int> stkTop = stk.top();
            stk.pop();

            oss << stkTop.first;
        }

        string revStr = oss.str();
        reverse(revStr.begin(), revStr.end());

        return revStr;
    }

   public:
    string removeDuplicates(string str, int k) {
        stack<pair<char, int> > stk;

        for (int i = 0; i < str.size(); i++) {
            char strCh = str.at(i);

            int freq = 1;
            if (!stk.empty()) {
                pair<char, int> stkTop = stk.top();

                char stkCh = stkTop.first;
                if (stkCh == strCh) {
                    freq += stkTop.second;
                }
            }
            stk.push({strCh, freq});

            if (freq == k) {
                popK(stk, k);
            }
        }

        if (stk.empty()) {
            return "";
        } else {
            return convertToStr(stk);
        }
    }
};
