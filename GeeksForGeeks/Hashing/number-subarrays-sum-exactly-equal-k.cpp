// https://www.geeksforgeeks.org/number-subarrays-sum-exactly-equal-k/
// https://leetcode.com/problems/subarray-sum-equals-k/

// quite tough problem

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

void testFindSubArrCount();
int findSubArrCount(vector<int>, int);

int main() {
    testFindSubArrCount();

    return 0;
}

void testFindSubArrCount() {
    assert(findSubArrCount({}, 0) == 0);
    assert(findSubArrCount({}, 1) == 0);
    assert(findSubArrCount({2, 3}, 0) == 0);
    assert(findSubArrCount({-2, -3}, 0) == 0);
    assert(findSubArrCount({0}, 0) == 1);
    assert(findSubArrCount({1, -2, 1}, 0) == 1);
    assert(findSubArrCount({1, -2, 1, 4}, 3) == 1);
    assert(findSubArrCount({1, 2, -11, 8}, 0) == 1);
    assert(findSubArrCount({1, -22, 15, 4, -6, 1}, -9) == 1);
    assert(findSubArrCount({1, -22, 15, 4, -6, -1}, -9) == 2);
    assert(findSubArrCount({1, -22, 15, 4, 6, -1}, 10) == 1);
    assert(findSubArrCount({1, -22, 15, 4, 6, -1}, 9) == 1);
    assert(findSubArrCount({1, -22, 15, 4, 6, -1, 9}, 9) == 2);
    assert(findSubArrCount({1, -22, 15, 4, 6, -1, 9, -18, 12, -3}, 9) == 4);
    assert(findSubArrCount({1, 2, 1, 2, 1}, 3) == 4);
}

int findSubArrCount(vector<int> vec, int k) {
    if (vec.empty()) {
        return 0;
    } else {
        map<int, int> cumSumFreq;
        // do NOT use cumSumFreq[k] to keep this, rather use a simple variable (or it overestimates the answer)
        int countKSum = 0;

        int crrSum = 0;
        cumSumFreq[0] = 1;
        for (int i = 0; i < vec.size(); i++) {
            crrSum += vec[i];

            // do note that diff-sum has to be increased before crrSum increment (or else it overshoots the answer)
            int diff = crrSum - k;
            if (cumSumFreq.find(diff) != cumSumFreq.end()) {
                int extraInc = cumSumFreq[diff];
                countKSum += extraInc;
            }

            cumSumFreq[crrSum]++;
        }

        return countKSum;
    }
}
