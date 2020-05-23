// https://www.geeksforgeeks.org/print-longest-palindromic-subsequence/?ref=rp
// https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/
// https://leetcode.com/problems/longest-palindromic-subsequence/

/*
geeksforgeeks
eekee, eesee etc

BBABCBCAB
BABCBAB
*/

#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 1001

void fillMat(int [MAX][MAX], string, int *, int *);
void showMat(int [MAX][MAX], string);
void prepareMat(int [MAX][MAX], int);

int main() {
  string str;
  int mat[MAX][MAX];

  cin >> str;
  prepareMat(mat, str.size());

  int iBegin = 0, iEnd = 0;
  fillMat(mat, str, &iBegin, &iEnd);
  
  return 0;
}

void fillMat(int mat[MAX][MAX], string str, int* iBegin, int* iEnd) {
    int rLoFix = 0;
    int rHiInit = str.size() - 2;
    int cLoInit = 1;
    int cHiFix = str.size() - 1;
    int maxPalinLength = 1;
    
    // showMat(mat, str);
    for (int rHi = rHiInit, cLo = cLoInit; cLo <= cHiFix; rHi--, cLo++) {
        for (int r = rLoFix, c = cLo; c <= cHiFix; r++, c++) {
          // printf("comparing str.at(r=%d) = %c, str.at(l=%d) = %c\n", r, str.at(r), c, str.at(c));
          if (str.at(r) == str.at(c)) {
            mat[r][c] = mat[r + 1][c - 1] + 2;
            int palinLength = c - r + 1;
            if (palinLength > maxPalinLength) {
                maxPalinLength = palinLength;
                *iBegin = r;
                *iEnd = c;
            }
          } else {
              mat[r][c] = max(mat[r + 1][c], mat[r][c - 1]);
          }
        }

        printf("\nafter cLo=%d\n", cLo);
        showMat(mat, str);
        printf("\n");
    }
}

void prepareMat(int mat[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        mat[i][i] = 1;
        mat[i + 1][i] = 0;
    }
}

void showMat(int mat[MAX][MAX], string str) {
    int n = str.size();
    
    printf("\t");
    for (int i = 0; i < n; i++) {
        printf("[%d]=%c\t", i, str.at(i));
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("[%d]=%c\t", i, str.at(i));
        for (int j = 0; j < n; j++) {
            if (j < i) {
                printf("\t");
            } else {
                if (mat[i][j]) {
                    printf("%d\t", mat[i][j]);
                } else {
                    printf("%d\t", mat[i][j]);
                }
            }
        }
        printf("\n");
    }
}
