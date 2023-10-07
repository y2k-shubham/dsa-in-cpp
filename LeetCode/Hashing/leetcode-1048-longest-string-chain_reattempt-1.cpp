// LeetCode-1048: https://leetcode.com/problems/longest-string-chain/
/**
 * high-level-approach
 * 1. create a map of {length : {set of words of that length}}
 * 2. (ignore the words having shortest length) starting from 2nd-shortest length, for each word
 *   - one by one try deleting each one it's characters and see if the reduced word exists in our set (or map)
 *   - if reduced word exists in map, then chain ending at current word would be
 *     at least 1 + max length chain ending at reduced word
 */

#include <iostream>
#include <map>
#include <string>
#include <cassert>

using namespace std;

class Solution {
private:
    inline string getWordWithoutChar(string word, int idx) {
        word.erase(idx, 1);
        return word;
    }

    map<int, map<string, int>> createMap(vector<string>& words) {
        map<int, map<string, int>> mOuterMap;

        for (vector<string>::iterator w = words.begin(); w != words.end(); w++) {
            string word = *w;
            int wordLen = word.size();

            if (mOuterMap.find(wordLen) == mOuterMap.end()) {
                map<string, int> mInnerMap;
                mOuterMap[wordLen] = mInnerMap;
            }

            mOuterMap[wordLen][word] = 1;
        }

        return mOuterMap;
    }

    int populateMap(map<int, map<string, int>>& mMap) {
        int maxLenChain = 1;

        for (map<int, map<string, int>>::iterator it1 = mMap.begin(); it1 != mMap.end(); it1++) {
            int crrWordLen = it1->first;
            map<string, int> crrLenWordSet = it1->second;

            if (mMap.find(crrWordLen - 1) == mMap.end()) {
                // no word with length crrWordLen - 1, implying that current set of words 'crrWordSet'
                // cannot be formed by adding one char to any other word in the set.
                continue;
            }

            map<string, int> prevLenWordSet = mMap[crrWordLen - 1];
            for (map<string, int>::iterator it2 = crrLenWordSet.begin(); it2 != crrLenWordSet.end(); it2++) {
                string crrWord = it2->first;
                int crrWordEndingMaxLenChain = 1;

                for (int i = 0; i < crrWordLen; i++) {
                    string crrWordPredecessor = getWordWithoutChar(crrWord, i);
                    if (prevLenWordSet.find(crrWordPredecessor) != prevLenWordSet.end()) {
                        crrWordEndingMaxLenChain = max(crrWordEndingMaxLenChain, 1 + prevLenWordSet[crrWordPredecessor]);
                    }
                }

                maxLenChain = max(maxLenChain, crrWordEndingMaxLenChain);
                mMap[crrWordLen][crrWord] = crrWordEndingMaxLenChain;
            }
        }

        return maxLenChain;
    }

public:
    friend class SolutionTest;

    int longestStrChain(vector<string>& words) {
        map<int, map<string, int>> mMap = createMap(words);
        return populateMap(mMap);
    }
};

class SolutionTest {
public:
    void testCreateMap() {
        Solution soln = Solution();
        vector<string> words;
        map<int, map<string, int>> mOuterMapExpected, mOuterMapComputed;

        words = {"a", "b", "ba", "bca", "bda", "bdca"};
        mOuterMapExpected = {
                {1, {
                            {"a",    1},
                            {"b",   1}
                    }},
                {2, {
                            {"ba",   1}
                    }},
                {3, {
                            {"bca",  1},
                            {"bda", 1}
                    }},
                {4, {
                            {"bdca", 1}
                    }}
        };
        mOuterMapComputed = soln.createMap(words);
        assert(mOuterMapExpected == mOuterMapComputed);

        words = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        mOuterMapExpected = {
                {2, {
                            {"xb",     1}
                    }},
                {3, {
                            {"xbc",    1}
                    }},
                {4, {
                            {"cxbc",   1}
                    }},
                {5, {
                            {"pcxbc",  1}
                    }},
                {6, {
                            {"pcxbcf", 1}
                    }}
        };
        mOuterMapComputed = soln.createMap(words);
        assert(mOuterMapExpected == mOuterMapComputed);

        words = {"abcd", "dbqca"};
        mOuterMapExpected = {
                {4, {
                            {"abcd",  1}
                    }},
                {5, {
                            {"dbqca", 1}
                    }}
        };
        mOuterMapComputed = soln.createMap(words);
        assert(mOuterMapExpected == mOuterMapComputed);
    }

    void testPopulateMap() {
        Solution soln = Solution();
        vector<string> words;
        map<int, map<string, int>> mMapOutExpected, mMapOutComputed;
        int maxLenOutExpected, maxLenOutComputed;

        words = {"a", "b", "ba", "bca", "bda", "bdca"};
        mMapOutExpected = {
                {1, {
                            {"a",    1},
                            {"b",   1}
                    }},
                {2, {
                            {"ba",   2}
                    }},
                {3, {
                            {"bca",  3},
                            {"bda", 3}
                    }},
                {4, {
                            {"bdca", 4}
                    }}
        };
        maxLenOutExpected = 4;
        mMapOutComputed = soln.createMap(words);
        maxLenOutComputed = soln.populateMap(mMapOutComputed);
        assert(mMapOutExpected == mMapOutComputed);
        assert(maxLenOutExpected == maxLenOutComputed);

        words = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        mMapOutExpected = {
                {2, {
                            {"xb",     1}
                    }},
                {3, {
                            {"xbc",    2}
                    }},
                {4, {
                            {"cxbc",   3}
                    }},
                {5, {
                            {"pcxbc",  4}
                    }},
                {6, {
                            {"pcxbcf", 5}
                    }}
        };
        maxLenOutExpected = 5;
        mMapOutComputed = soln.createMap(words);
        maxLenOutComputed = soln.populateMap(mMapOutComputed);
        assert(mMapOutExpected == mMapOutComputed);
        assert(maxLenOutExpected == maxLenOutComputed);

        words = {"abcd", "dbqca"};
        mMapOutExpected = {
                {4, {
                            {"abcd",  1}
                    }},
                {5, {
                            {"dbqca", 1}
                    }}
        };
        maxLenOutExpected = 1;
        mMapOutComputed = soln.createMap(words);
        maxLenOutComputed = soln.populateMap(mMapOutComputed);
        assert(mMapOutExpected == mMapOutComputed);
        assert(maxLenOutExpected == maxLenOutComputed);
    }

    void testLongestStrChain() {
        Solution soln = Solution();
        vector<string> words;
        int outExpected, outComputed;

        words = {"a", "b", "ba", "bca", "bda", "bdca"};
        outExpected = 4;
        outComputed = soln.longestStrChain(words);
        assert(outExpected == outComputed);

        words = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        outExpected = 5;
        outComputed = soln.longestStrChain(words);
        assert(outExpected == outComputed);

        words = {"abcd", "dbqca"};
        outExpected = 1;
        outComputed = soln.longestStrChain(words);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateMap();
    solnTest.testPopulateMap();
    solnTest.testLongestStrChain();

    return 0;
}
