// LeetCode-881: https://leetcode.com/problems/boats-to-save-people/

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int len = people.size();

        int numBoats = 0;
        int iLo = 0;
        int iHi = len - 1;
        while (iLo <= iHi) {
            int crrTotalWgt = people[iLo] + people[iHi];

            if (iLo == iHi) {
                iLo++;
                iHi--;
                numBoats++;
            } else if (crrTotalWgt <= limit) {
                iLo++;
                iHi--;
                numBoats++;
            } else {
                iHi--;
                numBoats++;
            }
        }

        return numBoats;
    }
};
