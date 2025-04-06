// LeetCode-368: https://leetcode.com/problems/largest-divisible-subset/

#include <list>
#include <algorithm>
#include <unordered_set>
#include <cassert>
#include <functional>

using namespace std;

class Subset {
private:
    int minElement;
    unordered_set <int> elements;

public:
    Subset(int element) {
        unordered_set <int> elements = {element};
        this->minElement = element;
    }

    int getNumElements() {
        return this->elements.size();
    }

    int getMinElement() {
        return minElement;
    }

    unordered_set <int> getElements() {
        return this->elements;
    }

    void insert(int element) {
        this->elements.insert(element);
        this->minElement = min(this->minElement, element);
    }

    void showSubset() {
        printf("Subset: ");
        for (int element : this->elements) {
            printf("%d ", element);
        }
        printf("(minElement = %d)\n", getMinElement());
    }
};

void showVec(vector <int>& vec, const char* name) {
    printf("%s vec is: ", name);
    for (int element : vec) {
        printf("%d ", element);
    }
    printf("\n");
}

class Solution {
private:
    bool debug = false;

    void enableDebug() {
        this->debug = true;
    }

    void disableDebug() {
        this->debug = false;
    }

    list <Subset> buildSubsets(vector <int>& nums) {
        int len = nums.size();

        sort(nums.begin(), nums.end(), greater<int>());
        if (debug) {
            showVec(nums, "after sorting nums");
        }

        list <Subset> subsets;
        if (debug) {
            printf("Creating singleton subset using element %d\n", nums[0]);
        }
        subsets.push_back(Subset(nums[0]));

        for (int i = 1; i < len; i++) {
            int crrElement = nums[i];
            bool addedInSomeSubset = false;
            if (debug) {
                printf("\nProcessing element %d\n", crrElement);
            }

            for (Subset subset : subsets) {
                if ((subset.getMinElement() % crrElement) == 0) {
                    if (debug) {
                        printf("\ninserting %d in ", crrElement);
                        subset.showSubset();
                    }

                    subset.insert(crrElement);
                    addedInSomeSubset = true;
                } else if (debug) {
                    printf("\nnot inserting %d in ", crrElement);
                    subset.showSubset();
                }
            }

            if (!addedInSomeSubset) {
                if (debug) {
                    printf("Creating singleton subset with element %d\n", crrElement);
                }
                subsets.push_back(Subset(crrElement));
            }
        }

        return subsets;
    }

    Subset findLargestSubset(list <Subset>& subsets) {
        Subset largestSubset = *subsets.begin();

        for (Subset subset : subsets) {
            if (subset.getNumElements() > largestSubset.getNumElements()) {
                largestSubset = subset;
            }
        }

        return largestSubset;
    }

    vector <int> convertSubsetToVec(Subset subset) {
        vector <int> subsetVec(subset.getElements().begin(), subset.getElements().end());
        return subsetVec;
    }

public:
    friend class SolutionTest;

    vector <int> largestDivisibleSubset(vector <int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return nums;
        }

        list <Subset> subsets = buildSubsets(nums);
        Subset largestSubset = findLargestSubset(subsets);

        vector <int> largestSubsetElements = convertSubsetToVec(largestSubset);
        sort(largestSubsetElements.begin(), largestSubsetElements.end());
        return largestSubsetElements;
    }
};

class SolutionTest {
private:
    void assertVectorsEqualIgnoringOrder(vector <int>& expected, vector <int>& actual) {
        sort(expected.begin(), expected.end());
        sort(actual.begin(), actual.end());

        assert(expected == actual);
    }

    void assertVectorOneOfIgnoringOrder(unordered_set<vector <int>>& expectedVecs, vector <int>& actual) {
        sort(actual.begin(), actual.end());
        for (vector <int> expected : expectedVecs) {
            sort(expected.begin(), expected.end());
            if (expected == actual) {
                return;
            }
        }

        assert(false);
    }

public:
    void testLargestDivisibleSubset() {
        Solution soln = Solution();
        vector <int> nums;
        unordered_set<vector <int>> expectedOutputVecs;
        vector<int> actualOutput;

        soln.enableDebug();
        nums = {1, 2, 3};
        expectedOutputVecs = {{1, 2}, {1, 3}};
        actualOutput = soln.largestDivisibleSubset(nums);
        assertVectorOneOfIgnoringOrder(expectedOutputVecs, actualOutput);
        soln.disableDebug();
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testLargestDivisibleSubset();

    return 0;
}
