// LeetCode-3163: https://leetcode.com/problems/string-compression-iii

#include <string>
#include <sstream>
#include <cassert>

using namespace std;

#define MAX_LEN 9

class Solution {
private:
    bool debug = false;

    int swallowSameCharactersPrefix(string& word, int idxLo) {
        int len = word.size();
        if (idxLo >= len) {
            return len;
        }

        char ch = word.at(idxLo);
        int i;
        for (
                i = idxLo;
                (i < len) && (i - idxLo + 1 <= MAX_LEN);
                i++
                ) {
            if (word.at(i) != ch) {
                return i;
            }
        }

        if (i - idxLo + 1 > MAX_LEN) {
            return idxLo + MAX_LEN;
        }

        return len;
    }

public:
    friend class SolutionTest;

    string compressedString(string word) {
        ostringstream oss;

        int idxLo = 0;
        int len = word.size();
        while (idxLo < len) {
            char ch = word.at(idxLo);
            int newIdxLo = swallowSameCharactersPrefix(word, idxLo);
            int numChars = newIdxLo - idxLo;

            oss << numChars << ch;

            idxLo = newIdxLo;
        }

        return oss.str();
    }
};

class SolutionTest {
public:
    void testSwallowSameCharactersPrefix() {
        Solution soln = Solution();
        string word;
        int idxLo;
        int outExpected, outComputed;

        word = "aaa";
        idxLo = 0;
        outExpected = 3;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaa";
        idxLo = 1;
        outExpected = 3;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaa";
        idxLo = 2;
        outExpected = 3;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaa";
        idxLo = 3;
        outExpected = 3;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 0;
        outExpected = 1;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 1;
        outExpected = 2;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 2;
        outExpected = 3;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 3;
        outExpected = 4;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 4;
        outExpected = 5;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "abcde";
        idxLo = 5;
        outExpected = 5;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaabb";
        idxLo = 0;
        outExpected = 7;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaaabb";
        idxLo = 0;
        outExpected = 8;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaaaabb";
        idxLo = 0;
        outExpected = 9;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaabb";
        idxLo = 0;
        outExpected = 9;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaaaabb";
        idxLo = 0;
        outExpected = 9;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaaaaaabb";
        idxLo = 0;
        outExpected = 9;
        outComputed = soln.swallowSameCharactersPrefix(word, idxLo);
        assert(outExpected == outComputed);

        printf("[testSwallowSameCharactersPrefix] All test-cases passed\n");
    }

    void testCompressedString() {
        Solution soln = Solution();
        string word;
        string outExpected, outComputed;

        word = "abcde";
        outExpected = "1a1b1c1d1e";
        outComputed = soln.compressedString(word);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaaaaaabb";
        outExpected = "9a5a2b";
        outComputed = soln.compressedString(word);
        assert(outExpected == outComputed);

        word = "aaaaaaaaabb";
        outExpected = "9a2b";
        outComputed = soln.compressedString(word);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaabb";
        outExpected = "9a1a2b";
        outComputed = soln.compressedString(word);
        assert(outExpected == outComputed);

        word = "aaaaaaaaaaabb";
        outExpected = "9a2a2b";
        outComputed = soln.compressedString(word);
        assert(outExpected == outComputed);

        printf("[testCompressedString] All test-cases passed\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSwallowSameCharactersPrefix();
    solnTest.testCompressedString();

    return 0;
}
