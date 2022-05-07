// LeetCode-187: https://leetcode.com/problems/repeated-dna-sequences/

// the idea of representing substring with an integer (along with constant-time update of representation
// as the window slides) is inspired by Rabin Karp Algorithm

#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>

using namespace std;

#define SEQ_LEN 10
#define MIN_FREQ 2

class Solution {
private:
    unordered_map<char, int> alphaDigMap = {
            {'A', 1},
            {'C', 2},
            {'G', 3},
            {'T', 4}
    };
    unordered_map<int, char> digAlphaMap = {
            {1, 'A'},
            {2, 'C'},
            {3, 'G'},
            {4, 'T'}
    };

    long long buildNumRepr(string& str, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return 0;
        }

        lo = max(0, lo);
        hi = min(((int) str.size()) - 1, hi);

        long long num = 0;
        for (int i = lo; i <= hi; i++) {
            char ch = str.at(i);
            int dig = alphaDigMap[ch];

            num *= 10;
            num += dig;
        }

        return num;
    }

    string buildStrRepr(long long num) {
        ostringstream oss;

        while (num > 0) {
            int dig = num % 10;
            num /= 10;

            char ch = digAlphaMap[dig];
            oss << ch;
        }

        string str = oss.str();
        reverse(str.begin(), str.end());

        return str;
    }

    long long updateNumRepr(
            string& str,
            int reprLen,
            int newHi,
            long long crrRepr
    ) {
        long long newRepr = crrRepr;

        int oldLo = newHi - reprLen;
        char oldCh = str.at(oldLo);
        int oldDig = alphaDigMap[oldCh];
        newRepr -= oldDig * ((long long) pow(10, reprLen - 1));

        char newCh = str.at(newHi);
        int newDig = alphaDigMap[newCh];
        newRepr *= 10;
        newRepr += newDig;

        return newRepr;
    }

    vector<long long> extractKeysWithValueAtLeast(unordered_map<long long, int>& freqMap, int minVal) {
        list<long long> keyList;

        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second >= minVal) {
                keyList.push_back(it->first);
            }
        }

        vector<long long> keyVec(keyList.begin(), keyList.end());
        return keyVec;
    }

    vector<string> convertValsToStr(vector<long long>& numKeyVec) {
        int len = numKeyVec.size();

        vector<string> strKeyVec(len);
        for (int i = 0; i < len; i++) {
            strKeyVec[i] = buildStrRepr(numKeyVec[i]);
        }

        return strKeyVec;
    }

    string stringRepr(vector<string>& vec) {
        int len = vec.size();
        if (len == 0) {
            return "";
        }
        if (len == 1) {
            return vec[0];
        }

        ostringstream oss;
        oss << vec[0];

        for (int i = 1; i < vec.size(); i++) {
            oss << ',' << vec[i];
        }

        return oss.str();
    }

public:
    friend class SolutionTest;

    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<long long, int> freqMap;

        // build frequency map of numeric-representations of each 10-length sequence
        long long numRepr = buildNumRepr(s, 0, SEQ_LEN - 1);
        freqMap[numRepr]++;
        for (int i = SEQ_LEN; i < s.size(); i++) {
            numRepr = updateNumRepr(s, SEQ_LEN, i, numRepr);
            freqMap[numRepr]++;
        }

        // extract representations having more than 1 occurrences
        vector<long long> multiOccurringReprs = extractKeysWithValueAtLeast(freqMap, MIN_FREQ);

        // convert num representations to string
        vector<string> multiOccurringSeqs = convertValsToStr(multiOccurringReprs);
        return multiOccurringSeqs;
    }
};

class SolutionTest {
public:
    void testNumRepr() {
        Solution soln = Solution();
        string strIn;
        int loIn, hiIn;
        long long outExpected, outComputed;

        strIn = "";
        loIn = 3;
        hiIn = 5;
        outExpected = 0;
        outComputed = soln.buildNumRepr(strIn, loIn, hiIn);
        assert(outExpected == outComputed);

        strIn = "ATCGCTCG";

        loIn = 0;
        hiIn = 0;
        outExpected = 1;
        outComputed = soln.buildNumRepr(strIn, loIn, hiIn);
        assert(outExpected == outComputed);

        loIn = 0;
        hiIn = 1;
        outExpected = 14;
        outComputed = soln.buildNumRepr(strIn, loIn, hiIn);
        assert(outExpected == outComputed);

        loIn = 0;
        hiIn = 2;
        outExpected = 142;
        outComputed = soln.buildNumRepr(strIn, loIn, hiIn);
        assert(outExpected == outComputed);

        loIn = 3;
        hiIn = 7;
        outExpected = 32423;
        outComputed = soln.buildNumRepr(strIn, loIn, hiIn);
        assert(outExpected == outComputed);
    }

    void testUpdatedNumRepr() {
        Solution soln = Solution();
        string strIn;
        int reprLenIn;
        int newHiIn;
        long long crrReprIn;
        long long updatedReprOutExpected, updatedReprOutComputed;

        strIn = "ATCGCTCG";
        reprLenIn = 4;

        crrReprIn = 1423;
        newHiIn = 4;
        updatedReprOutExpected = 4232;
        updatedReprOutComputed = soln.updateNumRepr(strIn, reprLenIn, newHiIn, crrReprIn);
        assert(updatedReprOutExpected == updatedReprOutComputed);

        crrReprIn = 4232;
        newHiIn = 5;
        updatedReprOutExpected = 2324;
        updatedReprOutComputed = soln.updateNumRepr(strIn, reprLenIn, newHiIn, crrReprIn);
        assert(updatedReprOutExpected == updatedReprOutComputed);

        crrReprIn = 2324;
        newHiIn = 6;
        updatedReprOutExpected = 3242;
        updatedReprOutComputed = soln.updateNumRepr(strIn, reprLenIn, newHiIn, crrReprIn);
        assert(updatedReprOutExpected == updatedReprOutComputed);
    }

    void testFindRepeatedDnaSequences() {
        Solution soln = Solution();
        string strIn;
        vector<string> seqsOutExpected;
        vector<string> seqsOutComputed;

        strIn = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        seqsOutExpected = {"AAAAACCCCC", "CCCCCAAAAA"};
        seqsOutComputed = soln.findRepeatedDnaSequences(strIn);
//        printf("expected = %s\n", soln.stringRepr(seqsOutExpected).c_str());
//        printf("computed = %s\n", soln.stringRepr(seqsOutComputed).c_str());
        assert(seqsOutExpected == seqsOutComputed);

        strIn = "AAAAAAAAAAAAA";
        seqsOutExpected = {"AAAAAAAAAA"};
        seqsOutComputed = soln.findRepeatedDnaSequences(strIn);
        assert(seqsOutExpected == seqsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testNumRepr();
    solnTest.testUpdatedNumRepr();
    solnTest.testFindRepeatedDnaSequences();

    return 0;
}
