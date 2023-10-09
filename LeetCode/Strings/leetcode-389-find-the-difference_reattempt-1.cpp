// LeetCode-389: https://leetcode.com/problems/find-the-difference/
// this solution is lamest (and yet outperforms first one); at least first attempt had a smart solution

#include <string>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        for (int i = 0; i < s.size(); i++) {
            if (s.at(i) != t.at(i)) {
                return t.at(i);
            }
        }

        return t.at(t.size() - 1);
    }
};
