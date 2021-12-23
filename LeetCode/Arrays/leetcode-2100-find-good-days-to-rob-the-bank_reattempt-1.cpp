// LeetCode-2100: https://leetcode.com/problems/find-good-days-to-rob-the-bank/
// CodingDecoded: https://www.youtube.com/watch?v=cHfwQyZohoY

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> buildDecPrefixArr(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> decPrefix(len, 0);
        for (int i = 1; i < len; i++) {
            if (vec[i - 1] >= vec[i]) {
                decPrefix[i] = decPrefix[i - 1] + 1;
            }
        }

        return decPrefix;
    }

    vector<int> buildIncSuffixArr(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> incSuffix(len, 0);
        for (int i = len - 2; i >= 0; i--) {
            if (vec[i] <= vec[i + 1]) {
                incSuffix[i] = incSuffix[i + 1] + 1;
            }
        }

        return incSuffix;
    }

    vector<int> createIncVec(int len) {
        vector<int> vec(len);
        for (int i = 0; i < len; i++) {
            vec[i] = i;
        }

        return vec;
    }

    void showVec(vector<int>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

   public:
    friend class SolutionTest;

    vector<int> findValleyPoints(
        vector<int>& vec,
        int halfWidth,
        vector<int>& decPrefixArr,
        vector<int>& incSuffixArr) {
        int len = vec.size();

        vector<int> valleyPoints;
        for (int i = halfWidth; (i + halfWidth) < len; i++) {
            int decPrefixLen = decPrefixArr[i - 1];
            bool hasLongEnoughPrefix = decPrefixLen >= (halfWidth - 1);
            bool hasValidDecPrefix = vec[i - 1] >= vec[i];

            int incSuffixLen = incSuffixArr[i + 1];
            bool hasLongEnoughSuffix = incSuffixLen >= (halfWidth - 1);
            bool hasValidIncSuffix = vec[i] <= vec[i + 1];

            if (hasLongEnoughPrefix && hasValidDecPrefix && hasLongEnoughSuffix && hasValidIncSuffix) {
                valleyPoints.push_back(i);
            }
        }

        return valleyPoints;
    }

    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int len = security.size();
        if (len < ((2 * time) + 1)) {
            return {};
        }
        if (time == 0) {
            return createIncVec(len);
        }

        vector<int> decPrefixArr = buildDecPrefixArr(security);
        vector<int> incSuffixArr = buildIncSuffixArr(security);

        vector<int> valleyPoints = findValleyPoints(security, time, decPrefixArr, incSuffixArr);
        return valleyPoints;
    }
};

class SolutionTest {
   public:
    void testGoodDaysToRobBank() {
        Solution soln = Solution();
        vector<int> inVec;
        int inHalfWidth;
        vector<int> outVecExpected, outVecComputed;

        inVec = {};
        inHalfWidth = 0;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 8};
        inHalfWidth = 0;
        outVecExpected = {0, 1};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 3, 3, 3, 5, 6, 2};
        inHalfWidth = 2;
        outVecExpected = {2, 3};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {1, 1, 1, 1, 1};
        inHalfWidth = 0;
        outVecExpected = {0, 1, 2, 3, 4};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        // soln.debug = true;
        inVec = {1, 2, 3, 4, 5, 6};
        inHalfWidth = 2;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {1, 2, 3, 4};
        inHalfWidth = 1;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testGoodDaysToRobBank();

    return 0;
}
