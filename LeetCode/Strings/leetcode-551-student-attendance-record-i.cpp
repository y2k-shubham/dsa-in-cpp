// LeetCode-551: https://leetcode.com/problems/student-attendance-record-i/

#include <string>

using namespace std;

class Solution {
public:
    bool checkRecord(string s) {
        int crrConsecLates = 0;
        int totalAbsents = 0;

        for (int i = 0; i < s.size(); i++) {
            char ch = s.at(i);

            switch (ch) {
                case 'A':
                    crrConsecLates = 0;
                    totalAbsents++;
                    break;

                case 'L':
                    crrConsecLates++;
                    break;

                default:
                    crrConsecLates = 0;
                    break;
            }

            if (totalAbsents >= 2) {
                return false;
            }
            if (crrConsecLates >= 3) {
                return false;
            }
        }

        return true;
    }
};
