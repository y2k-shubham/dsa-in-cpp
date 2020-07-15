// https://leetcode.com/problems/longest-valid-parentheses/
// https://www.geeksforgeeks.org/length-of-the-longest-valid-substring/

#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>
#include <cmath>
#include <cassert>

using namespace std;

int longestValidParentheses(string s);
pair <int, int> longestValidParen(string s);

int main() {
  assert(longestValidParentheses("(()") == 2);
  assert(longestValidParentheses(")()())") == 4);
  assert(longestValidParentheses("((()") == 2);
  assert(longestValidParentheses("()(()))))") == 6);
  assert(longestValidParentheses("()(())") == 6);

  return 0;
}

int longestValidParentheses(string s) {
  pair <int, int> longParenInd = longestValidParen(s);
  if (longParenInd.first == -1) {
    return 0;
  } else {
    return (longParenInd.second - longParenInd.first + 1);
  }
}

pair <int, int> longestValidParen(string s) {
  stack <int> stk;
  pair <int, int> longParenInd;
  int longParenLen;
  
  longParenInd = make_pair(-1, -1);
  longParenLen = -1;
  stk.push(-1);
  for (int i = 0; i < s.length(); i++) {
    char c = s.at(i);
    if (c == '(') {
      stk.push(i);
    } else if (stk.size() == 1) {
      // invalid; reset
      stk.pop();
      stk.push(i);
    } else {
      // valid
      stk.pop();
      int begInd = stk.top() + 1;
      int len = i - begInd + 1;
      
      if (len > longParenLen) {
        longParenLen = len;
        longParenInd.first = begInd;
        longParenInd.second = i;
      }
    }
  }

  return longParenInd;
}