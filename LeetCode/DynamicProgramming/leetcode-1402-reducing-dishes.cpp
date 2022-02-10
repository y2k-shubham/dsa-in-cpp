// not the conventional dynamic programming question
// (since it is solved in linear time)

/**
 * given dish satisfaction scores [-1,-8,0,5,-9]
 * 
 * we start by sorting satisfaction scores of dishes in ascending order
 * [-9,-8,-1,0,5]
 * 
 * now we have to assign indexes (which will also act as multipliers) to above array starting from 1
 * (anything at and below index 0 will be ignored) so as to maximize the sum of products
 * 
 * the most straightforward assignment would be to assign indexes starting 1 to the lowest positive number
 * [-9, -8, -1, 0, 5]
 * [               1]
 * here sum of products would be 5x1 = 5
 * note that this sum is what is being calculated int the calcProgressiveSum(..) fn
 * 
 * to (try to) increase the sum, we can shift this assignment leftwards
 *  - that would increase the weight / contrib of positive elements
 *  - (although it would also increase negative contrib of negative elements)
 * 
 * [-9, -8, -1, 0, 5]
 * [            1  2]
 * this assignment gives a sum of 0x1 + 5x2 = 10
 * 
 * [-9, -8, -1, 0, 5]
 * [         1  2  3]
 * while this one gives -1x1 + 0x2 + 5x3 = 14
 * this is the maximum possible sum
 * - further leftwards, we'll only get smaller sums
 * - (although we must not think of it is a pattern -> for safety we must calculate sum by moving leftwards all the way to beginning)
 * 
 * now obvious challenge here is how to efficiently re-calculate the sum after every leftward move
 * this can be done in constant time by using the result(s) in previous step (hence dyanamic programming) as follows
 * - updated contrib of positive numbers is easy: in each step it will increase by sigma(arr+) -> the total sum of all positive elements
 * - updated contrib of negative numbers will be equal to sum of
 *   1. contrib of negative numbers in previous step
 *   2. sum of negative numbers seen so far (moving from right to left up till current index)
 *   3. current negative number (where we just arrived)
 * 
 * this ways, we can recalculate updated sum at each step in constant time
 * and the solution is obtained in linear time (except for sorting of array; :meh:)
 */

#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
   // determine index of first positive number using binary search
    int binSearchPositiveIdxFloor(vector<int>& sortedVec, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return INT_MAX;
        }

        int mid = (lo + hi) / 2;
        int midEle = sortedVec[mid];

        if (midEle >= 1) {
            return min(mid, binSearchPositiveIdxFloor(sortedVec, lo, mid - 1));
        } else {
            return binSearchPositiveIdxFloor(sortedVec, mid + 1, hi);
        }
    }

    // calculate sum of a slice of array
    int calcSum(vector<int>& vec, int startIdx, int endIdx) {
        return accumulate(vec.begin() + startIdx, vec.begin() + endIdx + 1, 0);
    }

    // calculate the baseline sum (most straightforward assignment)
    int calcProgressiveSum(vector<int>& vec, int startIdx, int endIdx) {
        int sum = 0;

        int ctr = 1;
        for (int i = startIdx; i <= endIdx; i++, ctr++) {
            sum += vec[i] * ctr;
        }

        return sum;
    }

   public:
    int maxSatisfaction(vector<int>& vec) {
        sort(vec.begin(), vec.end());

        int len = vec.size();
        if (vec[len - 1] <= 0) {
            return 0;
        }

        int positiveBeginIdx = binSearchPositiveIdxFloor(vec, 0, len - 1);
        int totalPositiveSum = calcSum(vec, positiveBeginIdx, len - 1);
        int baselinePositiveSum = calcProgressiveSum(vec, positiveBeginIdx, len - 1);

        // initialize with baseline assigment
        int maxSatisfaction = baselinePositiveSum;

        int prevPositiveContrib = baselinePositiveSum;
        int prevNegativeContrib = 0;
        int crrNegativeSum = 0;
        for (int i = positiveBeginIdx - 1; i >= 0; i--) {
            int crrEle = vec[i];

            // re-calculate contrib of positive and negative numbers at each step
            int crrNegativeContrib = prevNegativeContrib + crrNegativeSum + crrEle;
            int crrPositiveContrib = prevPositiveContrib + totalPositiveSum;

            // calculate satisfaction obtained from current assignment and update the maxSatisfaction
            int crrSatisfaction = crrPositiveContrib + crrNegativeContrib;
            maxSatisfaction = max(maxSatisfaction, crrSatisfaction);

            // update sum of negative numbers seen so far
            crrNegativeSum += crrEle;

            // update 'state' variables
            prevNegativeContrib = crrNegativeContrib;
            prevPositiveContrib = crrPositiveContrib;
        }

        return maxSatisfaction;
    }
};
