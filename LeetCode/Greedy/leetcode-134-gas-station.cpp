// LeetCode-134: https://leetcode.com/problems/gas-station/
// excellent explaination here https://www.youtube.com/watch?v=wDgKaNrSOEI
// Very hard problem (extremely unintuitive logic)

#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void testVecSum();
int vecSum(vector<int>);
void testCanCompleteCircuit();
int canCompleteCircuit(vector<int>&, vector<int>&);

int main() {
    testVecSum();
    testCanCompleteCircuit();

    return 0;
}

void testVecSum() {
    vector<int> vecIn;

    vecIn = {};
    assert(vecSum(vecIn) == 0);

    vecIn = {0};
    assert(vecSum(vecIn) == 0);

    vecIn = {2};
    assert(vecSum(vecIn) == 2);

    vecIn = {2, 5};
    assert(vecSum(vecIn) == 7);

    vecIn = {8, -1, 4};
    assert(vecSum(vecIn) == 11);
}

int vecSum(vector<int> vec) {
    // https://stackoverflow.com/a/3221813/3679900
    return accumulate(vec.begin(), vec.end(), decltype(vec)::value_type(0));
}

void testCanCompleteCircuit() {
    vector<int> gasIn;
    vector<int> costIn;

    gasIn = {};
    costIn = {};
    assert(canCompleteCircuit(gasIn, costIn) == -1);

    gasIn = {};
    costIn = {5};
    assert(canCompleteCircuit(gasIn, costIn) == -1);

    gasIn = {};
    costIn = {};
    assert(canCompleteCircuit(gasIn, costIn) == -1);

    gasIn = {3};
    costIn = {5};
    assert(canCompleteCircuit(gasIn, costIn) == -1);

    gasIn = {5};
    costIn = {3};
    assert(canCompleteCircuit(gasIn, costIn) == 0);

    gasIn = {1,2,3,4,5};
    costIn = {3,4,5,1,2};
    assert(canCompleteCircuit(gasIn, costIn) == 3);

    gasIn = {2, 3, 4};
    costIn = {3, 4, 3};
    assert(canCompleteCircuit(gasIn, costIn) == -1);

    gasIn = {5, 1, 2, 3, 4};
    costIn = {4, 4, 1, 5, 1};
    assert(canCompleteCircuit(gasIn, costIn) == 4);
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    // empty / dumb cases
    if (gas.empty() || cost.empty() || gas.size() != cost.size()) {
        return -1;
    }

    // this check is NOT redundant
    if (gas.size() == 1) {
        return (gas[0] >= cost[0]) ? 0 : -1;
    }

    // determine if soln is possible or not
    int totalGasAvailable = vecSum(gas);
    int totalGasRequired = vecSum(cost);
    if (totalGasAvailable < totalGasRequired) {
        return -1;
    }

    // now we are certain that soln exists
    int startInd = 0;
    int gasInTank = 0;
    int prevGas = 0;
    int prevCost = 0;

    // note that loop limit has been made <= cost.size() because at ith iteration
    // we are adding net gains from i-1th hop
    for (int i = 0; i <= cost.size(); i++) {
        // determine gas in task by the time we reach this ith index
        // (starting from current startInd)
        gasInTank += prevGas - prevCost;

        // if negative, means that current startInd is not a valid soln,
        // so we reset startInd & gasInTank
        if (gasInTank < 0) {
            /**
             * an interesting point to note here is that despite loop limits dictate that i could exceed
             * last index, we are still safe because
             *  - by this point, we are certain that a soln exists
             *  - and this reset takes place only when we run into an infeasible start index (and are
             *    forced to discard existing value of startInd)
             * combining above two, it becomes clear that since soln exists, we won't ever run into the
             * case of having to reset the startInd at the stage when i exceeded array length
             */
            startInd = i;
            gasInTank = 0;
        }
        
        if (i < cost.size()) {
            prevGas = gas[i];
            prevCost = cost[i];
        }
    }

    /**
     * do understand that once we find an index from where we can get to end, it automatically implies
     * we have found the soln (we can wrap around the array and get to that index too)
     * why?
     *  1. (after watching video) we already know that any index prior to this one isn't a possible soln
     *  2. (after watching video) we also know that even if any index after this one is also a possible
     *     soln (which by the way can't be the case since question upfront says that only 1 soln exists),
     *     then this index too is a possible soln
     * combining above two facts with the fact that we had reached to this point of code only after
     * knowing that a solution certainly exists, implies that this is indeed the right soln
     */
    return startInd;
}
