// LeetCode-1048: https://leetcode.com/problems/longest-string-chain/

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <list>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    bool isChain(string& wSmall, string& wLong) {
        int wSmallLen = wSmall.size();
        int wLongLen = wLong.size();

        if (wLongLen != (wSmallLen + 1)) {
            return false;
        }

        int iSmall = 0;
        int iLong = 0;
        bool mismatchFound = false;
        while ((iSmall < wSmallLen) && (iLong < wLongLen)) {
            if (wSmall[iSmall] != wLong[iLong]) {
                if (mismatchFound) {
                    return false;
                } else {
                    iSmall--;
                    mismatchFound = true;
                }
            }

            iSmall++;
            iLong++;
        }

        return true;
    }

    pair<int, int> findSmallestAndBiggestKeys(unordered_map<int, unordered_map<string, pair<int, string> >>& mMap) {
        pair<int, int> pSmallestAndBiggestKeys;
        pSmallestAndBiggestKeys.first = INT_MAX;
        pSmallestAndBiggestKeys.second = INT_MIN;

        for (auto& p: mMap) {
            int key = p.first;
            if (key < pSmallestAndBiggestKeys.first) {
                pSmallestAndBiggestKeys.first = key;
            }
            if (key > pSmallestAndBiggestKeys.second) {
                pSmallestAndBiggestKeys.second = key;
            }
        }

        return pSmallestAndBiggestKeys;
    }

    unordered_map<int, unordered_map<string, pair<int, string> >> buildMap(vector<string>& words) {
        unordered_map<int, unordered_map<string, pair<int, string> >> mMap;
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            int len = word.size();

            mMap[len][word] = {1, ""};
        }
        return mMap;
    }

    void showMap(unordered_map<int, unordered_map<string, pair<int, string> >>& mMap) {
        for (auto& m: mMap) {
            cout << "----------------" << endl;
            cout << "len: " << m.first << endl;
            for (auto& w: m.second) {
                cout << w.first << ": (" << w.second.first << ", " << w.second.second << ")" << endl;
            }
            cout << "----------------" << endl;
        }
    }

    int updateMap(unordered_map<int, unordered_map<string, pair<int, string> >>& mMap) {
        int maxChainLen = 1;

        pair<int, int> pSmallestAndBiggestKeys = findSmallestAndBiggestKeys(mMap);
        if (debug) {
            printf("smallest key: %d, biggest key: %d\n", pSmallestAndBiggestKeys.first,
                   pSmallestAndBiggestKeys.second);
        }

        for (int i = pSmallestAndBiggestKeys.first; i <= pSmallestAndBiggestKeys.second; i++) {
            if (mMap.find(i) == mMap.end()) {
                continue;
            }

            int crrWordsLen = i;
            if (mMap.find(crrWordsLen - 1) == mMap.end()) {
                if (debug) {
                    printf("skipping processing set of words with length=%d\n", crrWordsLen);
                }
                continue;
            } else {
                if (debug) {
                    printf("--------\n");
                    printf("processing set of words with length=%d\n", crrWordsLen);
                }
            }

            for (auto& wordPair: mMap[i]) {
                string crrWord = wordPair.first;
                int crrWordMaxChainLen = wordPair.second.first;
                string crrWordMaxChainPrevWord = wordPair.second.second;

                for (auto& prevWordPair: mMap[crrWordsLen - 1]) {
                    string prevWord = prevWordPair.first;
                    if (isChain(prevWord, crrWord)) {
                        if (debug) {
                            printf("%s and %s form a chain\n", prevWord.c_str(), crrWord.c_str());
                        }

                        if (prevWordPair.second.first + 1 > crrWordMaxChainLen) {
                            crrWordMaxChainLen = prevWordPair.second.first + 1;
                            crrWordMaxChainPrevWord = prevWord;
                            if (debug) {
                                printf("for %s, %s is the new max chain len prev word of chain len=%d\n",
                                       crrWord.c_str(), crrWordMaxChainPrevWord.c_str(), crrWordMaxChainLen);
                            }
                        }

                        if (debug) {
                            printf(". . . . . . . . .\n");
                        }
                    }
                }

                wordPair.second = {crrWordMaxChainLen, crrWordMaxChainPrevWord};
                if (debug) {
                    printf("for word: %s, maxChainLen: %d, maxChainPrevWord: %s\n", crrWord.c_str(), crrWordMaxChainLen,
                           crrWordMaxChainPrevWord.c_str());
                }
                maxChainLen = max(maxChainLen, crrWordMaxChainLen);
            }
        }

        return maxChainLen;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int longestStrChain(vector<string>& words) {
        unordered_map<int, unordered_map<string, pair<int, string> >> mMap = buildMap(words);
        if (debug) {
            showMap(mMap);
        }

        return updateMap(mMap);
    }
};

class SolutionTest {
public:
    void testLongestStrChain() {
        Solution soln = Solution();
        vector<string> wordsIn;
        int lenOutExpected, lenOutComputed;

//        soln.enableDebug();
        wordsIn = {"a", "b", "ba", "bca", "bda", "bdca"};
        lenOutExpected = 4;
        lenOutComputed = soln.longestStrChain(wordsIn);
        cout << lenOutComputed << endl;
        assert(lenOutComputed == lenOutExpected);
//        soln.disableDebug();

        wordsIn = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        lenOutExpected = 5;
        lenOutComputed = soln.longestStrChain(wordsIn);
        assert(lenOutComputed == lenOutExpected);

        wordsIn = {"abcd", "dbqca"};
        lenOutExpected = 1;
        lenOutComputed = soln.longestStrChain(wordsIn);
        assert(lenOutComputed == lenOutExpected);
    }
};

int main() {
    SolutionTest st = SolutionTest();
    st.testLongestStrChain();
    return 0;
}