// LeetCode-2414: https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/

#include <string>
#include <cassert>

#define MAX_CHAR 'z'

using namespace std;

class Solution {
private:
    string str;

    void init(string& str) {
        this->str = str;
    }

    bool areConsecutiveChars(char smallerChar, char biggerChar) {
        return ((int)(biggerChar - smallerChar)) == 1;
    }

    int consumeConsecutiveChars(int beginIdx) {
        int len = str.size();
        int crrIdx = beginIdx;

        while ((crrIdx < (len - 1)) && areConsecutiveChars(str.at(crrIdx), str.at(crrIdx + 1))) {
            // consume characters till they are consecutive
            crrIdx++;
        }

        return crrIdx;
    }

public:
    friend class SolutionTest;

    int longestContinuousSubstring(string s) {
        init(s);

        int len = s.size();
        if (len <= 1) {
            return len;
        }

        int longestSeqLen = 1;

        for (int beginIdx = 0; beginIdx < len;) {
            // consume continuous sequence of consecutive chars starting at i
            int endIdx = consumeConsecutiveChars(beginIdx);
            // calculate length of current sequence of consecutive chars
            int crrSeqLen = (endIdx - beginIdx) + 1;

            // update length of max sequence of consecutive chars seen so far
            longestSeqLen = max(longestSeqLen, crrSeqLen);

            beginIdx = endIdx + 1;
        }

        return longestSeqLen;
    }
};

class SolutionTest {
public:
    void testConsumeConsecutiveChars() {
        string strIn;
        int beginIdxIn;
        int outExpected, outComputed;
        Solution soln = Solution();

        strIn = "abacaba";
        beginIdxIn = 0;
        outExpected = 1;
        soln.init(strIn);
        outComputed = soln.consumeConsecutiveChars(beginIdxIn);
        assert(outComputed == outExpected);

        strIn = "e";
        beginIdxIn = 0;
        outExpected = 0;
        soln.init(strIn);
        outComputed = soln.consumeConsecutiveChars(beginIdxIn);
        assert(outComputed == outExpected);

        strIn = "ef";
        beginIdxIn = 0;
        outExpected = 1;
        soln.init(strIn);
        outComputed = soln.consumeConsecutiveChars(beginIdxIn);
        assert(outComputed == outExpected);

        strIn = "ef";
        beginIdxIn = 1;
        outExpected = 1;
        soln.init(strIn);
        outComputed = soln.consumeConsecutiveChars(beginIdxIn);
        assert(outComputed == outExpected);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testConsumeConsecutiveChars();

    return 0;
}
