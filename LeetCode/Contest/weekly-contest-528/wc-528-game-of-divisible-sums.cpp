// LeetCode WeeklyContest-528: https://leetcode.com/contest/weekly-contest-528/problems/game-of-divisible-sums/
// DynamicProgramming

#include <cassert>
#include <numeric>
#include <vector>
#include <utility>

using namespace std;

class Solution {
private:
    bool isDivisibleBy3(long long num) {
        return (num % 3) == 0;
    }

public:
    friend class SolutionTest;

    long long maxDifference(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return accumulate(nums.begin(), nums.end(), 0LL);
        }

        // {scoreOfPlayerStartingFirst, scoreOfPlayerStartingSecond}
        vector <pair <long long, long long>> memoVec(len);
        // if only 1 or 2 items left, always player starting first will take them all
        memoVec[len - 1] = {nums[len - 1], 0};
        memoVec[len - 2] = {nums[len - 2] + nums[len - 1], 0};

        for (int i = len - 3; i >= 0; i--) {
            // calculate scores if player-1 starts by taking 1 item
            long long case1P1Score = nums[i];
            long long case1P2Score;
            if (isDivisibleBy3(case1P1Score)) {
                // after player-1 then player-2 gets to play
                case1P1Score += memoVec[i + 1].second;
                case1P2Score = memoVec[i + 1].first;
            } else {
                // player-1 gets to play again
                case1P1Score += memoVec[i + 1].first;
                case1P2Score = memoVec[i + 1].second;
            }

            // calculate scores if player-1 starts by taking 2 items
            long long case2P1Score = nums[i] + nums[i + 1];
            long long case2P2Score;
            if (isDivisibleBy3(case2P1Score)) {
                // after player-1 then player-2 gets to play
                case2P1Score += memoVec[i + 2].second;
                case2P2Score = memoVec[i + 2].first;
            } else {
                // player-1 gets to play again
                case2P1Score += memoVec[i + 2].first;
                case2P2Score = memoVec[i + 2].second;
            }

            // calculate and populate max scores for both players
            if (case1P1Score > case2P1Score) {
                memoVec[i] = {case1P1Score, case1P2Score};
            } else {
                memoVec[i] = {case2P1Score, case2P2Score};
            }
        }

        pair <long long, long long> maxScores = memoVec[0];
        return (maxScores.first - maxScores.second);
    }
};

class SolutionTest {
public:
    void testMaxDifference() {
        Solution soln = Solution();
        vector <int> numsIn;
        long long outExpected, outComputed;

        numsIn = {3,6,4};
        outExpected = 5;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {6,1,2,1,2};
        outExpected = 12;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {3, 3, 4, 5};
        outExpected = -3;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {9};
        outExpected = 9;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {9, 1};
        outExpected = 10;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {9, 1, 5};
        outExpected = 15;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {9, 2, 5};
        outExpected = 16;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);

        numsIn = {9, 3, 5};
        outExpected = 7;
        outComputed = soln.maxDifference(numsIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxDifference();

    return 0;
}
