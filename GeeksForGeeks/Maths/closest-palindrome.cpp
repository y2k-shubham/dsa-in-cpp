// Amazon Interview Question (Difficullty: Hard)
// https://practice.geeksforgeeks.org/problems/closest-palindrome/0
// submitted but lots of edge cases (not sure if all are covered)

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void runClosestPalin();
int getNumDigits(int);
bool isPalin(vector<int>);
vector<int> convertToDigVec(int);
int convertToNum(vector<int>);
vector<int> convertToPalinVec(vector<int>);
vector<int> convertToLowerPalinVec(vector<int>);
vector<int> convertToHigherPalinVec(vector<int>);
void showVec(vector<int>);

int main() {
    int T;
    cin >> T;

    while (T-- > 0) {
        runClosestPalin();
    }

    return 0;
}

void runClosestPalin() {
    int n;

    cout << "Enter positive integer: ";
    cin >> n;

    vector<int> digVec = convertToDigVec(n);
    int closestPalin = -999;

    if (isPalin(digVec)) {
        closestPalin = n;
    } else {
      /**
       * The resulting palindrome will be either
       * lesser or bigger than original number
       */
      vector<int> palinVec = convertToPalinVec(digVec);
      int palinNum = convertToNum(palinVec);

      // showVec(palinVec);
      // cout << "palinNum = " << palinNum << endl <<  endl;

      int lowerPalin, higherPalin;
      int diffLower, diffHigher;
      if (palinNum < n) {
          lowerPalin = palinNum;
          diffLower = n - lowerPalin;

          vector<int> higherPalinVec = convertToHigherPalinVec(palinVec);
          higherPalin = convertToNum(higherPalinVec);
          diffHigher = higherPalin - n;
      } else {
          higherPalin = palinNum;
          diffHigher = higherPalin - n;

          vector<int> lowerPalinVec = convertToLowerPalinVec(palinVec);
          lowerPalin = convertToNum(lowerPalinVec);

          diffLower = n - lowerPalin;
      }

      if (diffLower <= diffHigher) {
          closestPalin = lowerPalin;
      } else {
          closestPalin = higherPalin;
      }

      cout << endl;
      cout << "Lower   palin is " << lowerPalin << endl;
      cout << "Higher  palin is " << higherPalin << endl;
    }

    cout << "Closest palin is " << closestPalin << endl;
}

int getNumDigits(int n) {
    // assumes n >= 0
    if (n == 0) {
        return 0;
    } else {
        return (1 + getNumDigits(n / 10));
    }
}

bool isPalin(vector<int> digVec) {
    int len = digVec.size();
    for (int i = 0; i <= ((len / 2) - 1); i++) {
        if (digVec[i] != digVec[len - i - 1]) {
            return false;
        }
    }

    return true;
}

vector<int> convertToDigVec(int n) {
    vector<int> digVec;
    for (int i = 0; n > 0; i++) {
        digVec.push_back(n % 10);
        n /= 10;
    }

    return digVec;
}

int convertToNum(vector<int> digVec) {
    int n = 0;
    for (int i = digVec.size() - 1; i >= 0; i--) {
        n = (n * 10) + digVec[i];
    }

    return n;
}

void showVec(vector<int> digVec) {
    cout << endl;

    for (int i = digVec.size() - 1; i >= 0; i--) {
        printf("[%d]\t", i);
    }
    cout << endl;

    for (int i = digVec.size() - 1; i >= 0; i--) {
        printf("%d\t", digVec[i]);
    }
    cout << endl;
}

vector<int> convertToPalinVec(vector<int> digVec) {
    int len = digVec.size();
    vector<int> palVec = digVec;

    for (int i = 0; i < (len / 2); i++) {
        palVec[i] = digVec[len - i - 1];
    }

    return palVec;
}

vector<int> convertToLowerPalinVec(vector<int> palinVec) {
    int len = palinVec.size();
    vector<int> lowerPalinVec = palinVec;

    int i;
    for (i = (len / 2); (i < len) && (lowerPalinVec[i] == 0); i++) {
        lowerPalinVec[i] = 9;
    }
    lowerPalinVec[i]--;

    if (lowerPalinVec[lowerPalinVec.size() - 1] == 0) {
        /**
         * palindrome with one less digit.
         * will never happen until smaller
         * palindrome is explicitly requested
         */
        lowerPalinVec.pop_back();
        lowerPalinVec[(len / 2) - 1] = 9;
    }

    lowerPalinVec = convertToPalinVec(lowerPalinVec);
    return lowerPalinVec;
}

vector<int> convertToHigherPalinVec(vector<int> palinVec) {
    int len = palinVec.size();
    vector<int> higherPalinVec = palinVec;

    int i;
    for (i = (len / 2); (i < len) && (higherPalinVec[i] == 9); i++) {
        higherPalinVec[i] = 0;
    }

    if (i < len) {
        higherPalinVec[i]++;
    } else {
        i--;
        /**
       * palindrome with one more digit.
       * will never happen until bigger
       * palindromme is explicitly requested
       */
        higherPalinVec.push_back(1);
    }

    higherPalinVec = convertToPalinVec(higherPalinVec);

    return higherPalinVec;
}
