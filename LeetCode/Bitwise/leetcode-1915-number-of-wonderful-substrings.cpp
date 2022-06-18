// LeetCode-1915: https://leetcode.com/problems/number-of-wonderful-substrings/
// certainly not a medium problem; more like medium-hard / hard
// CodingForDummies: https://www.youtube.com/watch?v=TTFrsi6iDog

#include <string>
#include <unordered_map>
#include <cassert>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'j'

class Solution {
private:
    inline int flipKthBit(int num, int k) {
        // https://stackoverflow.com/q/18247126/3679900
        return num ^ (1 << k);
    }

    inline int flipCharBit(int num, char ch) {
        return flipKthBit(num, ch - BEGIN_CHAR);
    }

    // unused fn
    inline bool isPowerOf2(int num) {
        // https://stackoverflow.com/a/600306/3679900
        return (num != 0) && ((num ^ (num - 1)) == 0);
    }

    inline int countChar(int mask, char ch) {
        return flipCharBit(mask, ch);
    }

public:
    friend class SolutionTest;

    long long wonderfulSubstrings(string word) {
        int mask = 0;
        unordered_map<int, int> maskFreqMap = {{0, 1}};

        long long numWonderSubstrs = 0;

        for (int i = 0; i < word.size(); i++) {
            char iCh = word.at(i);
            mask = countChar(mask, iCh);

            // count same mask freqs: all substrings ending at i having all even char freqs
            numWonderSubstrs += maskFreqMap[mask];

            // count 1-char diff freqs: all substrings ending at i having just one char with odd freq
            for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
                numWonderSubstrs += maskFreqMap[flipCharBit(mask, ch)];
            }

            // update mask freq map
            maskFreqMap[mask]++;
        }

        return numWonderSubstrs;
    }
};

class SolutionTest {
public:
    void testFlipKthBit() {
        Solution soln = Solution();
        int numIn, kIn;
        int numOutExpected, numOutComputed;

        numIn = 0;
        kIn = 0;
        numOutExpected = 1;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);

        numIn = 0;
        kIn = 1;
        numOutExpected = 2;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);

        numIn = 5;
        kIn = 0;
        numOutExpected = 4;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);

        numIn = 5;
        kIn = 1;
        numOutExpected = 7;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);

        numIn = 5;
        kIn = 2;
        numOutExpected = 1;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);

        numIn = 5;
        kIn = 3;
        numOutExpected = 13;
        numOutComputed = soln.flipKthBit(numIn, kIn);
        assert(numOutExpected == numOutComputed);
    }

    void testCountChar() {
        Solution soln = Solution();
        int maskIn;
        char chIn;
        int maskOutExpected, maskOutComputed;

        maskIn = 0;
        chIn = 'a';
        maskOutExpected = 1;
        maskOutComputed = soln.countChar(maskIn, chIn);
        assert(maskOutExpected == maskOutComputed);

        maskIn = 0;
        chIn = 'b';
        maskOutExpected = 2;
        maskOutComputed = soln.countChar(maskIn, chIn);
        assert(maskOutExpected == maskOutComputed);

        maskIn = 0;
        chIn = 'c';
        maskOutExpected = 4;
        maskOutComputed = soln.countChar(maskIn, chIn);
        assert(maskOutExpected == maskOutComputed);

        maskIn = 5;
        chIn = 'e';
        maskOutExpected = 21;
        maskOutComputed = soln.countChar(maskIn, chIn);
        assert(maskOutExpected == maskOutComputed);

        maskIn = 21;
        chIn = 'e';
        maskOutExpected = 5;
        maskOutComputed = soln.countChar(maskIn, chIn);
        assert(maskOutExpected == maskOutComputed);
    }

    void testWonderfulSubstrings() {
        Solution soln = Solution();
        string wordIn;
        long long countOutExpected, countOutComputed;

        wordIn = "abc";
        countOutExpected = 3;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "aba";
        countOutExpected = 4;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "aabb";
        countOutExpected = 9;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "he";
        countOutExpected = 2;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "j";
        countOutExpected = 1;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "jj";
        countOutExpected = 3;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);

        wordIn = "jje";
        countOutExpected = 5;
        countOutComputed = soln.wonderfulSubstrings(wordIn);
        assert(countOutExpected == countOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFlipKthBit();
    solnTest.testCountChar();
    solnTest.testWonderfulSubstrings();

    return 0;
}
