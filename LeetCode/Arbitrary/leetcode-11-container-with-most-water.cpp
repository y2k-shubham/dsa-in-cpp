// LeetCode-11: https://leetcode.com/problems/container-with-most-water/
// Nick-White: https://www.youtube.com/watch?v=6PrIRPpTI9Q

/*
 * a proposed soln that leverages solns to existing problems to solve this one
 * 1. apply rainwater trapping on this problem to determine the height till which water
 *    be filled on each posn; now use the output array (that stores height of water) as
 *    input to next step
 * 2. apply maximum area under rectangle to obtain those two bars that will hold maximum
 *    water between them
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) {
    int maxVolume = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
        int crrVolume = min(height[i], height[j]) * (j - i);
        maxVolume = max(maxVolume, crrVolume);

        if (height[i] < height[j]) {
            i++;
        } else {
            j--;
        }
    }
    return maxVolume;
}
