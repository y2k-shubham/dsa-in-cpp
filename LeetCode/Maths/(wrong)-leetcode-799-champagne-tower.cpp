// LeetCode-799: https://leetcode.com/problems/champagne-tower/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cassert>
#include <numeric>

using namespace std;

class Solution {
private:
    bool debug = false;

    int calcLastFilledRowNum(int qty) {
        if (qty <= 1) {
            return qty;
        }

        /**
         * [calculating index of last (fully or partially) filled row from top]
         *
         * volume of wine filled in each row starting from topmost row follows elementary arithmetic progression
         * 1 (1st row) units,
         * 2 (2nd row) units,
         * 3 units (3rd row)
         * ..
         * and so on
         *
         * so total volume of wine filled up till nth row
         * (assuming nth row is the last fully / partially filled row)
         *
         * so then
         *    Σn <= q; where q = qty
         * => {n(n+1)} / 2 <= q
         * => n = ⌊{√(1 + 8q) - 1} / 2⌋
         */
        return (int) ceil((sqrt(1 + 8 * qty) - 1) / 2.0);
    }

    int calcCompletelyFilledQty(int rows) {
        // simple Σn = n(n+1) / 2
        return (rows * (rows + 1)) / 2;
    }

public:
    friend class SolutionTest;

    double champagneTower(int poured, int query_row, int query_glass) {
        int lastFilledRowNum = calcLastFilledRowNum(poured);
        int expectedCompletelyFilledQty = calcCompletelyFilledQty(lastFilledRowNum);
        int actualCompletelyFilledQty = (expectedCompletelyFilledQty == poured) ? expectedCompletelyFilledQty : calcCompletelyFilledQty(lastFilledRowNum - 1);

        int partiallyFilledQty = poured - actualCompletelyFilledQty;
        double partiallyFilledQtyPerGlass = (partiallyFilledQty * 1.0) / lastFilledRowNum;

        // making adjustment for input query row which is 0-indexed
        query_row++;
        if (debug) {
            printf("poured=%d, lastFilledRowNum=%d, expecetedCompletelyFilledQty=%d, actualCompletelyFilledQty=%d\n", poured, lastFilledRowNum, expectedCompletelyFilledQty, actualCompletelyFilledQty);
            printf("actualCompletelyFilledQty=%d, partiallyFilledQty=%d, partiallyFilledQtyPerGlass=%3.2lf\n", actualCompletelyFilledQty, partiallyFilledQty, partiallyFilledQtyPerGlass);
            printf("query_row (after increment)=%d, query_glass=%d\n", query_row, query_glass);
        }

        if (query_row < lastFilledRowNum) {
            return 1.0;
        } else if (query_row == lastFilledRowNum) {
            return partiallyFilledQtyPerGlass;
        } else {
            return 0.0;
        }
    }
};

class SolutionTest {
private:

    bool areEqual(double d1, double d2) {
        double absDelta = abs(d1 - d2);

        // double epsilon: https://stackoverflow.com/a/1566283/3679900
        double epsilon = 0.000001; // numeric_limits<double>::epsilon();

        return absDelta <= epsilon;
    }

public:
    void testCalcLastFilledRowNum() {
        Solution soln = Solution();
        int qtyIn;
        int rowNumOutExpected, rowNumOutComputed;

        qtyIn = 0;
        rowNumOutExpected = 0;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 1;
        rowNumOutExpected = 1;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 2;
        rowNumOutExpected = 2;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 3;
        rowNumOutExpected = 2;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 4;
        rowNumOutExpected = 3;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 5;
        rowNumOutExpected = 3;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 6;
        rowNumOutExpected = 3;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 7;
        rowNumOutExpected = 4;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 8;
        rowNumOutExpected = 4;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 9;
        rowNumOutExpected = 4;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 10;
        rowNumOutExpected = 4;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);

        qtyIn = 11;
        rowNumOutExpected = 5;
        rowNumOutComputed = soln.calcLastFilledRowNum(qtyIn);
        assert(rowNumOutExpected == rowNumOutComputed);
    }

    void testCalcCompletelyFilledQty() {
        Solution soln = Solution();
        int rowsIn;
        int qtyOutExpected, qtyOutComputed;

        rowsIn = 0;
        qtyOutExpected = 0;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);

        rowsIn = 1;
        qtyOutExpected = 1;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);

        rowsIn = 2;
        qtyOutExpected = 3;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);

        rowsIn = 3;
        qtyOutExpected = 6;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);

        rowsIn = 4;
        qtyOutExpected = 10;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);

        rowsIn = 5;
        qtyOutExpected = 15;
        qtyOutComputed = soln.calcCompletelyFilledQty(rowsIn);
        assert(qtyOutExpected == qtyOutComputed);
    }

    void testChampagneTower() {
        Solution soln = Solution();
        int pouredIn;
        int query_rowIn;
        int query_glassIn;
        double outExpected, outComputed;

        pouredIn = 0;
        query_rowIn = 0;
        query_glassIn = 0;
        outExpected = 0.0;
        outComputed = soln.champagneTower(pouredIn, query_rowIn, query_glassIn);
        assert(areEqual(outExpected, outComputed));

        pouredIn = 1;
        query_rowIn = 1;
        query_glassIn = 1;
        outExpected = 0.0;
        outComputed = soln.champagneTower(pouredIn, query_rowIn, query_glassIn);
        assert(areEqual(outExpected, outComputed));

//        soln.debug = true;
        pouredIn = 2;
        query_rowIn = 1;
        query_glassIn = 1;
        outExpected = 0.5;
        outComputed = soln.champagneTower(pouredIn, query_rowIn, query_glassIn);
//        printf("outExpected = %3.2lf, outComputed = %3.2lf\n", outExpected, outComputed);
        assert(areEqual(outExpected, outComputed));
//        soln.debug = false;

        pouredIn = 100000009;
        query_rowIn = 33;
        query_glassIn = 17;
        outExpected = 1.0;
        outComputed = soln.champagneTower(pouredIn, query_rowIn, query_glassIn);
        assert(areEqual(outExpected, outComputed));
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcLastFilledRowNum();
    solnTest.testCalcCompletelyFilledQty();
    solnTest.testChampagneTower();

    return 0;
}
