// LeetCode-220: https://leetcode.com/problems/contains-duplicate-iii/
// Companies: [Google][Netflix][Microsoft][Amazon][Bloomberg][Meta]
// Incomplete

#include <vector>
#include <map>
#include <queue>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    map <int, int> mFreqMap;
    queue <int> mQue;
    int windowSize;
    int valDiffSize;
    bool debug;

    // ------ debug helpers ------

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showQue() {
        queue <int> mQueCopy = mQue;

        printf("Que is:-\n");
        while (!mQueCopy.empty()) {
            int val = mQueCopy.front();
            mQueCopy.pop();

            printf("%d ", val);
        }
        printf("\n");
    }

    void showMap() {
        printf("Map is:-\n");

        for (auto it = mFreqMap.begin(); it != mFreqMap.end(); ++it) {
            printf("%d -> %d\n", it->first, it->second);
        }
        printf("\n");
    }

    void showSingleSeparator() {
        printf("--------------\n");
    }

    void showDoubleSeparator() {
        printf("\n==============\n\n");
    }

    // ------ CRUD helpers ------

    void replaceOldestValWith(int val) {
        int crrNumVals = mQue.size();
        // we keep 1 lesser element than allowed
        // (current element is not added into the map to avoid duplicate checks logic)
        if (crrNumVals >= (windowSize - 1)) {
            if (debug) {
                showSingleSeparator();
                printf("before dropping");
                showSingleSeparator();

                cout << endl;
                showQue();
                cout << endl;
                showMap();
            }

            int droppedVal = dropOldestVal();
            if (debug) {
                printf("dropped val:%d\n", droppedVal);
            }
        }

        addVal(val);
        if (debug) {
            showSingleSeparator();
            printf("after adding new val: %d\n", val);
            showSingleSeparator();

            cout << endl;
            showQue();
            cout << endl;
            showMap();

            showDoubleSeparator();
        }
    }

    void addVal(int val) {
        mQue.push(val);
        addValToMap(val);
    }

    void addValToMap(int val) {
        mFreqMap[val]++;
    }

    int dropOldestVal() {
        int val = mQue.front();

        // remove from queue
        mQue.pop();

        // remove from map
        dropValFromMap(val);

        return val;
    }

    void dropValFromMap(int val) {
        int crrFreq = mFreqMap[val];
        if (crrFreq <= 1) {
            mFreqMap.erase(val);
        } else {
            mFreqMap[val] = crrFreq - 1;
        }
    }

    // ------ init helpers ------

    bool addFirstWindowVals(vector<int>& nums, int windowSize) {
        int len = nums.size();
        int iMaxExc = min(len, windowSize);

        for (int i = 0; i < iMaxExc; i++) {
            int val = nums[i];

            if (containsAlmostDuplicate(val)) {
                if (debug) {
                    printf("\nfound match within first %d vals when processing val=%d\n", windowSize, val);
                }
                return true;
            }

            addVal(val);

            if (debug) {
                showSingleSeparator();
                printf("after adding initial window val = %d\n", val);
                showSingleSeparator();

                showQue();
                cout << endl;
                showMap();
                cout << endl;

                showDoubleSeparator();
            }
        }

        return false;
    }

    // ------ search helpers ------

    bool containsAlmostDuplicate(int val) {
        if (mFreqMap.empty()) {
            if (debug) {
                printf("\nempty map\n");
            }
            return false;
        }

        if (valDiffSize == 0) {
            if (mFreqMap.find(val) != mFreqMap.end()) {
                return true;
            } else {
                return false;
            }
        }

        map<int, int>::iterator itLower = mFreqMap.lower_bound(val - valDiffSize);
        if (itLower != mFreqMap.end()) {
            if (debug) {
                printf("\nMatched at lower_bound = %d when searching for (val=%d + diff=%d) = %d\n", itLower->first, val, valDiffSize, (val - valDiffSize));
            }
            return true;
        }

        map<int, int>::iterator itUpper = mFreqMap.upper_bound(val + valDiffSize);
        if (itUpper != mFreqMap.begin()) {
            if (itUpper == mFreqMap.end()) {
                itUpper--;
            }

            if ((itUpper->first >= val) && (itUpper->first <= (val + valDiffSize))) {
                if (debug) {
                    printf("\nMatched at upper_bound = %d when searching for (val=%d + diff=%d) = %d\n", itUpper->first, val, valDiffSize, (val + valDiffSize));
                }
                return true;
            }
        }

        if (debug) {
            printf("\nNo duplicates found yet\n");
        }
        return false;
    }

public:
    friend class SolutionTest;

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        // clear map and queue
        this->mFreqMap.clear();
        this->mQue = queue<int>();

        // assign globals
        this->windowSize = (2 * indexDiff);
        this->valDiffSize = valueDiff;

        // fill initial window vals
        if (addFirstWindowVals(nums, windowSize)) {
            if (debug) {
                printf("\nfound match within first %d vals\n", windowSize);
            }
            return true;
        }

        if (debug) {
            showSingleSeparator();
            printf("after populating first %d vals\n", windowSize);
            showSingleSeparator();

            showQue();
            cout << endl;
            showMap();
            cout << endl;

            showDoubleSeparator();
        }

        int len = nums.size();
        int iMaxExc = len - indexDiff;
        int jMinInc = (2 * indexDiff);

        for (int i = indexDiff, j = jMinInc; (i < iMaxExc) && (j < len); i++, j++) {
            // add new incoming val
            int jVal = nums[j];
            addVal(jVal);

            // read current value
            int iVal = nums[i];

            // remove current value from map
            dropValFromMap(iVal);

            // check if map contains near-duplicates
            if (containsAlmostDuplicate(iVal)) {
                return true;
            }

            // re-add current value to map
            addValToMap(iVal);

            // advance window by dropping oldest value
            dropOldestVal();
        }

        return false;
    }
};

class SolutionTest {
public:
    void testContainsNearbyAlmostDuplicate() {
        Solution soln = Solution();
        vector <int> numsIn;
        int indexDiffIn, valueDiffIn;
        bool outExpected, outComputed;

        numsIn = {1,2,3,1};
        indexDiffIn = 3;
        valueDiffIn = 0;
        outComputed = soln.containsNearbyAlmostDuplicate(numsIn, indexDiffIn, valueDiffIn);
        outExpected = true;
        assert(outExpected == outComputed);

        printf("\n/////////////////\n\n");

        soln.enableDebug();

        numsIn = {1,5,9,1,5,9};
        indexDiffIn = 2;
        valueDiffIn = 3;
        outComputed = soln.containsNearbyAlmostDuplicate(numsIn, indexDiffIn, valueDiffIn);
        outExpected = false;
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testContainsNearbyAlmostDuplicate();

    return 0;
}
