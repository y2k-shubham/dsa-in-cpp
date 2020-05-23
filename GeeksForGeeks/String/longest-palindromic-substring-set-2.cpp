// https://www.geeksforgeeks.org/longest-palindromic-substring-set-2/
// https://practice.geeksforgeeks.org/problems/longest-palindrome-in-a-string/0

// Time: O(n^2), Extra-Space: O(1) [obviously O(n) space is still needed for storing the generated substring(s) themselves (one-at-a-time)]

/*
aaaabbaa
------
aabbaa

======

forgeeksskeegfor
------
geeksskeeg
*/

#include <cstdio>
#include <iostream>

using namespace std;

void findOddLenPalSubstr(string, int &, int &);
void findEvenLenPalSubstr(string, int &, int &);

int main() {
  string str;
  cin >> str;

  int palSubstrLen = 1, palSubstrStartInd = 0;
  findOddLenPalSubstr(str, palSubstrLen, palSubstrStartInd);
  findEvenLenPalSubstr(str, palSubstrLen, palSubstrStartInd);

  cout << /*"Longest palindromic substring is " <<*/ str.substr(palSubstrStartInd, palSubstrLen) << endl;
  // printf("Longest palindromic substring spans between str[%d]=%c and str[%d]=%c\n", palSubstrStartInd, str[palSubstrStartInd], (palSubstrStartInd + palSubstrLen - 1), str[palSubstrStartInd + palSubstrLen - 1]);


  return 0;
}

void findOddLenPalSubstr(string str, int &palSubstrLen, int &palSubstrStartInd) {
  for (int i = 1; i < str.size() - 2; i++) {
    for (int j = 1; (i - j > 0) && (i + j < str.size()); j++) {
      if (str.at(i - j) == str.at(i + j)) {
        int len = 2 * j + 1;
        int startInd = i - j;
        if (len > palSubstrLen) {
          palSubstrLen = len;
          palSubstrStartInd = startInd;
        }
      } else {
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
      for (int j = 1; (i - j > 0) && (i + 1 + j < str.size()); j++) {
        if (str.at(i - j) == str.at(i + 1 + j)) {
          len = 2 * j + 2;
          startInd = i - j;
          if (len > palSubstrLen) {
            palSubstrLen = len;
            palSubstrStartInd = startInd;
          }
        } else {
          break;
        }
      }
    }
  }
}
