// LeetCode-2078: https://leetcode.com/problems/two-furthest-houses-with-different-colors/
// quite easy soln; but not super-intuitive to strike

#include <cmath>
#include <vector>

using namespace std;

class Solution {
   private:
    int findSolnLoInc(vector<int>& colors, int idxLo, int idxHi) {
        while ((idxLo < idxHi) && (colors[idxLo] == colors[idxHi])) {
            idxLo++;
        }

        if (idxLo < idxHi) {
            return idxHi - idxLo;
        } else {
            return -1;
        }
    }

    int findSolnHiDec(vector<int>& colors, int idxLo, int idxHi) {
        while ((idxLo < idxHi) && (colors[idxLo] == colors[idxHi])) {
            idxHi--;
        }

        if (idxLo < idxHi) {
            return idxHi - idxLo;
        } else {
            return -1;
        }
    }

   public:
    int maxDistance(vector<int>& colors) {
        int len = colors.size();
        if (len < 2) {
            return -1;
        }

        int idxLo = 0;
        int idxHi = len - 1;
        return max(
            findSolnLoInc(colors, idxLo, idxHi),
            findSolnHiDec(colors, idxLo, idxHi));
    }
};
