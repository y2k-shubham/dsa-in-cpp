// LeetCode-2079: https://leetcode.com/problems/watering-plants/
// easy problem; no DS / Algo / tricks involved, just pure simulation (do-as-directed)

#include <vector>

using namespace std;

class Solution {
   public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int len = plants.size();

        int steps = len;
        int quantity = capacity;
        for (int i = 0; i < len; i++) {
            int requirement = plants[i];

            if (quantity >= requirement) {
                quantity -= requirement;
            } else {
                quantity = capacity;
                quantity -= requirement;

                // note that we are NOT incrementing this by 2 * (i + 1) because
                // we walk back to river from i - 1 itself (that is before even reaching i)
                steps += 2 * i;
            }
        }

        return steps;
    }
};
