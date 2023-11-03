// LeetCode-1441: https://leetcode.com/problems/build-an-array-with-stack-operations/
// wierd but easy problem

#include <vector>
#include <cassert>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector <string> operations;

        int i = 1;
        for (vector <int>::iterator it = target.begin(); it != target.end(); ) {
            int crrEle = *it;

            while (i < crrEle) {
                operations.push_back("Push");
                operations.push_back("Pop");

                i++;
            }

            operations.push_back("Push");
            i++;
            ++it;
        }

        return operations;
    }
};

class SolutionTest {
public:
    void testBuildArray() {
        Solution soln = Solution();
        int n;
        vector <int> target;
        vector <string> operationsOutExpected, operationsOutComputed;

        target = {1};
        n = 5;
        operationsOutExpected = {"Push"};
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);

        target = {1, 3};
        n = 3;
        operationsOutExpected = {"Push", "Push", "Pop", "Push"};
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);

        target = {1, 3};
        n = 5;
        operationsOutExpected = {"Push", "Push", "Pop", "Push"};
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);

        target = {1, 2, 3};
        n = 3;
        operationsOutExpected = {"Push", "Push", "Push"};
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);

        target = {1, 2};
        n = 4;
        operationsOutExpected = {"Push", "Push"};
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);

        target = {1, 3, 4, 5, 9};
        n = 12;
        operationsOutExpected = {
                "Push", // 1
                "Push", "Pop", // 2
                "Push", // 3
                "Push", // 4
                "Push", // 5
                "Push", "Pop", // 6
                "Push", "Pop", // 7
                "Push", "Pop", // 8
                "Push" // 9
                };
        operationsOutComputed = soln.buildArray(target, n);
        assert(operationsOutExpected == operationsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildArray();

    return 0;
}
