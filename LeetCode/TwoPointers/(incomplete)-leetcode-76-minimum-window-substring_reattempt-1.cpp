// https://leetcode.com/problems/minimum-window-substring/
// incomplete
// Uses C++14 syntax

#include <string>
#include <vector>
#include <memory>
#include <climits>
#include <cassert>

using namespace std;

#define CHAR_SET_SIZE 123

class CharFreqStore {
private:
    vector<int> freqVec;
    int numUniqueChars;

public:
    int addChar(char ch) {
        freqVec[ch]++;
        if (freqVec[ch] == 1) {
            numUniqueChars++;
        }

        return freqVec[ch];
    }

    int removeChar(char ch) {
        freqVec[ch]--;
        if (freqVec[ch] == 0) {
            numUniqueChars--;
        }

        return freqVec[ch];
    }

    int getFreq(char ch) const {
        return freqVec[ch];
    }

    int getNumUniqueChars() const {
        return numUniqueChars;
    }

    CharFreqStore() {
        freqVec.resize(CHAR_SET_SIZE, 0);
    }

    static CharFreqStore fromString(const string& str) {
        CharFreqStore store;
        for (char ch : str) {
            store.addChar(ch);
        }
        return store;
    }

    static bool equals(const CharFreqStore& a, const CharFreqStore& b) {
        return (a.numUniqueChars == b.numUniqueChars) && (a.freqVec == b.freqVec);
    }
};

class CharFreqSubStrCheckStore {
private:
    const CharFreqStore tStrFreqStore;
    CharFreqStore sStrFreqStore;
    int numSatisfyingChars;

public:
    bool addChar(char ch) {
        int newFreq = sStrFreqStore.addChar(ch);
        if (newFreq == tStrFreqStore.getFreq(ch)) {
            numSatisfyingChars++;
        }


        return isSubStrSatisfying();
    }

    bool removeChar(char ch) {
        int newFreq = sStrFreqStore.removeChar(ch);
        if (newFreq == (tStrFreqStore.getFreq(ch) - 1)) {
            numSatisfyingChars--;
        }

        return isSubStrSatisfying();
    }

    bool isSubStrSatisfying() const {
        return numSatisfyingChars == tStrFreqStore.getNumUniqueChars();
    }

    CharFreqSubStrCheckStore(const CharFreqStore& tStrFreqStore)
        : tStrFreqStore(tStrFreqStore) {
        sStrFreqStore = CharFreqStore();
    }
};

class Solution {
private:
    unique_ptr<CharFreqSubStrCheckStore> tInSubStrOfSCheckStore;
    string s;
    int sLen;
    // at any point of time our current window in s would be [iLo .. iHi] (both inclusive)
    int iLo, iHi;
    int minWindowSize, minWindowILo, minWindowIHi;

    bool moveIHiTillNotSatisfying() {
        if ((iHi >= (sLen - 1)) || tInSubStrOfSCheckStore->isSubStrSatisfying()) {
            // can't / need-not move any further, so return false
            return false;
        }

        if (iLo == INT_MIN) {
            // initial state
            iLo = 0;
        }

        do {
            // advance iHi and then add iHi char
            iHi++;
            if (tInSubStrOfSCheckStore->addChar(s[iHi])) {
                // if satisfying now then break
                break;
            }
        } while ((iHi < (sLen - 1)) && !tInSubStrOfSCheckStore->isSubStrSatisfying());

        if (tInSubStrOfSCheckStore->isSubStrSatisfying()) {
            // calculate and update minWindowSize if required
            int crrWindowSize = iHi - iLo + 1;
            if (crrWindowSize < minWindowSize) {
                minWindowSize = crrWindowSize;
                minWindowILo = iLo;
                minWindowIHi = iHi;
            }
        }

        // return true since we moved iHi
        return true;
    }

    bool moveILoTillSatisfying() {
        if ((iLo == iHi) || !tInSubStrOfSCheckStore->isSubStrSatisfying()) {
            // can't / need-not move any further, so return false
            return false;
        }

        while ((iLo < iHi) && tInSubStrOfSCheckStore->isSubStrSatisfying()) {
            // calculate and update minWindowSize if required
            int crrWindowSize = iHi - iLo + 1;
            if (crrWindowSize < minWindowSize) {
                minWindowSize = crrWindowSize;
                minWindowILo = iLo;
                minWindowIHi = iHi;
            }

            // remove iLo char and advance iLo
            tInSubStrOfSCheckStore->removeChar(s[iLo]);
            iLo++;
        }

        // return true since we moved iLo
        return true;
    }

public:
    string minWindow(string s, string t) {
        this->s = s;
        sLen = s.size();
        int tLen = t.size();
        if (sLen < tLen) {
            // s being smaller than t obviously can't contain it
            return "";
        }

        CharFreqStore tFreqStore = CharFreqStore::fromString(t);
        if (sLen == tLen) {
            // since lengths are equal
            CharFreqStore sFreqStore = CharFreqStore::fromString(s);
            // check if s and t have same chars
            if (CharFreqStore::equals(tFreqStore, sFreqStore)) {
                return s;
            } else {
                return "";
            }
        }

        tInSubStrOfSCheckStore = make_unique<CharFreqSubStrCheckStore>(tFreqStore);

        while (true) {
            bool iHiMoved = moveIHiTillNotSatisfying();
            bool iLowMoved = moveILoTillSatisfying();

            if (!!iHiMoved && !iLowMoved) {
                // if none of them could be moved, then we are done
                break;
            }
        }

        if (minWindowSize == INT_MAX) {
            return "";
        } else {
            return s.substr(minWindowILo, minWindowSize);
        }
    }

    Solution() {
        iLo = iHi = INT_MIN;
        sLen = INT_MIN;
        minWindowSize = INT_MAX;
        minWindowILo = minWindowIHi = INT_MIN;
    }

    friend class SolutionTest;
};

class SolutionTest {
public:
    void testMinWindow() {
        Solution solution;

        string s, t;
        string actual, expected;

        s = "ADOBECODEBANC";
        t = "ABC";
        expected = "BANC";
        actual = solution.minWindow(s, t);
        assert(actual == expected);

        s = "a";
        t = "a";
        expected = "a";
        actual = solution.minWindow(s, t);
        assert(actual == expected);

        s = "a";
        t = "aa";
        expected = "";
        actual = solution.minWindow(s, t);
        assert(actual == expected);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinWindow();

    return 0;
}
