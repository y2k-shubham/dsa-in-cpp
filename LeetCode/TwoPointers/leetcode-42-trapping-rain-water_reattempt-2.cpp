// LeetCode-42: https://leetcode.com/problems/trapping-rain-water/

// Companies: [Amazon][Google][Meta][Microsoft][Bloomberg][Goldman Sachs][Media.net][Infosys][Snowflake][tcs][Rakuten][Nvidia][Accenture][TikTok][Zoho][Walmart Labs][Zopsmart][Samsung][Visa][Apple][Oracle][ServiceNow][Flipkart]

#include <numeric>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    // ----- debugging -----

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl
             << endl;
    }

    // ----- left to right fill methods -----

    int findVesselStartIdxFromLeft(vector <int>& height, int startIdx) {
        int len = height.size();
        if (startIdx >= (len - 2)) {
            return INT_MAX;
        }

        // swallow until we find a bar where the next bar on the right is shorter than it
        int i;
        for (i = startIdx; ((i + 1) < len) && (height[i] <= height[i + 1]); i++) {}

        if (i >= (len - 2)) {
            return INT_MAX;
        } else {
            return i;
        }
    }

    int findVesselEndIdxFromLeft(vector <int>& height, int startIdx) {
        int len = height.size();
        if (startIdx >= (len - 2)) {
            return INT_MAX;
        }

        int startHeight = height[startIdx];
        int i;
        // swallow until we find a bar at least as high as starting bar
        for (i = (startIdx + 1); (i < len) && (startHeight > height[i]); i++) {}

        if (i >= len) {
            return INT_MAX;
        } else {
            return i;
        }
    }

    void findAndFillVesselsFromLeft(vector <int>& height, vector<int>& water) {
        int len = height.size();
        for (int startIdx = 0; startIdx <= (len - 2); ) {
            // find left boundary of vessel
            startIdx = findVesselStartIdxFromLeft(height, startIdx);
            if (startIdx >= (len - 2)) {
                return;
            }
            // printf("found left boundary at startIdx=%d ; ", startIdx);

            // find right boundary of vessel
            int endIdx = findVesselEndIdxFromLeft(height, startIdx);
            if (endIdx >= len) {
                // printf("\n");
                return;
            }
            // printf("found right boundary at endIdx=%d \n", endIdx);

            // fill water
            fillWater(height, water, startIdx, endIdx);

            // advance pointer to find left boundary of next vessel in next iteration
            startIdx = endIdx;
        }
    }

    // ----- right to left fill methods -----

    int findVesselStartIdxFromRight(vector <int>& height, int startIdx) {
        if (startIdx <= 1) {
            return INT_MIN;
        }

        // swallow until we find a bar where the next bar on the left is shorter than it
        int i;
        for (i = startIdx; ((i - 1) >= 0) && (height[i - 1] >= height[i]); i--) {}

        if (i <= 1) {
            return INT_MIN;
        } else {
            return i;
        }
    }

    int findVesselEndIdxFromRight(vector <int>& height, int startIdx) {
        if (startIdx <= 1) {
            return INT_MIN;
        }

        int startHeight = height[startIdx];
        int i;
        // swallow until we find a bar at least as high as starting bar
        for (i = (startIdx - 1); (i >= 0) && (height[i] < startHeight); i--) {}

        if (i < 0) {
            return INT_MIN;
        } else {
            return i;
        }
    }

    void findAndFillVesselsFromRight(vector <int>& height, vector<int>& water) {
        int len = height.size();
        for (int startIdx = len - 1; 1 <= startIdx; ) {
            // find right boundary of vessel
            startIdx = findVesselStartIdxFromRight(height, startIdx);
            if (startIdx <= 1) {
                return;
            }
            // printf("found right boundary at startIdx=%d ; ", startIdx);

            // find left boundary of vessel
            int endIdx = findVesselEndIdxFromRight(height, startIdx);
            if (endIdx < 0) {
                // printf("\n");
                return;
            }
            // printf("found left boundary at endIdx=%d\n", endIdx);

            // fill water
            fillWater(height, water, endIdx, startIdx);

            // advance pointer to find right boundary of next vessel in next iteration
            startIdx = endIdx;
        }
    }

    // ----- common methods -----

    void fillWater(vector <int>& height, vector <int>& water, int leftIdx, int rightIdx) {
        int minHeight = min(height[leftIdx], height[rightIdx]);
        for (int i = (leftIdx + 1); i < rightIdx; i++) {
            water[i] = max(water[i], minHeight);
        }
    }

    int calculateWaterVolume(vector <int>& height, vector <int>& water) {
        int len = height.size();

        int waterVolume = 0;
        for (int i = 0; i < len; i++) {
            if (water[i] > 0) {
                waterVolume += water[i] - height[i];
            }
        }

        return waterVolume;
    }

public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2) {
            return 0;
        }

        vector <int> water(len, 0);

        findAndFillVesselsFromLeft(height, water);
        // printf("------ after left to right fill ------\n");
        // showVec(water, "water");

        findAndFillVesselsFromRight(height, water);
        // printf("------ after right to left fill ------\n");
        // showVec(water, "water");

        return calculateWaterVolume(height, water);
    }
};
