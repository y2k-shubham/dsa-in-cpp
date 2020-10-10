// LeetCode-139: https://leetcode.com/problems/word-break/
// https://www.interviewbit.com/problems/word-break/
// TusharRoy: https://www.youtube.com/watch?v=WepWFGxiwRs

/*
"applepenapple"
["apple","pen"]
*/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int> > createTab(set<string>& wordSet, string s);
void showTab(string s, vector<vector<int> >& tab);
void fillTab(set<string>& wordSet, string s, vector<vector<int> >& tab);
void testWordBreak();
bool wordBreak(string s, vector<string>& wordDict);

int main() {
    testWordBreak();
    return 0;
}

vector<vector<int> > createTab(set<string>& wordSet, string s) {
    int len = s.size();

    vector<vector<int> > tab(len);
    for (int i = 0; i < len; i++) {
        vector<int> tabRow(len, -1);

        string charWord = s.substr(i, 1);
        if (wordSet.find(charWord) != wordSet.end()) {
            tabRow[i] = i;
        }

        tab[i] = tabRow;
    }

    return tab;
}

void showTab(string s, vector<vector<int> >& tab) {
    int len = s.size();

    cout << "\t";
    for (int j = 0; j < len; j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    cout << "\t";
    for (int j = 0; j < len; j++) {
        printf("%c\t", s.at(j));
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("[%d] %c\t", i, s.at(i));
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        // cout << "\t";
        for (int j = i; j < len; j++) {
            if (tab[i][j] < 0) {
                printf("-\t");
            } else {
                printf("%d\t", tab[i][j]);
            }
        }
        cout << endl;
    }
}

// poor score on LC: speed 16%, memory 11%
// goes OOM on InterviewBit
void fillTab(set<string>& wordSet, string s, vector<vector<int> >& tab) {
    int len = s.size();

    // showTab(s, tab);
    for (int wordLen = 2; wordLen <= len; wordLen++) {
        int rLo = 0;
        int cLo = wordLen - 1;

        int cHi = len - 1;

        int i = rLo;
        int j = cLo;
        while (j <= cHi) {
            string crrSubStr = s.substr(i, (j - i + 1));
            if (wordSet.find(crrSubStr) != wordSet.end()) {
                tab[i][j] = j;
            } else {
                for (int k = i; k < j; k++) {
                    // string subStr1 = s.substr(i, (k - i + 1));
                    // if (wordSet.find(subStr1) == wordSet.end()) {
                    if (tab[i][k] < 0) {
                        continue;
                    }

                    // string subStr2 = s.substr(k + 1, (j - k));
                    // if (wordSet.find(subStr2) != wordSet.end()) {
                    if (tab[k + 1][j] >= 0) {
                        tab[i][j] = k;
                        break;
                    }
                }
            }

            i++;
            j++;
        }

        // showTab(s, tab);
    }
}

void testWordBreak() {
    string s;
    vector<string> wordDict;

    s = "applepenapple";
    wordDict = {"apple", "pen"};
    assert(wordBreak(s, wordDict) == true);
}

bool wordBreak(string s, vector<string>& wordDict) {
    int len = s.size();
    set<string> wordSet(wordDict.begin(), wordDict.end());

    vector<vector<int> > tab = createTab(wordSet, s);
    fillTab(wordSet, s, tab);

    return tab[0][len - 1] >= 0;
}
