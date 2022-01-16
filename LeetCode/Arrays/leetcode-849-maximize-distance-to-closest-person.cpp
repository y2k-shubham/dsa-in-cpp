// LeetCode-849: https://leetcode.com/problems/maximize-distance-to-closest-person/

#include <climits>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildClosestOccIdxLeftVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> closestOccIdxLeftVec(len, -1);
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                closestOccIdxLeftVec[i] = i;
            } else {
                closestOccIdxLeftVec[i] = (i >= 1) ? closestOccIdxLeftVec[i - 1] : -1;
            }
        }

        return closestOccIdxLeftVec;
    }

    vector<int> buildClosestOccIdxRightVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> closestOccIdxRightVec(len, len);
        for (int i = len - 1; i >= 0; i--) {
            if (vec[i] == 1) {
                closestOccIdxRightVec[i] = i;
            } else {
                closestOccIdxRightVec[i] = (i < (len - 1)) ? closestOccIdxRightVec[i + 1] : len;
            }
        }

        return closestOccIdxRightVec;
    }

    int findMaxDist(
        vector<int>& vec,
        vector<int>& closestOccIdxLeftVec,
        vector<int>& closestOccIdxRightVec) {
        int len = vec.size();

        int overallMaxDist = 0;
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                // seat is already occupied
                continue;
            }

            int crrLeftDist = (i == 0) ? INT_MAX : (i - closestOccIdxLeftVec[i]);
            int crrRightDist = (i == (len - 1)) ? INT_MAX : (closestOccIdxRightVec[i] - i);
            int crrMinDist = min(crrLeftDist, crrRightDist);

            overallMaxDist = max(overallMaxDist, crrMinDist);
        }

        return overallMaxDist;
    }

   public:
    int maxDistToClosest(vector<int>& seats) {
        vector<int> closestOccIdxLeftVec = buildClosestOccIdxLeftVec(seats);
        vector<int> closestOccIdxRightVec = buildClosestOccIdxRightVec(seats);

        return findMaxDist(
            seats,
            closestOccIdxLeftVec,
            closestOccIdxRightVec);
    }
};
