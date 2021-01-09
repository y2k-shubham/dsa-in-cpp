// LeetCode-127: https://leetcode.com/problems/word-ladder/
// smart, simple soln: https://www.youtube.com/watch?v=O3hUyXyHeBw

// this (arguably) more advanced soln submitted 
// is ~ 8x slower than simpler, more rudimentary solution submitted in next attempt

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// map with pair keys https://stackoverflow.com/a/32685618/3679900
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

void showVisitedSet(set<string> mSet);
void showQue(queue<string> que);
void showSet(set<char> mSet);
map<int, set<char>> preparePosCharMap(vector<string>& wordList, int wordLen);
bool isAdjacent(string& word1, string& word2);
void testLadderLength();
void testLadderLengthOpt1();
void testLadderLengthOpt2();
void testLadderLengthOpt3();
int ladderLength(string beginWord, string endWord, vector<string>& wordList, bool debug);
int ladderLengthOpt1(string beginWord, string endWord, vector<string>& wordList, bool debug);
int ladderLengthOpt2(string beginWord, string endWord, vector<string>& wordList, bool debug);
bool isAdjacentMemo(unordered_map <pair <string, string>, bool, pair_hash>& areAdjMemo, string& word1, string& word2);
int ladderLengthOpt3(string beginWord, string endWord, vector<string>& wordList, bool debug);
int ladderLength(string beginWord, string endWord, vector<string>& wordList);

int main() {
    testLadderLength();
    testLadderLengthOpt1();
    testLadderLengthOpt2();
    testLadderLengthOpt3();

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

void showPosCharSetMap(map<int, set<char>> posCharSetMap) {
    printf("\nposCharSetMap is:-\n");
    for (map<int, set<char>>::iterator i = posCharSetMap.begin(); i != posCharSetMap.end(); i++) {
        printf("[%d] -> ", (*i).first);
        showSet((*i).second);
    }
}

// barely passes: LC bottom 5% percentile (both memory & runtime)

map<int, set<char>> preparePosCharMap(vector<string>& wordList, int wordLen) {
    map<int, set<char>> posCharSetMap;
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

int ladderLength(string beginWord, string endWord, vector<string>& wordList, bool debug) {
    int wordLen = beginWord.size();
    set<string> wordSet(wordList.begin(), wordList.end());

    if (beginWord.empty() || (beginWord.size() != endWord.size()) || wordList.empty() || wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }

    map<int, set<char>> posCharSetMap = preparePosCharMap(wordList, wordLen);
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

// (apparently) optimized soln is going TLE on LC ::facepalm::
// don't know how that girl in above video managed to submit it in Java

void testLadderLengthOpt1() {
    vector<string> wordList;

    wordList = {};
    assert(ladderLengthOpt1("", "", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(ladderLengthOpt1("", "", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    // cout << ladderLengthOpt1("hit", "cog", wordList, false) << endl;
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 5);

    wordList = {"hot", "dot", "dog", "lot", "log"};
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt1("hit", "cog", wordList, false) == 0);
}

bool isAdjacent(string& word1, string& word2) {
    bool diffFound = false;

    for (int i = 0; i < word1.size(); i++) {
        if (word1.at(i) != word2.at(i)) {
            if (diffFound) {
                return false;
            } else {
                diffFound = true;
            }
        }
    }

    return true;
}

int ladderLengthOpt1(string beginWord, string endWord, vector<string>& wordList, bool debug) {
    if (beginWord.empty() || endWord.empty() || wordList.empty()) {
        return 0;
    }

    queue<pair<string, int>> que;
    set<string> visitedWords;

    // short-cut to make_pair
    // i don't understand why this thing has to be initialized with 1 (instead of 0)
    que.push({beginWord, 1});
    visitedWords.insert(beginWord);
    while (!que.empty()) {
        pair<string, int> item = que.front();
        que.pop();

        for (int i = 0; i < wordList.size(); i++) {
            string targetWord = wordList[i];
            if (visitedWords.find(targetWord) == visitedWords.end() && isAdjacent(targetWord, item.first)) {
                if (targetWord == endWord) {
                    return item.second + 1;
                } else {
                    que.push({targetWord, item.second + 1});
                    visitedWords.insert(targetWord);
                }
            }
        }
    }

    return 0;
}

// and this one employing priority queue also goes TLE (different test case from previous one)

void testLadderLengthOpt2() {
    vector<string> wordList;

    wordList = {};
    assert(ladderLengthOpt2("", "", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(ladderLengthOpt2("", "", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    // cout << ladderLengthOpt2("hit", "cog", wordList, false) << endl;
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 5);

    wordList = {"hot", "dot", "dog", "lot", "log"};
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt2("hit", "cog", wordList, false) == 0);
}

int ladderLengthOpt2(string beginWord, string endWord, vector<string>& wordList, bool debug) {
    if (beginWord.empty() || endWord.empty() || wordList.empty()) {
        return 0;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pQue;
    set<string> visitedWords;

    // short-cut to make_pair
    // i don't understand why this thing has to be initialized with 1 (instead of 0)
    pQue.push({1, beginWord});
    visitedWords.insert(beginWord);
    while (!pQue.empty()) {
        pair<int, string> item = pQue.top();
        pQue.pop();

        for (int i = 0; i < wordList.size(); i++) {
            string targetWord = wordList[i];
            if (visitedWords.find(targetWord) == visitedWords.end() && isAdjacent(targetWord, item.second)) {
                if (targetWord == endWord) {
                    return item.first + 1;
                } else {
                    pQue.push({item.first + 1, targetWord});
                    visitedWords.insert(targetWord);
                }
            }
        }
    }

    return 0;
}

// how about an improved (cached / memoized) isAdjacent implementation? still TLE (same test case as previous one)
void testLadderLengthOpt3() {
    vector<string> wordList;

    wordList = {};
    assert(ladderLengthOpt3("", "", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(ladderLengthOpt3("", "", wordList, false) == 0);

    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    // cout << ladderLengthOpt3("hit", "cog", wordList, false) << endl;
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 5);

    wordList = {"hot", "dot", "dog", "lot", "log"};
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 0);

    wordList = {};
    assert(ladderLengthOpt3("hit", "cog", wordList, false) == 0);
}

bool isAdjacentMemo(unordered_map <pair <string, string>, bool, pair_hash>& areAdjMemo, string& word1, string& word2) {
    pair<string, string> strPair;
    if (word1.compare(word2) < 0) {
        strPair = {word1, word2};
    } else {
        strPair = {word2, word1};
    }

    if (areAdjMemo.find(strPair) != areAdjMemo.end()) {
        return areAdjMemo[strPair];
    } else {
        bool diffFound = false;

        for (int i = 0; i < word1.size(); i++) {
            if (word1.at(i) != word2.at(i)) {
                if (diffFound) {
                    areAdjMemo[strPair] = false;
                    return false;
                } else {
                    diffFound = true;
                }
            }
        }

        areAdjMemo[strPair] = true;
        return true;
    }
}

int ladderLengthOpt3(string beginWord, string endWord, vector<string>& wordList, bool debug) {
    if (beginWord.empty() || endWord.empty() || wordList.empty()) {
        return 0;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pQue;
    unordered_map <pair <string, string>, bool, pair_hash> areAdjMemo;
    set<string> visitedWords;

    // short-cut to make_pair
    // i don't understand why this thing has to be initialized with 1 (instead of 0)
    pQue.push({1, beginWord});
    visitedWords.insert(beginWord);
    while (!pQue.empty()) {
        pair<int, string> item = pQue.top();
        pQue.pop();

        for (int i = 0; i < wordList.size(); i++) {
            string targetWord = wordList[i];
            if (visitedWords.find(targetWord) == visitedWords.end() && isAdjacentMemo(areAdjMemo, targetWord, item.second)) {
                if (targetWord == endWord) {
                    return item.first + 1;
                } else {
                    pQue.push({item.first + 1, targetWord});
                    visitedWords.insert(targetWord);
                }
            }
        }
    }

    return 0;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    return ladderLength(beginWord, endWord, wordList, false);
}
