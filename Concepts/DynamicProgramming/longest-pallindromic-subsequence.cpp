// https://www.geeksforgeeks.org/print-longest-palindromic-subsequence/?ref=rp
// https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/
// https://leetcode.com/problems/longest-palindromic-subsequence/

/*
geeksforgeeks
eekee, eesee etc

BBABCBCAB
BABCBAB
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX 100
#define maxVal(a, b) ((a > b) ? a : b)

void input(string&, const char *);
void findLCS(string, string, int [MAX][MAX]);
string getLCSRec(string, string, int [MAX][MAX], int, int);
string getLCSIter(string, string, int [MAX][MAX]);
void showMat(int [MAX][MAX], string, string, int, int);

int main() {
	string str;
	int lcs[MAX][MAX];

	input(str, "the");

  string strRev = str;
  reverse(strRev.begin(), strRev.end());
  // cout << "after reversing" << endl << "str = " << str << endl << "strRev = " << strRev << endl;

	findLCS(str, strRev, lcs);
	cout << "The lps is:\t" << getLCSRec(str, strRev, lcs, str.length(), strRev.length()) << endl;
	cout << "The lps is:\t" << getLCSIter(str, strRev, lcs) << endl;

	return 0;
}

void input(string& str, const char * which) {
	printf("Enter %s string:\t", which);
	cin >> str;
}

void findLCS(string str1, string str2, int lcs[MAX][MAX]) {
	int len1, len2;
	int i, j;

	memset(lcs, 0, MAX*MAX);
  // showMat(lcs, str1, str2, -1, -1);

	len1 = str1.length();
	len2 = str2.length();

	for (int i = 1; i <= len1; i++) {
		for (int j =1; j <= len2; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				lcs[i][j] = 1 + lcs[i - 1][j - 1];
			} else {
				lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
			}
      // showMat(lcs, str1, str2, i, j);
		}
	}

	printf("\nLength of lcs is:\t%d\n", lcs[len1][len2]);
}

string getLCSRec(string str1, string str2, int lcs[MAX][MAX], int row, int col) {
	if (row <= 0 || col <= 0) {
		return "";
	} else if (str1[row - 1] == str2[col - 1]) {
		return getLCSRec(str1, str2, lcs, row - 1, col - 1) + str1[row - 1];
	} else if (lcs[row - 1][col] > lcs[row][col - 1]) {
		return getLCSRec(str1, str2, lcs, row - 1, col);
	} else {
		return getLCSRec(str1, str2, lcs, row, col - 1);
	}
}

string getLCSIter(string str1, string str2, int lcs[MAX][MAX]) {
	int i, j;
	string lcsStr;

	i = str1.length();
	j = str2.length();

	while (i > 0 && j > 0) {
    // showMat(lcs, str1, str2, i, j);
		if (str1[i - 1] == str2[j - 1]) {
      // printf("included str1[i=%d] = %c\n", i, str1[i]);
			lcsStr = str1[i - 1] + lcsStr;
			i--;
			j--;
		} else if (lcs[i - 1][j] > lcs[i][j - 1]) {
			i--;
		} else {
			j--;
		}
    // cout << endl;
	}

	return lcsStr;
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
}
