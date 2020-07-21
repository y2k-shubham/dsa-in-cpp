// LeetCode 3: https://leetcode.com/problems/longest-substring-without-repeating-characters/
// geeksforgeeksandgeeksquiz
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

void showLongestUniqueCharSubstring(string, pair <int, int>);
pair <int, int> findLongestUniqueCharSubstring(string);

int main() {
  string str;
  
  cout << "Enter a long string: ";
  cin >> str;

  pair <int, int> mRange = findLongestUniqueCharSubstring(str);
  showLongestUniqueCharSubstring(str, mRange);

  return 0;
}

void showLongestUniqueCharSubstring(string str, pair <int, int> mRange) {
  int length = mRange.second - mRange.first + 1;
  printf("Longest substring with unique charcters is str[%d..%d] = %s\n", mRange.first, mRange.second, str.substr(mRange.first, length).c_str());
}

pair <int, int> findLongestUniqueCharSubstring(string str) {
  pair <int, int> mRange, cRange;
  int mLength, cLength;
  map <char, int> freqMap;
  int iLo, iHi;

  mLength = -1;
  iLo = 0;
  iHi = -1;
  // printf("iHi = %d, str.length() = %d, (iHi < str.length() - 1) = %d\n", iHi, (int) (str.length()), (iHi < (int) str.length() - 1));
  while (iHi < (int) str.length() - 1 || iLo < iHi) {
    // printf("puchi");
    // expanding
    while (iHi < (int) str.length() - 1) {
      // printf("\nstr[iLo=%d] = %c, str[iHi=%d]=%c\n", iLo, str.at(iLo), iHi, str.at(max(iHi, 0)));
      iHi++;
      // printf("str[iLo=%d] = %c, str[iHi=%d]=%c\n", iLo, str.at(iLo), iHi, str.at(max(iHi, 0)));
      char addedChar = str.at(iHi);
      freqMap[addedChar]++;
      if (freqMap[addedChar] == 2) {
        break;
      } else {
        cRange = make_pair(iLo, iHi);
        cLength = iHi - iLo + 1;
        if (cLength > mLength) {
          mLength = cLength;
          mRange = cRange;
        }
      }
    }
    // shrinking
    while (iLo < iHi) {
      // printf("\nstr[iLo=%d] = %c, str[iHi=%d]=%c\n", iLo, str.at(iLo), iHi, str.at(max(iHi, 0)));
      iLo++;
      // printf("str[iLo=%d] = %c, str[iHi=%d]=%c\n", iLo, str.at(iLo), iHi, str.at(max(iHi, 0)));
      char removedChar = str.at(iLo - 1);
      freqMap[removedChar]--;
      if (freqMap[removedChar] == 1) {
        break;
      }
    }
  }

  return mRange;
}
