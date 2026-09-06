// LeetCode-1647: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/

#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <cassert>
#include <list>

using namespace std;

#define MIN_CHAR 'a'
#define MAX_CHAR 'z'

class Solution {
private:
    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showMap(unordered_map<int, int>& mMap, const char* name) {
        printf("%s map is:-\n", name);

        for (auto it = mMap.begin(); it != mMap.end(); it++) {
            printf("[%d] -> %d\n", it->first, it->second);
        }
    }

    vector <int> createCharFreqVec(string& str) {
        vector <int> charFreqVec(MAX_CHAR + 1, 0);

        for (char ch: str) {
            charFreqVec[ch]++;
        }

        return charFreqVec;
    }

    unordered_map<int, int> createFreqFreqMap(vector <int>& charFreqVec) {
        unordered_map<int, int> freqFreqMap;

        for (int i = MIN_CHAR; i <= MAX_CHAR; i++) {
            int freq = charFreqVec[i];
            if (freq > 0) {
                freqFreqMap[charFreqVec[i]]++;
            }
        }

        return freqFreqMap;
    }

    int findValWithFreqGreaterThan1(unordered_map<int, int>& freqFreqMap) {
        for (auto it = freqFreqMap.begin(); it != freqFreqMap.end(); it++) {
            if (it->second > 1) {
                return it->first;
            }
        }

        return -1;
    }

    void cleanupZeroFreqFreqs(unordered_map<int, int>& freqFreqMap) {
        list <int> freqsToCleanup;
        for (auto it = freqFreqMap.begin(); it != freqFreqMap.end(); it++) {
            if (it->second == 0) {
                freqsToCleanup.push_back(it->first);
            }
        }

        for (int freqToCleanup : freqsToCleanup) {
            freqFreqMap.erase(freqToCleanup);
        }
    }

    pair <int, int> deleteSingleCharToMakeItsFreqUnique(unordered_map<int, int>& freqFreqMap, int val) {
        int crrFreq = freqFreqMap[val];
        if (crrFreq <= 1) {
            return {0, val};
        }

        int numDeletions = 0;
        while (freqFreqMap[val] > 1) {
            if (debug) {
                printf("decreasing freq of val=%d from freqFreq=%d\n", val, freqFreqMap[val]);
            }
            freqFreqMap[val]--;

            if (freqFreqMap[val] == 0) {
                if (debug) {
                    printf("freq of val=%d became zero, erasing\n", val);
                }
                freqFreqMap.erase(val);
            }

            numDeletions++;

            val--;
            if (val > 0) {
                if (debug) {
                    printf("increasing freq of val=%d from freqFreq=%d\n", val, freqFreqMap[val]);
                }
                freqFreqMap[val]++;
            }
        }

        cleanupZeroFreqFreqs(freqFreqMap);

        return {numDeletions, val};
    }

    int deleteAllCharsOfGivenFreqToMakeTheirFreqsUnique(unordered_map<int, int>& freqFreqMap, int val) {
        int numDeletions = 0;
        stack <int> valsToDecreaseFreq;

        valsToDecreaseFreq.push(val);
        while (!valsToDecreaseFreq.empty()) {
            int val = valsToDecreaseFreq.top();
            valsToDecreaseFreq.pop();

            int crrFreq = freqFreqMap[val];
            if (crrFreq <= 1) {
                continue;
            }

            pair <int, int> singleCharDeletionResult = deleteSingleCharToMakeItsFreqUnique(freqFreqMap, val);
            numDeletions += singleCharDeletionResult.first;

            int newFreq = freqFreqMap[val];
            if (newFreq > 1) {
                valsToDecreaseFreq.push(val);
            }
        }

        return numDeletions;
    }

    int deleteAllCharsOfAllFreqsToMakeTheirFreqsUnique(unordered_map<int, int>& freqFreqMap) {
        int numDeletions = 0;

        do {
            int val = findValWithFreqGreaterThan1(freqFreqMap);

            if (val < 1) {
                // all characters now have unique frequencies
                break;
            } else {
                // found a frequency shared by multiple characters
                numDeletions += deleteAllCharsOfGivenFreqToMakeTheirFreqsUnique(freqFreqMap, val);
            }
        } while (true);

        return numDeletions;
    }

public:
    friend class SolutionTest;

    int minDeletions(string s) {
        vector <int> charFreqVec = createCharFreqVec(s);
        unordered_map<int, int> freqFreqMap = createFreqFreqMap(charFreqVec);

        return deleteAllCharsOfAllFreqsToMakeTheirFreqsUnique(freqFreqMap);
    }
};

class SolutionTest {
public:
    void testCreateCharFreqVec() {
        Solution soln = Solution();
        string strIn;
        vector <int> charFreqVecOutExpected(MAX_CHAR + 1, 0);
        vector <int> charFreqVecOutComputed;

        strIn = "aab";
        fill(charFreqVecOutExpected.begin(), charFreqVecOutExpected.end(), 0);
        charFreqVecOutExpected['a'] = 2;
        charFreqVecOutExpected['b'] = 1;
        charFreqVecOutComputed = soln.createCharFreqVec(strIn);
        assert(charFreqVecOutExpected == charFreqVecOutComputed);

        strIn = "aaabbbcc";
        fill(charFreqVecOutExpected.begin(), charFreqVecOutExpected.end(), 0);
        charFreqVecOutExpected['a'] = 3;
        charFreqVecOutExpected['b'] = 3;
        charFreqVecOutExpected['c'] = 2;
        charFreqVecOutComputed = soln.createCharFreqVec(strIn);
        assert(charFreqVecOutExpected == charFreqVecOutComputed);

        strIn = "ceabaacb";
        fill(charFreqVecOutExpected.begin(), charFreqVecOutExpected.end(), 0);
        charFreqVecOutExpected['a'] = 3;
        charFreqVecOutExpected['b'] = 2;
        charFreqVecOutExpected['c'] = 2;
        charFreqVecOutExpected['e'] = 1;
        charFreqVecOutComputed = soln.createCharFreqVec(strIn);
        assert(charFreqVecOutExpected == charFreqVecOutComputed);
    }

    void testCreateFreqFreqMap() {
        Solution soln = Solution();
        string strIn;
        vector <int> charFreqVecIn;
        unordered_map<int, int> freqFreqMapOutExpected;
        unordered_map<int, int> freqFreqMapOutComputed;

        strIn = "aab";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapOutExpected = {
            {1, 1},
            {2, 1}
        };
        freqFreqMapOutComputed = soln.createFreqFreqMap(charFreqVecIn);
        assert(freqFreqMapOutExpected == freqFreqMapOutComputed);

        strIn = "aaabbbcc";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapOutExpected = {
            {3, 2},
            {2, 1}
        };
        freqFreqMapOutComputed = soln.createFreqFreqMap(charFreqVecIn);
        assert(freqFreqMapOutExpected == freqFreqMapOutComputed);

        strIn = "ceabaacb";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapOutExpected = {
            {3, 1},
            {2, 2},
            {1, 1}
        };
        freqFreqMapOutComputed = soln.createFreqFreqMap(charFreqVecIn);
        assert(freqFreqMapOutExpected == freqFreqMapOutComputed);
    }

    void testDeleteSingleCharToMakeItsFreqUnique() {
        Solution soln = Solution();
        string strIn;
        vector <int> charFreqVecIn;
        unordered_map<int, int> freqFreqMapIn;
        int charFreqIn;
        unordered_map<int, int> freqFreqMapOutExpected;
        pair <int, int> resultOutExpected;
        pair <int, int> resultOutComputed;

        strIn = "aab";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapIn = soln.createFreqFreqMap(charFreqVecIn);
        charFreqIn = 1;
        // freqFreqMapOutExpected = {
        //     {2, 1},
        //     {1, 1}
        // };
        freqFreqMapOutExpected = {
            {2, 1},
            {1, 1}
        };
        resultOutExpected = {0, 1};
        resultOutComputed = soln.deleteSingleCharToMakeItsFreqUnique(freqFreqMapIn, charFreqIn);
        assert(freqFreqMapOutExpected == freqFreqMapIn);
        assert(resultOutExpected == resultOutComputed);

        strIn = "aaabbbcc";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapIn = soln.createFreqFreqMap(charFreqVecIn);
        charFreqIn = 3;
        // freqFreqMapOutExpected = {
        //     {3, 2},
        //     {2, 1}
        // };
        freqFreqMapOutExpected = {
            {3, 1},
            {2, 1},
            {1, 1}
        };
        resultOutExpected = {2, 1};
        resultOutComputed = soln.deleteSingleCharToMakeItsFreqUnique(freqFreqMapIn, charFreqIn);
        assert(freqFreqMapOutExpected == freqFreqMapIn);
        assert(resultOutExpected == resultOutComputed);

        // soln.enableDebug();
        strIn = "ceabaacb";
        charFreqVecIn = soln.createCharFreqVec(strIn);
        freqFreqMapIn = soln.createFreqFreqMap(charFreqVecIn);
        charFreqIn = 2;
        // freqFreqMapOutExpected = {
        //     {3, 1},
        //     {2, 2},
        //     {1, 1}
        // };
        freqFreqMapOutExpected = {
            {3, 1},
            {2, 1},
            {1, 1}
        };
        resultOutExpected = {2, 0};
        resultOutComputed = soln.deleteSingleCharToMakeItsFreqUnique(freqFreqMapIn, charFreqIn);
        // soln.showMap(freqFreqMapIn, "freqMapOutComputed (actually freqMapIn)");
        assert(freqFreqMapOutExpected == freqFreqMapIn);
        assert(resultOutExpected == resultOutComputed);
        // soln.disableDebug();
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateCharFreqVec();
    solnTest.testCreateFreqFreqMap();
    solnTest.testDeleteSingleCharToMakeItsFreqUnique();

    return 0;
}
