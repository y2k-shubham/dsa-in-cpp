// LeetCode-1046: https://leetcode.com/problems/last-stone-weight/
// pretty dumb problem; dont bother looking

#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq(stones.begin(), stones.end());

        while (pq.size() > 1) {
            int stone1Wgt = pq.top();
            pq.pop();
            int stone2Wgt = pq.top();
            pq.pop();

            if (stone1Wgt != stone2Wgt) {
                int stonesRemWgt = abs(stone1Wgt - stone2Wgt);
                pq.push(stonesRemWgt);
            }
        }

        return pq.empty() ? 0 : pq.top();
    }
};
