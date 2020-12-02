// LeetCode-1641: https://leetcode.com/problems/count-sorted-vowel-strings/submissions/

/**
 * @file leetcode-1641-count-sorted-vowel-strings.cpp
 * @author Shubham Gupta (y2k-shubham)
 * @brief the idea is that we create and fill up a table having
 *        - 5 rows -> 1 per vowel
 *        - n columns -> length of string
 *        1. each cell of the table stores no of required (lexicographical) strings
 *        ending at the character corresponding to that ith row.
 *        2. by that logic, no of required strings of any given length n will be
 *        the summation of cells of nth column of the table (all possible strings
 *        that end at all possible vowels)
 *        3. filling up the table
 *        (a) observation: the no of lexicographic strings of any given length j
 *        ending at a vowel, say 'o' will be equal to sum of all strings ending
 *        at vowels before 'o' plus 'o' itelf, but having 1 less length => j - 1
 *        (b) why? because in each one of those strings of length j - 1, we can
 *        append 'o' to form a lexicographic string of length j. furthermore that
 *        set is exhaustive => there are no other strings of length j - 1 that can
 *        be appended with 'o' to still give a lexicographic string of length j
 *        ending at 'o'
 *        (c) so essentially value we fill up at any cell [i][j] is
 *        sum([k][j-1]) for k = 'a' to v, where v is vowel corresponding to row i
 *        (d) writing down that operation on paper, we'll quickly realize that above
 *        quantity simplifies to [i][j - 1] + [i - 1][j]
 *        because [i - 1][j] already included sums of all nums until previous row
 * @date 2020-12-02
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int countVowelStrings(int n) {
    int numVowels = 5;

    vector<vector<int> > mat(numVowels);
    for (int i = 0; i < numVowels; i++) {
        if (i == 0) {
            vector<int> matRow(n, 1);
            mat[i] = matRow;
        } else {
            vector<int> matRow(n, 0);
            matRow[0] = 1;
            mat[i] = matRow;
        }
    }

    for (int i = 1; i < numVowels; i++) {
        for (int j = 1; j < n; j++) {
            mat[i][j] = mat[i - 1][j] + mat[i][j - 1];
        }
    }

    int sum = 0;
    for (int i = 0; i < numVowels; i++) {
        sum += mat[i][n - 1];
    }

    return sum;
}
