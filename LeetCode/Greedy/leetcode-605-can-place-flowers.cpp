// LeetCode-605: https://leetcode.com/problems/can-place-flowers/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int len = flowerbed.size();

    if (n == 0) {
        return true;
    } else if (len < n) {
        return false;
    } else if (len == 1) {
        return (n == 1) && (flowerbed[0] == 0);
    } else {
        int numFlowersPlaced = 0;

        // first posn of flowerbed having 2 or more places
        if ((len >= 2) && ((flowerbed[0] | flowerbed[1]) == 0)) {
            flowerbed[0] = 1;
            numFlowersPlaced++;
        }

        for (int i = 1; i <= (len - 2); i++) {
            if ((flowerbed[i - 1] | flowerbed[i] | flowerbed[i + 1]) == 0) {
                flowerbed[i] = 1;
                numFlowersPlaced++;

                if (numFlowersPlaced >= n) {
                    return true;
                }
            }
        }

        // last posn of flowerbed having 2 or more places
        if ((len >= 2) && ((flowerbed[len - 2] | flowerbed[len - 1]) == 0)) {
            flowerbed[len - 1] = 1;
            numFlowersPlaced++;
        }

        return (numFlowersPlaced >= n);
    }
}
