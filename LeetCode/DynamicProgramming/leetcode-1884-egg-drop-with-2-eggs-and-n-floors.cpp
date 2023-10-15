// LeetCode-1884: https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/
// TusharRoy: https://www.youtube.com/watch?v=3hcaVyX00_4

#include <vector>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<vector<int>> createMatrix(int numFloors, int numEggs) {
        vector<vector<int> > mat(numEggs + 1);

        for (int i = 0; i <= numEggs; i++) {
            vector<int> matRow(numFloors + 1, INT_MAX);
            matRow[0] = 0;

            mat[i] = matRow;
        }

        return mat;
    }

    void fillMatrix(vector<vector<int> >& mat) {
        int numEggs = ((int) mat.size()) - 1;
        int numFloors = ((int) mat[0].size()) - 1;

        // fill first row (no of attempts required with one egg = no of floors)
        for (int j = 1; j <= numFloors; j++) {
            mat[1][j] = j;
        }

        // fill subsequent rows
        for (int i = 2; i <= numEggs; i++) {
            for (int j = 1; j <= numFloors; j++) {
                if (i > j) {
                    // if no of eggs > no of floors, then there's no real gain
                    mat[i][j] = mat[i - 1][j];
                }

                int minAttempts = mat[i][j];
                for (int k = 1; k <= j; k++) {
                    int crrAttempts = 1 + max(mat[i - 1][k - 1], mat[i][j - k]);
                    minAttempts = min(minAttempts, crrAttempts);
                }

                mat[i][j] = minAttempts;
            }
        }
    }

public:
    friend class SolutionTest;

    int twoEggDrop(int n) {
        vector<vector<int> > mat = createMatrix(n, 2);
        fillMatrix(mat);

        return mat[2][n];
    }
};

class SolutionTest {
public:
    void testTwoEggDrop() {
        Solution soln = Solution();
        int numFloors;
        int outExpected, outComputed;

        numFloors = 0;
        outExpected = 0;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 1;
        outExpected = 1;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 2;
        outExpected = 2;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 3;
        outExpected = 2;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 4;
        outExpected = 3;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 5;
        outExpected = 3;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 6;
        outExpected = 3;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);

        numFloors = 100;
        outExpected = 14;
        outComputed = soln.twoEggDrop(numFloors);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testTwoEggDrop();

    return 0;
}
