// Dumb binary search problem
// LeetCode-374: https://leetcode.com/problems/guess-number-higher-or-lower/

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
   private:
    long long int guessNumRec(long long int lo, long long int hi) {
        if (lo > hi) {
            return -1;
        }

        long long int mid = (lo + hi) / 2;
        // this guess(..) function will be available in LeetCode runtime
        int guessResponse = guess(mid);

        if (guessResponse == -1) {
            return guessNumRec(lo, mid - 1);
        } else if (guessResponse == 0) {
            return mid;
        } else {
            return guessNumRec(mid + 1, hi);
        }
    }

   public:
    int guessNumber(int n) {
        return (int)guessNumRec(1, n);
    }
};
