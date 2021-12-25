// LeetCode-2109: https://leetcode.com/problems/adding-spaces-to-a-string/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
   public:
    string addSpaces(string s, vector<int>& spaces) {
        if (spaces.empty()) {
            return s;
        }

        ostringstream oss;
        int i = 0, j = 0;
        for (; i < s.size(); i++) {
            if ((j < spaces.size()) && (i == spaces[j])) {
                oss << ' ';
                j++;
            }
            oss << s.at(i);
        }

        return oss.str();
    }
};
