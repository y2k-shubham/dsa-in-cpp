// https://www.geeksforgeeks.org/longest-common-substring-dp-29/

/*
GeeksforGeeks GeeksQuiz
abcdxyz xyzabcd
zxabcdezy yzabcdezx
*/

/*

Input : X = “GeeksforGeeks”, y = “GeeksQuiz”
Output : 5
The longest common substring is “Geeks” and is of length 5.

Input : X = “abcdxyz”, y = “xyzabcd”
Output : 4
The longest common substring is “abcd” and is of length 4.

Input : X = “zxabcdezy”, y = “yzabcdezx”
Output : 6
The longest common substring is “abcdez” and is of length 6.
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

#define MAX 100
using namespace std;

void initMat(int [MAX][MAX]);
void fillMat(string, string, int[MAX][MAX], int &, int &);
void showMat(int[MAX][MAX], string, string, int, int);

int main() {
  string str1, str2;
  int mat[MAX][MAX];

  cin >> str1 >> str2;
  cout << "Strings are " << str1 << " and " << str2 << endl;

  initMat(mat);
  showMat(mat, str1, str2, -1, -1);

  int iEnd1 = 0, len = 0;
  fillMat(str1, str2, mat, iEnd1, len);

  string lcs = str1.substr(iEnd1 - len + 1, len);
  cout << endl << "Longest Common Substring is " << lcs << endl;
}

void initMat(int mat[MAX][MAX]) {
  memset(mat, -1, MAX * MAX * sizeof(int));

  // 1st row zero
  for (int j = 0; j < MAX; j++) {
    mat[0][j] = 0;
  }  

  // 1st column zero
  for (int i = 0; i < MAX; i++) {
    mat[i][0] = 0;
  }
}

void fillMat(string str1, string str2, int mat[MAX][MAX], int &iEnd1, int &len) {
  for (int i = 1; i <= str1.size(); i++) {
    for (int j = 1; j <= str2.size(); j++) {
      if (str1.at(i - 1) == str2.at(j - 1)) {
        mat[i][j] = mat[i - 1][j - 1] + 1;
        if (mat[i][j] > len) {
          len = mat[i][j];
          iEnd1 = i - 1;
        }
      } else {
        mat[i][j] = 0;
      }
    }
    showMat(mat, str1, str2, -1, -1);
  }
}

void showMat(int mat[MAX][MAX], string str1, string str2, int crrI, int crrJ) {
    int rows = str1.size();
    int cols = str2.size();
    
    printf("\t");
    for (int j = 0; j <= cols; j++) {
      if (j >= 1) {
        printf("[%d]=%c\t", j, str2.at(j - 1));
      } else {
        printf("\t");
      }
    }
    printf("\n");
    
    for (int i = 0; i <= rows; i++) {
      if (i >= 1) {
        printf("[%d]=%c\t", i, str1.at(i - 1));
      } else {
        printf("\t");
      }
        
      for (int j = 0; j <= cols; j++) {
          if (mat[i][j] >= 0) {
            if (i == crrI && j == crrJ) {
              printf("(%d)\t", mat[i][j]);
            } else {
              printf("%d\t", mat[i][j]);
            }
          } else {
            printf("\t");
          }
      }
      printf("\n");
    }
    printf("\n");
}
