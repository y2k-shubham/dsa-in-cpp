// https://leetcode.com/problems/iterator-for-combination/
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3422/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

class CombinationIterator {
   private:
    string chars;
    int charsLen;
    int combLen;
    queue<string> que;

    void genCombs(string crrComb, int idx) {
        int crrCombLen = crrComb.size();
        if (idx < charsLen) {
          // printf("\n-----------\nat chars[%d] = %c, crrComb = %s\n", idx, chars.at(idx), crrComb.c_str());
        } else {
          // printf("\n-----------\nat chars[%d] = %c, crrComb = %s\n", idx, '?', crrComb.c_str());
        }

        if (combLen == crrCombLen) {
            // printf("added crrComb = %s to que\n", crrComb.c_str());
            que.push(crrComb);
        } else if (charsLen - idx < combLen - crrCombLen) {
            // printf("no hope, returning\n");
            return;
        } else {
            for (int i = idx; i < charsLen; i++) {
                genCombs(crrComb + chars.at(i), i + 1);
            }
        }
    }

   public:
    CombinationIterator(string characters, int combinationLength) {
        chars = characters;
        charsLen = characters.size();
        combLen = combinationLength;
        genCombs("", 0);
    }

    string next() {
        if (hasNext()) {
            string nextComb = que.front();
            que.pop();
            return nextComb;
        } else {
            return "";
        }
    }

    bool hasNext() {
        return !que.empty();
    }
};

int main() {
  CombinationIterator iter = CombinationIterator("abc", 2);


  return 0;
}
