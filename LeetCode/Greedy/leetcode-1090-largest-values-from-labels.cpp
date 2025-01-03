// LeetCode-1090: https://leetcode.com/problems/largest-values-from-labels

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector <pair <int, int>> zipVecs(vector <int>& vec1, vector <int>& vec2) {
        int len = vec1.size();
        vector <pair <int, int>> zippedVec(len);

        for (int i = 0; i < vec1.size(); i++) {
            zippedVec[i] = {vec1[i], vec2[i]};
        }

        return zippedVec;
    }

    int findMaximumSum(vector <pair <int, int>> valueAndLabels, int labelUseLimit, int numItemsToPick) {
        unordered_map <int, int> labelPickCounts;

        int sum = 0;
        int numItemsPicked = 0;
        for (int i = 0; (i < valueAndLabels.size()) && (numItemsPicked < numItemsToPick); i++) {
            int val = valueAndLabels[i].first;
            int label = valueAndLabels[i].second;

            int labelUseCount = labelPickCounts[label];
            if (labelUseCount < labelUseLimit) {
                sum += val;

                numItemsPicked++;
                labelPickCounts[label]++;
            }
        }

        return sum;
    }

public:
    int largestValsFromLabels(vector <int>& values, vector <int>& labels, int numWanted, int useLimit) {
        vector <pair <int, int>> valueAndLabels = zipVecs(values, labels);
        sort(valueAndLabels.begin(), valueAndLabels.end(), greater <pair <int, int>>());

        return findMaximumSum(valueAndLabels, useLimit, numWanted);
    }
};
