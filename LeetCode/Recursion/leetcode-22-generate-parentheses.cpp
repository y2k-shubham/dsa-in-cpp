// LeetCode 22: https://leetcode.com/problems/generate-parentheses/
// https://www.geeksforgeeks.org/print-all-combinations-of-balanced-parentheses/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void genPerms(char openParen, char closedParen, int n, char* str, vector <string>& perms, int i, int doneOpen, int doneClosed);

int main() {
  int n;
  cin >> n;

  char str[2 * n + 1];  // 1 extra space at end for null char '\0'
  vector <string> perms;
  
  genPerms('(', ')', n, str, perms, 0, 0, 0);

  for (vector <string>::iterator it = perms.begin(); it != perms.end(); it++) {
    cout << *it << endl;
    // cout << (*it).size() << endl;
  }

  return 0;
}

void genPerms(char openParen, char closedParen, int n, char* str, vector <string>& perms, int i, int doneOpen, int doneClosed) {
  if (i == (2 * n)) {
    str[i] = '\0';
    string perm(str);

    perms.push_back(perm);
    // cout << perm << endl;

    return;
  }

  if (doneOpen < n) {
    str[i] = openParen;
    genPerms(openParen, closedParen, n, str, perms, i + 1, doneOpen + 1, doneClosed);
  }
  if (doneClosed < doneOpen) {
    str[i] = closedParen;
    genPerms(openParen, closedParen, n, str, perms, i + 1, doneOpen, doneClosed + 1);
  }
}

vector<string> generateParenthesis(int n) {
  char str[2 * n + 1];  // 1 extra space at end for null char '\0'
  vector <string> perms;

  genPerms('(', ')', n, str, perms, 0, 0, 0);

  return perms;
}
