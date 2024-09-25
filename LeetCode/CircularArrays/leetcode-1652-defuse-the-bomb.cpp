// LeetCode-1652: https://leetcode.com/problems/defuse-the-bomb/

#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    void showVec(vector<int>& vec, const char* name) {
        printf("%s vector is:-\n", name);

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    inline int getNextIdx(int idx, int len) {
        return (idx + 1) % len;
    }

    vector<int> createNextKSumVec(vector<int>& vec, int k) {
        int len = vec.size();
        vector<int> nextKSumVec(len);

        int crrKSum = accumulate(vec.begin() + 1, vec.begin() + k + 1, 0);
//        printf("crrKSum = %d\n", crrKSum);

        for (int i = 0; i < len; i++) {
            nextKSumVec[i] = crrKSum;
            crrKSum = crrKSum - vec[getNextIdx(i, len)] + vec[getNextIdx(i + k, len)];
        }

        return nextKSumVec;
    }

public:
    friend class SolutionTest;

    vector<int> decrypt(vector<int>& code, int k) {
        if (k > 0) {
            return createNextKSumVec(code, k);
        } else if (k == 0) {
            return vector<int>(code.size(), 0);
        } else {
            reverse(code.begin(), code.end());

            vector<int> nextKSumVec = createNextKSumVec(code, -k);

            reverse(nextKSumVec.begin(), nextKSumVec.end());
            return nextKSumVec;
        }
    }
};

class SolutionTest {
public:
    void testCreateNextKSumVec() {
        Solution soln = Solution();
        vector<int> vec;
        int k;
        vector<int> nextKSumVecOutExpected, nextKSumVecOutComputed;

        vec = {5, 7, 1, 4};

        k = 1;
        nextKSumVecOutExpected = {7, 1, 4, 5};
        nextKSumVecOutComputed = soln.createNextKSumVec(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        k = 2;
        nextKSumVecOutExpected = {8, 5, 9, 12};
        nextKSumVecOutComputed = soln.createNextKSumVec(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        k = 3;
        nextKSumVecOutExpected = {12, 10, 16, 13};
        nextKSumVecOutComputed = soln.createNextKSumVec(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        printf("[testCreateNextKSumVec] all test cases passed!\n");
    }

    void testDecrypt() {
        Solution soln = Solution();
        vector<int> vec;
        int k;
        vector<int> nextKSumVecOutExpected, nextKSumVecOutComputed;

        vec = {1, 2, 3, 4};
        k = 0;
        nextKSumVecOutExpected = {0, 0, 0, 0};
        nextKSumVecOutComputed = soln.decrypt(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        vec = {2, 4, 9, 3};
        k = -1;
        nextKSumVecOutExpected = {3, 2, 4, 9};
        nextKSumVecOutComputed = soln.decrypt(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        vec = {2, 4, 9, 3};
        k = -2;
        nextKSumVecOutExpected = {12, 5, 6, 13};
        nextKSumVecOutComputed = soln.decrypt(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        vec = {2, 4, 9, 3};
        k = -3;
        nextKSumVecOutExpected = {16, 14, 9, 15};
        nextKSumVecOutComputed = soln.decrypt(vec, k);
        assert(nextKSumVecOutExpected == nextKSumVecOutComputed);

        printf("[testDecrypt] all test cases passed!\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testCreateNextKSumVec();
    test.testDecrypt();

    return 0;
}

