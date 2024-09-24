// LeetCode-2515: https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector<int> findTargetWordIndices(vector<string>& words, string target) {
        vector<int> indices;

        for (int i = 0; i < words.size(); i++) {
            if (words[i] == target) {
                indices.push_back(i);
            }
        }

        return indices;
    }

    inline int calculateMinDistanceToTargetIdx(int len, int startIndex, int targetIdx) {
        return min(abs(startIndex - targetIdx), len - abs(startIndex - targetIdx));
    }

public:
    int closetTarget(vector<string>& words, string target, int startIndex) {
        int len = words.size();
        if (len == 0) {
            return -1;
        }

        vector<int> targetIndices = findTargetWordIndices(words, target);
        if (targetIndices.empty()) {
            return -1;
        }

        int minDist = INT_MAX;
        for (int targetIdx: targetIndices) {
            minDist = min(
                    minDist,
                    calculateMinDistanceToTargetIdx(len, startIndex, targetIdx)
            );
        }

        return minDist;
    }
};
