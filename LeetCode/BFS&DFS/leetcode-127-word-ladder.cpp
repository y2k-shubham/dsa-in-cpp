// LeetCode-127: https://leetcode.com/problems/word-ladder/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void showVisitedSet(set<string> mSet);
void showQue(queue<string> que);
void showSet(set<char> mSet);
map<int, set<char> > preparePosCharMap(vector<string>& wordList, int wordLen);
void testLadderLength();
int ladderLength(string beginWord, string endWord, vector<string>& wordList, bool debug);
int ladderLength(string beginWord, string endWord, vector<string>& wordList);

int main() {
    testLadderLength();

    return 0;
}

void showQue(queue<string> que) {
    printf("\nQueue is:-\n");
    while (!que.empty()) {
        cout << que.front() << "\t";
        que.pop();
    }
    cout << endl;
}

void showVisitedSet(set<string> mSet) {
    printf("\nVisited set is:-\n");
    for (set<string>::iterator i = mSet.begin(); i != mSet.end(); i++) {
        printf("%s, ", (*i).c_str());
    }
    cout << endl;
}

void showSet(set<char> mSet) {
    printf("(");
    for (set<char>::iterator i = mSet.begin(); i != mSet.end(); i++) {
        printf("%c, ", *i);
    }
    printf(")");
    cout << endl;
}

void showPosCharSetMap(map<int, set<char> > posCharSetMap) {
    printf("\nposCharSetMap is:-\n");
    for (map<int, set<char> >::iterator i = posCharSetMap.begin(); i != posCharSetMap.end(); i++) {
        printf("[%d] -> ", (*i).first);
        showSet((*i).second);
    }
}

map<int, set<char> > preparePosCharMap(vector<string>& wordList, int wordLen) {
    map<int, set<char> > posCharSetMap;
    for (int i = 0; i < wordLen; i++) {
        set<char> charSet;
        for (int j = 0; j < wordList.size(); j++) {
            charSet.insert(wordList[j].at(i));
        }
        posCharSetMap[i] = charSet;
    }
    return posCharSetMap;
}

void testLadderLength() {
    vector<string> wordList;

    wordList = {};
    assert(ladderLength("", "", wordList, false) == 0);

    wordList = {};
    assert(ladderLength("hit", "cog", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(ladderLength("", "", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(ladderLength("hit", "cog", wordList, false) == 5);

    wordList = {"hot", "dot", "dog", "lot", "log"};
    assert(ladderLength("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLength("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLength("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLength("hit", "cog", wordList, false) == 0);
}

// barely passes: LC bottom 5% percentile (both memory & runtime)
int ladderLength(string beginWord, string endWord, vector<string>& wordList, bool debug) {
    int wordLen = beginWord.size();
    set<string> wordSet(wordList.begin(), wordList.end());

    if (beginWord.empty() || (beginWord.size() != endWord.size()) || wordList.empty() || wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }

    map<int, set<char> > posCharSetMap = preparePosCharMap(wordList, wordLen);
    if (debug) {
        showPosCharSetMap(posCharSetMap);
    }

    queue<string> que;
    set<string> visitedWords;

    visitedWords.insert(beginWord);
    que.push(beginWord);

    for (int steps = 1; !que.empty(); steps++) {
        int qLen = que.size();

        if (debug) {
            printf("\n=========================================================\n");
            printf("steps = %d, qLen = %d\n", steps, qLen);
            showQue(que);
            showVisitedSet(visitedWords);
        }

        for (int i = 0; i < qLen; i++) {
            string crrWord = que.front();
            que.pop();

            if (debug) {
                printf("\n------------------------------------------------------\n");
                printf("crrWord = %s\n", crrWord.c_str());
            }

            for (int j = 0; j < wordLen; j++) {
                set<char> possibleChars = posCharSetMap[j];

                if (debug) {
                    printf("\n*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *\n");
                    printf("trying replacements for char j=%d with following set\n", j);
                    showSet(possibleChars);
                    cout << endl;
                }

                for (set<char>::iterator k = possibleChars.begin(); k != possibleChars.end(); k++) {
                    string crrWordCopy = crrWord;
                    crrWordCopy[j] = *k;

                    if (crrWordCopy == endWord) {
                        if (debug) {
                            printf("%s: endWord found!\n", crrWordCopy.c_str());
                        }
                        return (steps + 1);
                    } else if (wordSet.find(crrWordCopy) != wordSet.end() && visitedWords.find(crrWordCopy) == visitedWords.end()) {
                        visitedWords.insert(crrWordCopy);
                        que.push(crrWordCopy);
                        if (debug) {
                            printf("%s: added to que, visitedSet\n", crrWordCopy.c_str());
                        }
                    } else {
                        if (debug) {
                            printf("%s: discarded\n", crrWordCopy.c_str());
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    return ladderLength(beginWord, endWord, wordList, false);
}