// LeetCode-1562: https://leetcode.com/problems/find-latest-group-of-size-m/
// incomplete

#include <set>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    bool debug = false;

    void showAllRanges(set <pair<int,int>>& allRanges, string when) {
        printf("%s, allRanges are:-\n", when.c_str());
        printf("{");
        for (pair<int,int> range : allRanges) {
            if (range.first == range.second) {
                printf(" (%d) ", range.first);
            } else {
                printf(" (%d,%d) ", range.first, range.second);
            }
        }
        printf("}\n");
    }

    void eraseRange(set<pair<int, int>>& allRanges, unordered_map<int, int>& rangeSizeFreq, pair<int, int> range) {
        allRanges.erase(range);
        rangeSizeFreq[range.second - range.first + 1]--;
    }

    void addRange(set<pair<int, int>>& allRanges, unordered_map<int, int>& rangeSizeFreq, pair<int, int> range) {
        allRanges.insert(range);
        rangeSizeFreq[range.second - range.first + 1]++;
    }

    pair<int, int> insertRange(set<pair<int, int>>& allRanges, unordered_map<int, int>& rangeSizeFreq, pair<int, int> rangeNew) {
        bool canMergeLowerRange = false;
        bool canMergeUpperRange = false;
        pair<int, int> rangeLower = {-1, -1};
        pair<int, int> rangeUpper = {-1, -1};

        auto itLower = allRanges.lower_bound(rangeNew);
        if (!allRanges.empty()) {
            if (itLower == allRanges.begin()) {
                rangeUpper = *itLower;
            }
            if (itLower == allRanges.end()) {
                itLower--;
                rangeLower = *itLower;
            }

            if ((rangeLower.second + 1) == rangeNew.first) {
                canMergeLowerRange = true;
            }
            if ((rangeNew.second + 1) == rangeUpper.first) {
                canMergeUpperRange = true;
            }
        }

        pair<int, int> updatedNewRange;
        if (canMergeLowerRange && canMergeUpperRange) {
            updatedNewRange = {rangeLower.first, rangeUpper.second};
            eraseRange(allRanges, rangeSizeFreq, rangeLower);
            eraseRange(allRanges, rangeSizeFreq, rangeUpper);
            if (debug) {
                printf("erased both lowerBound=(%d,%d) and upperBound=(%d,%d) while inserting newRange=(%d)\n", rangeLower.first, rangeLower.second, rangeUpper.first, rangeUpper.second, rangeNew.first);
            }
        } else if (canMergeLowerRange) {
            eraseRange(allRanges, rangeSizeFreq, rangeLower);
            updatedNewRange = {rangeLower.first, rangeNew.second};
            if (debug) {
                printf("erased only lowerBound=(%d,%d) while inserting newRange=(%d)\n", rangeLower.first, rangeLower.second, rangeNew.first);
            }
        } else if (canMergeUpperRange) {
            eraseRange(allRanges, rangeSizeFreq, rangeUpper);
            updatedNewRange = {rangeNew.first, rangeUpper.second};
            if (debug) {
                printf("erased only upperBound=(%d,%d) while inserting newRange=(%d)\n", rangeUpper.first, rangeUpper.second, rangeNew.first);
            }
        } else {
            updatedNewRange = rangeNew;
            if (debug) {
                printf("erased no pre-existing ranges while inserting newRange=(%d)\n", rangeNew.first);
            }
        }

        addRange(allRanges, rangeSizeFreq, updatedNewRange);
        return updatedNewRange;
    }

public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if (m > n) {
            return -1;
        }

        set<pair<int, int>> allRanges;
        unordered_map<int, int> rangeSizeFreq;
        int lastIdx = -1;
        for (int i = 0; i < n; i++) {
            int val = arr[i] - 1;
            pair<int, int> newRange = {val, val};

            if (debug) {
                showAllRanges(allRanges, "before inserting (" + to_string(newRange.first) + ")");
            }
            insertRange(allRanges, rangeSizeFreq, newRange);
            if (debug) {
                showAllRanges(allRanges, "after inserting (" + to_string(newRange.first) + ")");
            }

            if (rangeSizeFreq[m] >= 1) {
                lastIdx = i + 1;
            }

            if (debug) {
                printf("\n----------\n");
            }
        }

        return lastIdx;
    }
};
