// LeetCode-624: https://leetcode.com/problems/maximum-distance-in-arrays/

#include <vector>

using namespace std;

class Solution {
private:
    pair <pair <int, int>, pair <int, int>> findMinElements(vector <vector <int>>& arrays) {
        pair <int, int> min1Element = {INT_MAX, -1};
        pair <int, int> min2Element = {INT_MAX, -1};

        for (int i = 0; i < arrays.size(); i++) {
            int crrElement = arrays[i][0];

            if (crrElement < min1Element.first) {
                min2Element = min1Element;
                min1Element = {crrElement, i};
            } else if (crrElement < min2Element.first) {
                min2Element = {crrElement, i};
            }
        }

        return {min1Element, min2Element};
    }

    pair <pair <int, int>, pair <int, int>> findMaxElements(vector <vector <int>>& arrays) {
        pair <int, int> max1Element = {INT_MIN, -1};
        pair <int, int> max2Element = {INT_MIN, -1};

        for (int i = 0; i < arrays.size(); i++) {
            int len = arrays[i].size();
            int crrElement = arrays[i][len - 1];

            if (crrElement > max1Element.first) {
                max2Element = max1Element;
                max1Element = {crrElement, i};
            } else if (crrElement > max2Element.first) {
                max2Element = {crrElement, i};
            }
        }

        return {max1Element, max2Element};
    }

public:
    int maxDistance(vector <vector <int>>& arrays) {
        pair <pair <int, int>, pair <int, int>> minElements = findMinElements(arrays);
        pair <int, int> min1Element = minElements.first;
        pair <int, int> min2Element = minElements.second;

        pair <pair <int, int>, pair <int, int>> maxElements = findMaxElements(arrays);
        pair <int, int> max1Element = maxElements.first;
        pair <int, int> max2Element = maxElements.second;

        if (min1Element.second != max1Element.second) {
            // if min & max elements come from different arrays
            return abs(max1Element.first - min1Element.first);
        } else {
            // calculate diffs 1 & 2 and take the bigger of them
            int diff1 = abs(max1Element.first - min2Element.first);
            int diff2 = abs(max2Element.first - min1Element.first);
            return max(diff1, diff2);
        }
    }
};
