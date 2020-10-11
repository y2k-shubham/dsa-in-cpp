// LeetCode-140: https://leetcode.com/problems/word-break-ii/
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

vector<vector<vector<int> > > createTab(set<string>& wordSet, string s);
void showTab(string s, vector<vector<vector<int> > >& tab);
void fillTab(set<string>& wordSet, string s, vector<vector<vector<int> > >& tab, bool);
void testWordBreak();
vector<string> wordBreak(string s, vector<string>& wordDict, bool debug);
vector<string> wordBreak(string s, vector<string>& wordDict);
void buildSentences(string s, vector<vector<vector<int> > >& tab, vector<vector<string> >& sentences, int& sInd, int r, int c, bool);
void showSentences(vector<vector<string> > sentences);
void showSentences(vector <string> sentences);
vector<string> buildSentences(vector<vector<string> > sentences);

int main() {
    testWordBreak();
    return 0;
}

vector<vector<vector<int> > > createTab(set<string>& wordSet, string s) {
    int len = s.size();

    vector<vector<vector<int> > > tab(len);
    for (int i = 0; i < len; i++) {
        vector<vector<int> > tabRow(len);

        string charWord = s.substr(i, 1);
        if (wordSet.find(charWord) != wordSet.end()) {
            tabRow[i].push_back(i);
        }

        tab[i] = tabRow;
    }

    return tab;
}

void showTab(string s, vector<vector<vector<int> > >& tab) {
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
            if (tab[i][j].empty()) {
                printf("-\t");
            } else {
                vector<int> indices = tab[i][j];
                printf("[%d", indices[0]);
                for (int k = 1; k < indices.size(); k++) {
                    printf(",%d", indices[k]);
                }
                printf("]\t");
            }
        }
        cout << endl;
    }
}

void fillTab(set<string>& wordSet, string s, vector<vector<vector<int> > >& tab, bool debug) {
    int len = s.size();

    if (debug) {
      showTab(s, tab);
    }
    for (int wordLen = 2; wordLen <= len; wordLen++) {
        int rLo = 0;
        int cLo = wordLen - 1;

        int cHi = len - 1;

        int i = rLo;
        int j = cLo;
        while (j <= cHi) {
            string crrSubStr = s.substr(i, (j - i + 1));
            if (wordSet.find(crrSubStr) != wordSet.end()) {
                tab[i][j].push_back(j);
            } else {
                for (int k = i; k < j; k++) {
                    // string subStr1 = s.substr(i, (k - i + 1));
                    // if (wordSet.find(subStr1) == wordSet.end()) {
                    if (tab[i][k].empty()) {
                        continue;
                    }

                    // string subStr2 = s.substr(k + 1, (j - k));
                    // if (wordSet.find(subStr2) != wordSet.end()) {
                    if (!tab[k + 1][j].empty()) {
                        tab[i][j].push_back(k);
                    }
                }
            }

            i++;
            j++;
        }

        if (debug) {
          showTab(s, tab);
        }
    }
}

void testWordBreak() {
    string s;
    vector<string> wordDict;
    vector<string> sentences;

    s = "applepenapple";
    wordDict = {"apple", "pen"};
    sentences = {"apple pen apple"};
    // showSentences(wordBreak(s, wordDict));
    assert(wordBreak(s, wordDict) == sentences);

    s = "catsanddog";
    wordDict = {"cat", "cats", "and", "sand", "dog"};
    sentences = {
      "cats and dog",
      "cat sand dog"
    };
    showSentences(wordBreak(s, wordDict));
    assert(wordBreak(s, wordDict) == sentences);
}

void buildSentences(string s, vector<vector<vector<int> > >& tab, vector<vector<string> >& sentences, int& sInd, int r, int c, bool debug) {
    if (tab[r][c].size() == 1 && tab[r][c][0] == c) {
        sentences[sInd].push_back(s.substr(r, c - r + 1));
    } else if (r <= c) {
        vector<string> crrSenCopy;
        if (sentences.size() > sInd) {
            crrSenCopy = sentences[sInd];
        }
        vector<int> splitInds = tab[r][c];

        for (int i = 0; i < splitInds.size(); i++, sInd++) {
            if (sentences.size() > sInd) {
                sentences[sInd] = crrSenCopy;
            } else {
                sentences.push_back(crrSenCopy);
            }

            int splitInd = splitInds[i];

            buildSentences(s, tab, sentences, sInd, r, splitInd, debug);
            buildSentences(s, tab, sentences, sInd, splitInd + 1, c, debug);
        }
    }
}

void showSentences(vector<vector<string> > sentences) {
    printf("\nsentences are:-\n");
    for (int i = 0; i < sentences.size(); i++) {
        vector<string> crrSentence = sentences[i];
        for (int j = 0; j < crrSentence.size(); j++) {
            printf("%s ", crrSentence[j].c_str());
        }
        cout << endl;
    }
}

void showSentences(vector <string> sentences) {
  cout << endl;
  for (int i = 0; i < sentences.size(); i++) {
    printf("'%s'\n", sentences[i].c_str());
  }
}

vector<string> buildSentences(vector<vector<string> > sentences) {
    vector<string> sentencesWithSpaces(sentences.size());
    for (int i = 0; i < sentences.size(); i++) {
        vector<string> crrSentenceVec = sentences[i];

        string crrSentenceStr = crrSentenceVec[0];
        for (int j = 1; j < crrSentenceVec.size(); j++) {
            crrSentenceStr = crrSentenceStr + " " + crrSentenceVec[j];
        }

        sentencesWithSpaces[i] = crrSentenceStr;
    }

    return sentencesWithSpaces;
}

vector<string> wordBreak(string s, vector<string>& wordDict, bool debug) {
    int len = s.size();
    set<string> wordSet(wordDict.begin(), wordDict.end());

    vector<vector<vector<int> > > tab = createTab(wordSet, s);
    fillTab(wordSet, s, tab, debug);

    // showTab(s, tab);

    vector<vector<string> > sentences;
    int r = 0;
    int c = len - 1;
    int sInd = 0;
    buildSentences(s, tab, sentences, sInd, r, c, debug);
    // showSentences(sentences);

    return buildSentences(sentences);
    // return {};
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
    return wordBreak(s, wordDict, false);
}
