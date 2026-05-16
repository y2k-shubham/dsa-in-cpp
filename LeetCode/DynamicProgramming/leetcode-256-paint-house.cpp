// LeetCode-256: https://leetcode.com/problems/paint-house/

#include <vector>

using namespace std;

class Cost {
public:
    int red;
    int blue;
    int green;

    Cost() : red(INT_MAX), blue(INT_MAX), green(INT_MAX) {}

    Cost(int red, int blue, int green) : red(red), blue(blue), green(green) {}
};

class Solution {
private:
    vector<Cost> convertToCostVec(vector<vector<int>>& costMat) {
        int costsSize = costMat.size();
        vector<Cost> costVec(costsSize, Cost());

        for (int i = 0; i < costsSize; i++) {
            vector<int> costRow = costMat[i];

            costVec[i].red = costRow[0];
            costVec[i].blue = costRow[1];
            costVec[i].green = costRow[2];
        }

        return costVec;
    }

    vector<Cost> buildMinCostVec(vector<Cost>& costVec) {
        int costsSize = costVec.size();

        vector<Cost> minCostVec(costsSize, Cost());
        minCostVec[0] = costVec[0];

        return minCostVec;
    }

    void fillMinCostVec(
        vector<Cost>& costVec,
        vector<Cost>& minCostVec) {
        for (int j = 1; j < costVec.size(); j++) {
            minCostVec[j].red = costVec[j].red + min(minCostVec[j - 1].blue, minCostVec[j - 1].green);
            minCostVec[j].blue = costVec[j].blue + min(minCostVec[j - 1].red, minCostVec[j - 1].green);
            minCostVec[j].green = costVec[j].green + min(minCostVec[j - 1].red, minCostVec[j - 1].blue);
        }
    }

public:
    int minCost(vector<vector<int>>& costs) {
        int len = costs.size();
        if (len < 1) {
            return 0;
        }

        vector<Cost> costVec = convertToCostVec(costs);

        vector<Cost> minCostVec = buildMinCostVec(costVec);
        fillMinCostVec(costVec, minCostVec);

        return min(
            minCostVec[len - 1].red,
            min(
                minCostVec[len - 1].blue,
                minCostVec[len - 1].green)
        );
    }
};
