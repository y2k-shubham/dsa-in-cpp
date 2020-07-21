// https://leetcode.com/problems/regular-expression-matching/
// incorrect code (too many edge cases, can't be solved in this way)

/*
a ab*
true
*/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool doesMatch(string str, int strInd, string exp, int expInd);

int main() {
    assert(doesMatch("aa", 0, "a", 0) == false);
    assert(doesMatch("aa", 0, "a*", 0) == true);
    assert(doesMatch("ab", 0, ".*", 0) == true);
    assert(doesMatch("aab", 0, "c*a*b", 0) == true);
    assert(doesMatch("mississippi", 0, "mis*is*p*.", 0) == false);
    assert(doesMatch("a", 0, "ab*.", 0) == false);
    assert(doesMatch("ab", 0, ".*c", 0) == false);

    printf("all passed\n");

    return 0;
}

bool doesMatch(string str, int strInd, string exp, int expInd) {
    printf("\n=========\n");
    printf("str = %s, exp = %s\n", str.c_str(), exp.c_str());
    printf("strInd = %d, expInd = %d\n", strInd, expInd);

    int strSize = (int) str.size();
    int expSize = (int) exp.size();

    bool strFinished = strInd >= strSize;
    // printf("done1\n");
    bool expIsStar = (expInd <= (expSize - 2)) && exp.at(expInd + 1) == '*';
    // printf("done2\n");
    bool expFinished =  (!expIsStar && expInd >= expSize);
    bool expFinishedAtStar = (expIsStar && (expInd == expSize - 2));

    printf("strFinished = %s, expIsStar = %s, expFinished = %s, expFinishedAtStar = %s\n", (strFinished ? "true" : "false"), (expIsStar ? "true" : "false"), (expFinished ? "true" : "false"), (expFinishedAtStar ? "true" : "false"));

    if (strFinished && (expFinished || expFinishedAtStar)) {
        printf("both finisedh, returning true\n");
        return true;
    }
    
    else if (strFinished && !expFinished) {
      printf("str finished, exp didn't, returning expFinihsedAtStar\n");
      return expFinishedAtStar;
    }
    
    else if (!strFinished && expFinished && !expIsStar) {
      printf("str didn't finish, exp did, returning false\n");
      return false;
    }  

    //  else if (strFinished && !expFinished) {
    //     printf("str finished, exp didn't, returning expIsStar = %s\n", (expIsStar ? "true" : "false"));
    //     return expIsStar;
    // } else if (!strFinished && expFinished) {
    //     printf("str didn't finish, exp did, returning false\n");
    //     return false;
    // }
    
     else {
        char strCh = str.at(strInd);
        char expCh = exp.at(expInd);
        bool expIsDot = expCh == '.';

        printf("str[%d] = %c, exp[%d] = %c\n", strInd, strCh, expInd, expCh);
        printf("expIsDot = %s, expIsStar = %s\n", (expIsDot ? "true" : "false"), (expIsStar ? "true" : "false"));

        if (expIsStar) {
            if (expIsDot || strCh == expCh) {
                printf("block 1\n");
                return doesMatch(str, strInd + 1, exp, expInd) || doesMatch(str, strInd + 1, exp, expInd + 2) || doesMatch(str, strInd, exp, expInd + 2);
            } else {
                printf("block 2\n");
                return doesMatch(str, strInd, exp, expInd + 2);
            }
        } else {
            if (expIsDot || strCh == expCh) {
                printf("block 3\n");
                return doesMatch(str, strInd + 1, exp, expInd + 1);
            } else {
                printf("block 4\n");
                return false;
            }
        }
    }
}
