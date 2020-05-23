// https://www.geeksforgeeks.org/longest-palindromic-substring-set-2/
// https://practice.geeksforgeeks.org/problems/longest-palindrome-in-a-string/0
// https://www.hackerearth.com/practice/algorithms/string-algorithm/manachars-algorithm/practice-problems/algorithm/longest-palindromic-string/
// https://www.hackerrank.com/contests/security-challenge/challenges/largest-palindromic-substring/

// Time: O(n^2), Extra-Space: O(1) [obviously O(n) space is still needed for storing the generated substring(s) themselves (one-at-a-time)]

/*
aaaabbaa
------
aabbaa

======

forgeeksskeegfor
------
geeksskeeg

======

czcaba
------
czc

*/

#include <cstdio>
#include <iostream>

using namespace std;

void findOddLenPalSubstr(string, int &, int &);
void findEvenLenPalSubstr(string, int &, int &);
void showStr(string, int, int, bool);

int main() {
  string str;
  cin >> str;

  int palSubstrLen = 1, palSubstrStartInd = 0;
  findOddLenPalSubstr(str, palSubstrLen, palSubstrStartInd);
  findEvenLenPalSubstr(str, palSubstrLen, palSubstrStartInd);

  // cout << palSubstrLen << endl;
  cout << str.substr(palSubstrStartInd, palSubstrLen) << endl;
  // cout << "Longest palindromic substring is " << str.substr(palSubstrStartInd, palSubstrLen) << endl;
  // printf("Longest palindromic substring spans between str[%d]=%c and str[%d]=%c\n", palSubstrStartInd, str[palSubstrStartInd], (palSubstrStartInd + palSubstrLen - 1), str[palSubstrStartInd + palSubstrLen - 1]);

  return 0;
}

void findOddLenPalSubstr(string str, int &palSubstrLen, int &palSubstrStartInd) {
  for (int i = 1; i < str.size() - 2; i++) {
    for (int j = 1; (i - j >= 0) && (i + j < str.size()); j++) {
      // showStr(str, i, j, false);
      if (str.at(i - j) == str.at(i + j)) {
        int len = 2 * j + 1;
        int startInd = i - j;
        if (len > palSubstrLen) {
          palSubstrLen = len;
          palSubstrStartInd = startInd;
          // printf("found longest palindrome so far with length %d\n", len);
        } else {
          // printf("found         palindrome        with length %d\n", len);
        }
      } else {
        // printf("found no      palindrome; breaking\n");
        break;
      }
    }
  }
}

void findEvenLenPalSubstr(string str, int &palSubstrLen, int &palSubstrStartInd) {
  for (int i = 0; i < str.size() - 1; i++) {
    if (str.at(i) == str.at(i + 1)) {
      int len = 2;
      int startInd = i;
      for (int j = 1; (i - j >= 0) && (i + 1 + j < str.size()); j++) {
        // showStr(str, i, j, true);
        if (str.at(i - j) == str.at(i + 1 + j)) {
          len = 2 * j + 2;
          startInd = i - j;
          if (len > palSubstrLen) {
            palSubstrLen = len;
            palSubstrStartInd = startInd;
            // printf("found longest palindrome so far with length %d\n", len);
          } else {
            // printf("found         palindrome        with length %d\n", len);
          }
        } else {
          // printf("found no      palindrome; breaking\n");
          break;
        }
      }
    }
  }
}

void showStr(string str, int crrI, int crrJ, bool even) {
  cout << endl;

  printf("Ind:\t");
  for (int i = 0; i < str.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  printf("Char:\t");
  for (int i = 0; i < str.size(); i++) {
    cout << str.at(i) << "\t";
  }
  cout << endl;

  printf("\t");
  for (int k = 0; k < str.size(); k++) {
    if (k == (crrI - crrJ)) {
      printf("-(j=%d)\t", crrJ);
    } else {
      if (even) {
        if (k == crrI) {
          printf("(i=%d)\t(i+1=%d)\t", crrI, crrI + 1);
        } else if (k == crrI + crrJ + 1) {
          printf("(j=%d)\t", crrJ);
        } else {
          printf("\t");
        }
      } else {
        if (k == crrI) {
          printf("(i=%d)\t", crrI);
        } else if (k == crrI + crrJ) {
          printf("(j=%d)\t", crrJ);
        } else {
          printf("\t");
        }
      }
    }
  }
  cout << endl;
}
