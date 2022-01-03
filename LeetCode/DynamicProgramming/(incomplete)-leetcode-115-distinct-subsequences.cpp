// LeetCode-115: https://leetcode.com/problems/distinct-subsequences/
// incomplete: some test cases failing (overflowing even long long -> likely problem with logic)

/**
 * Input
 * "rabbbit"
 * "rabbit"
 * Output
 * 3
 *
 * Input
 * "rabbbit"
 * "rabi"
 * Output
 * 3
 *
 * Input
 * "rabbbit"
 * "rbt"
 * Output
 * 3
 *
 * Input
 * "rabbbit"
 * "r"
 * Output
 * 1
 *
 * Input
 * "rabbbit"
 * "a"
 * Output
 * 1
 *
 * Input
 * "rabbbit"
 * "b"
 * Output
 * 3
 *
 * Input
 * "rabbbit"
 * "i"
 * Output
 * 1
 *
 * Input
 * "rabbbit"
 * "t"
 * Output
 * 1
 *
 * Input
 * "rabbbit"
 * "z"
 * Output
 * 0
 *
 * Input
 * "babgbag"
 * "bag"
 * Output
 * 5
 *
 * Input
 * "babgbag"
 * "gab"
 * Output
 * 0
 *
 * Input
 * "babgbag"
 * "ab"
 * Output
 * 2
 *
 * Input
 * "babgbag"
 * "bga"
 * Output
 * 2
 *
 * Input
 * "babgbag"
 * "a"
 * Output
 * 2
 *
 * Input
 * "babgbag"
 * "b"
 * Output
 * 3
 *
 * Input
 * "babgbag"
 * "g"
 * Output
 * 2
 *
 * Input
 * "babgbag"
 * "m"
 * Output
 * 0
 *
 * (this testcase runs into overflow with int)
 * Input
 * "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo"
 * "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys"
 * Output
 * 
 * (this testcase runs into overflow even with long long)
 * Input
 * "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
 * "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
 * Output
 * 
 */

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // method 1: table
    // space complexity: O(m x n); m=s.length & n=t.length
    // would go OOM for s & t of length 1000 chars
    vector<vector<long long> > createMemoMat(string s, string t) {
        int rows = t.size();
        int cols = s.size();

        vector<vector<long long> > memoMat(rows + 1);
        for (int i = 0; i <= rows; i++) {
            vector<long long> memoMatRow(cols + 1, 0);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMemoMat(string s, string t, vector<vector<long long> >& memoMat) {
        int rows = t.size();
        int cols = s.size();

        for (int i = 1; i <= rows; i++) {
            char tChar = t.at(i - 1);

            for (int j = i; j <= cols; j++) {
                char sChar = s.at(j - 1);

                if (tChar == sChar) {
                    if (i == 1) {
                        // in first row, we just keep count of every sChar that matches with (first) tChar
                        memoMat[i][j] = memoMat[i][j - 1] + 1;
                    } else {
                        memoMat[i][j] = memoMat[i][j - 1] + memoMat[i - 1][j - 1];
                    }
                } else {
                    memoMat[i][j] = memoMat[i][j - 1];
                }
            }
        }
    }

    int numDistinctMat(string s, string t) {
        int rows = t.size();
        int cols = s.size();

        vector<vector<long long> > memoMat = createMemoMat(s, t);
        fillMemoMat(s, t, memoMat);

        return (int)memoMat[rows][cols];
    }

    // method 2: vector
    // space complexity: O(m); m=s.length & n=t.length
    // will work for s & t of length 1000 chars
    void copyVals(vector<long long>& srcVec, vector<long long>& dstVec) {
        for (int i = 0; i < srcVec.size(); i++) {
            dstVec[i] = srcVec[i];
        }
    }

    void zeroOutVec(vector<long long>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            vec[i] = 0;
        }
    }

    int numDistinctVec(string s, string t) {
        int rows = t.size();
        int cols = s.size();

        vector<long long> prevRow(cols + 1, 0);
        vector<long long> crrRow(cols + 1, 0);

        for (int i = 1; i <= rows; i++) {
            char tChar = t.at(i - 1);

            for (int j = i; j <= cols; j++) {
                char sChar = s.at(j - 1);

                if (tChar == sChar) {
                    if (i == 1) {
                        // in first row, we just keep count of every sChar that matches with (first) tChar
                        crrRow[j] = crrRow[j - 1] + 1;
                    } else {
                        crrRow[j] = crrRow[j - 1] + prevRow[j - 1];
                    }
                } else {
                    crrRow[j] = crrRow[j - 1];
                }
            }

            // this didnt work
            // copy(crrRow.begin(), crrRow.end(), back_inserter(prevRow));
            // fill(crrRow.begin(), crrRow.end(), 0);

            copyVals(crrRow, prevRow);
            zeroOutVec(crrRow);
        }

        return (int)prevRow[cols];
    }

   public:
    int numDistinct(string s, string t) {
        // return numDistinctMat(s, t);
        return numDistinctVec(s, t);
    }
};

int main() {
  return 0;
}
