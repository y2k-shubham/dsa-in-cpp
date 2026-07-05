// LeetCode-651: https://leetcode.com/problems/4-keys-keyboard/
// intuition provided by Claude

#include <vector>
#include <cassert>

using namespace std;

#define MAX_N_TILL_NO_GAIN 3

class Solution {
private:
    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showMemoVec(vector<int>& memoVec) {
        int len = memoVec.size();

        printf("Idx:\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < len; i++) {
            if (memoVec[i] >= 0) {
                printf("%d\t", memoVec[i]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }

    vector<int> createMemoVec(int n) {
        vector<int> memoVec(n + 1, -1);

        for (int i = 0; i <= MAX_N_TILL_NO_GAIN; i++) {
            memoVec[i] = i;
        }

        return memoVec;
    }

    void fillMemoVec(vector<int>& memoVec) {
        int len = memoVec.size();

        for (int i = MAX_N_TILL_NO_GAIN + 1; i <= len; i++) {
            if (debug) {
                printf("\n-----------\n");
                printf("Before i=%d, memoVec:-\n", i);
                showMemoVec(memoVec);
            }

            int maxAs = i; // implicitly we can type A's i times

            // j = no of Ctrl+V (paste) keystrokes
            // - we need at least 1 paste, so it starts from 1
            // - and since our vec is 1-indexed (i=no of keystrokes) and for a single paste we need 2 preceding
            //   keystrokes (select + copy), so we have (i - j - 2) >= 1
            for (int j = 1; (i - j - 2) >= 1; j++) {
                // whatever was on screen will be multiplied by 'j + 1' times (1 original + j paste keystrokes)
                int crrAs = memoVec[i - j - 2] * (j + 1);

                if (debug) {
                    printf("\n");
                    printf("trying j=%d\n", j);
                    printf("memoVec[i=%d - j=%d - 2] = memoVec[%d] = %d\n", i, j, (i - j - 2), memoVec[i - j - 2]);
                    printf("crrAs = memoVec[%d]=%d * j=%d = %d\n", (i - j - 2), memoVec[i - j - 2], j, crrAs);
                    printf("maxAs = max(maxAs=%d, crrAs=%d) = %d\n", maxAs, crrAs, max(maxAs, crrAs));
                    printf("\n");
                }

                maxAs = max(maxAs, crrAs);
            }

            memoVec[i] = maxAs;

            if (debug) {
                printf("After i=%d, memoVec:-\n", i);
                showMemoVec(memoVec);
                printf("\n-----------\n");
            }
        }
    }

public:
    friend class SolutionTest;

    int maxA(int n) {
        if (n <= MAX_N_TILL_NO_GAIN) {
            if (debug) {
                printf("Short circuiting to return n=%d\n", n);
            }
            return n;
        }

        vector <int> memoVec = createMemoVec(n);
        if (debug) {
            printf("After creation, memoVec:-\n");
            showMemoVec(memoVec);
        }

        fillMemoVec(memoVec);

        return memoVec[n];
    }
};

class SolutionTest {
    public:
    void testMaxA() {
        Solution soln = Solution();
        int nIn;
        int outExpected, outComputed;

        nIn = 0;
        outExpected = 0;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 1;
        outExpected = 1;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 2;
        outExpected = 2;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 3;
        outExpected = 3;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 4;
        outExpected = 4;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 5;
        outExpected = 5;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 6;
        outExpected = 6;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        // soln.enableDebug();
        nIn = 7;
        outExpected = 9;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);
        // soln.disableDebug();

        nIn = 8;
        outExpected = 12;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 9;
        outExpected = 16;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 10;
        outExpected = 20;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 11;
        outExpected = 27;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);

        nIn = 12;
        outExpected = 36;
        outComputed = soln.maxA(nIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMaxA();

    return 0;
}
