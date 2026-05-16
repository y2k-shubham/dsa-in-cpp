// LeetCode-276: https://leetcode.com/problems/paint-fence/
// YouTube 'Code Scribbler': https://www.youtube.com/watch?v=LnumO0QcmV0

#include <vector>

using namespace std;

class MemoEntry {
public:
    int sameColor;
    int diffColor;

    MemoEntry(int sameColor, int diffColor): sameColor(sameColor), diffColor(diffColor) {}
};

class Solution {
private:
    vector<MemoEntry> createMemoTable(int n, int k) {
        vector<MemoEntry> memoMat(n, MemoEntry(-1, -1));
        memoMat[1].sameColor = k;
        memoMat[1].diffColor = k * (k - 1);
        return memoMat;
    }

    void fillMemoTable(vector<MemoEntry>& memoTable, int n, int k) {
        for (int j = 2; j < n; j++) {
            memoTable[j].sameColor = memoTable[j - 1].diffColor;
            memoTable[j].diffColor = (memoTable[j - 1].sameColor + memoTable[j - 1].diffColor) * (k - 1);
        }
    }

public:
    int numWays(int n, int k) {
        if (n == 0 || k == 0) {
            return 0;
        } else if (n == 1) {
            return k;
        } else if (n == 2) {
            return k * k;
        }

        vector<MemoEntry> memoTable = createMemoTable(n, k);
        fillMemoTable(memoTable, n, k);

        return (memoTable[n - 1].sameColor
                + memoTable[n - 1].diffColor);
    }
};
