// https://www.geeksforgeeks.org/longest-palindrome-substring-set-1/
// https://practice.geeksforgeeks.org/problems/longest-palindrome-in-a-string/0
// https://leetcode.com/problems/longest-palindromic-substring/#
// https://www.interviewbit.com/problems/longest-palindromic-substring/

/*
1
aaaabbaa

1
forgeeksskeegfor
*/

#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 1001

void prepareMat(bool mat[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        mat[i][i] = true;
        mat[i + 1][i] = true;
    }
}

void showMat(bool mat[MAX][MAX], string str) {
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
                    printf("T\t");
                } else {
                    printf("F\t");
                }
            }
        }
        printf("\n");
    }
}

void fillMat(bool mat[MAX][MAX], string str, int* rAnsBeg, int* cAnsBeg) {
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
              mat[r][c] = mat[r + 1][c - 1];
              if (mat[r][c] == true) {
                  int palinLength = c - r + 1;
                  if (palinLength > maxPalinLength) {
                      maxPalinLength = palinLength;
                      *rAnsBeg = r;
                      *cAnsBeg = c;
                  }
              }
          } else {
              mat[r][c] = false;
          }
        }

        // printf("\nafter cLo=%d\n", cLo);
        // showMat(mat, str);
        // printf("\n");
    }
}

int main() {
    int T;
    bool mat[MAX][MAX];
    
    cin >> T;
    while (T-- > 0) {
        string str;
        
        cin >> str;
        prepareMat(mat, str.size());
        
        int r, c;
        fillMat(mat, str, &r, &c);
        
        string lcs = str.substr(r, (c - r + 1));
        cout << lcs << endl;
    }
    
    return 0;
}