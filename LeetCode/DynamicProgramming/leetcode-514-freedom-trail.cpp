// LeetCode-514: https://leetcode.com/problems/freedom-trail/

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showMemoMat(string ring, string key, vector<vector<int> >& memoMat) {
        int rows = key.size();
        int cols = ring.size();

        printf("\t\t");
        for (int j = 0; j <= cols; j++) {
            if (j == 0) {
                printf("\t");
            } else {
                printf("%c\t", ring.at(j - 1));
            }
        }
        cout << endl;

        printf("\t\t");
        for (int j = 0; j <= cols; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i <= rows; i++) {
            // if (i == 0) {
            //     printf("\t[0]\n");
            //     continue;
            // }

            if (i == 0) {
                printf("\t[0]\t");
            } else {
                printf("%c\t[%d]\t", key.at(i - 1), i);
            }

            for (int j = 0; j <= cols; j++) {
                if (memoMat[i][j] == INT_MAX) {
                    printf("-\t");
                } else {
                    printf("%d\t", memoMat[i][j]);
                }
            }
            cout << endl;
        }
    }

    void showMap(unordered_map<int, int>& mMap, string name) {
        printf("%s map is:-\n", name.c_str());

        for (unordered_map<int, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            printf("%d -> %d\n", it->first, it->second);
        }
    }

    vector<vector<int> > createMemoMat(string ring, string key) {
        int rows = key.size();
        int cols = ring.size();

        vector<vector<int> > memoMat(rows + 1);
        for (int i = 0; i <= rows; i++) {
            vector<int> memoMatRow(cols + 1, INT_MAX);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMemoMat(string ring, string key, vector<vector<int> >& memoMat) {
        int rows = key.size();
        int cols = ring.size();

        unordered_map<int, int> prevRowWays;

        // fill first row
        char keyFirstChar = key.at(0);
        for (int j = 1; j <= cols; j++) {
            if (ring.at(j - 1) == keyFirstChar) {
                int normalRotationMoves = j - 1;                    // reaching directly
                int revRotationMoves = cols - normalRotationMoves;  // reaching indirectly: leveraging the fact that it is a circular dial

                int numRotationMoves = min(normalRotationMoves, revRotationMoves);
                if (debug) {
                    printf("normalRotationMoves=%d, revRotationMoves=%d, numRotationMoves=%d\n", normalRotationMoves, revRotationMoves, numRotationMoves);
                }

                int numTotalMoves = numRotationMoves + 1;

                memoMat[1][j] = numTotalMoves;
                prevRowWays[j] = numTotalMoves;
            }
        }

        if (debug) {
            printf("after initial row fill\n");
            showMemoMat(ring, key, memoMat);
            cout << endl;
            showMap(prevRowWays, "crrRowWays");
        }

        // fill subsequent rows
        for (int i = 2; i <= rows; i++) {
            unordered_map<int, int> crrRowWays;

            char crrKeyChar = key.at(i - 1);
            for (int j = 1; j <= cols; j++) {
                if (ring.at(j - 1) == crrKeyChar) {
                    int minTotalMoves = INT_MAX;
                    for (unordered_map<int, int>::iterator it = prevRowWays.begin(); it != prevRowWays.end(); it++) {
                        int normalRotationMoves = abs(j - it->first);       // reaching directly
                        int revRotationMoves = cols - normalRotationMoves;  // reaching indirectly: leveraging the fact that it is a circular dial

                        int numRotationMoves = min(normalRotationMoves, revRotationMoves);
                        int numTotalMoves = numRotationMoves + it->second + 1;

                        if (debug) {
                            printf("normalRotationMoves=%d, revRotationMoves=%d, numRotationMoves=%d\n", normalRotationMoves, revRotationMoves, numRotationMoves);
                        }

                        minTotalMoves = min(minTotalMoves, numTotalMoves);
                    }

                    memoMat[i][j] = minTotalMoves;
                    crrRowWays[j] = minTotalMoves;
                }
            }

            if (debug) {
                printf("\n-----------\n\n");
                printf("after filling i=%d\n", i);
                cout << endl;
                showMemoMat(ring, key, memoMat);
                cout << endl;
                showMap(crrRowWays, "crrRowWays");
            }

            prevRowWays = crrRowWays;
        }
    }

    int findMinSteps(string ring, string key, vector<vector<int> >& memoMat) {
        int rows = key.size();
        int cols = ring.size();

        int minSteps = INT_MAX;
        for (int j = 1; j <= cols; j++) {
            minSteps = min(minSteps, memoMat[rows][j]);
        }

        return minSteps;
    }

   public:
    friend class SolutionTest;

    int findRotateSteps(string ring, string key) {
        int rows = key.size();
        int cols = ring.size();

        vector<vector<int> > memoMat = createMemoMat(ring, key);
        fillMemoMat(ring, key, memoMat);

        return findMinSteps(ring, key, memoMat);
    }
};

class SolutionTest {
   public:
    void testFindRotateSteps() {
        Solution soln = Solution();
        string inRing;
        string inKey;
        int outStepsExpected;
        int outStepsComputed;

        // soln.debug = true;
        inRing = "godding";
        inKey = "gd";
        outStepsExpected = 4;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        inRing = "godding";
        inKey = "godding";
        outStepsExpected = 13;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);

        inRing = "godding";
        inKey = "god";
        outStepsExpected = 5;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);

        inRing = "godding";
        inKey = "ding";
        outStepsExpected = 10;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);

        inRing = "godding";
        inKey = "dig";
        outStepsExpected = 9;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);

        inRing = "godding";
        inKey = "odin";
        outStepsExpected = 9;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);

        // soln.debug = true;
        inRing = "godding";
        inKey = "gog";
        outStepsExpected = 5;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        // soln.debug = true;
        inRing = "abcde";
        inKey = "ade";
        outStepsExpected = 6;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        // soln.debug = true;
        inRing = "abcde";
        inKey = "a";
        outStepsExpected = 1;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        // soln.debug = true;
        inRing = "abcde";
        inKey = "d";
        outStepsExpected = 3;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        // soln.debug = true;
        inRing = "abcde";
        inKey = "e";
        outStepsExpected = 2;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;

        // soln.debug = true;
        inRing = "abcde";
        inKey = "aed";
        outStepsExpected = 5;
        outStepsComputed = soln.findRotateSteps(inRing, inKey);
        assert(outStepsExpected == outStepsComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testFindRotateSteps();
    return 0;
}
