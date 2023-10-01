// LeetCode-557: https://leetcode.com/problems/reverse-words-in-a-string-iii

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cctype>
#include <cassert>

using namespace std;

class Solution {
private:
    // this inline keyword had no effect on runtime
    inline pair <string, int> extractWhitespace(string& str, int iLo) {
        iLo = max(iLo, 0);

        int len = str.size();
        if (iLo >= len) {
            return {"", len};
        }
        if (!isspace(str.at(iLo))) {
            return {"", iLo};
        }

        ostringstream oss;
        int i = iLo;
        while ((i < len) && isspace(str.at(i))) {
            oss << str.at(i);
            i++;
        }

        return {oss.str(), i};
    }

    inline pair <string, int> extractNonWhitespace(string& str, int iLo) {
        iLo = max(iLo, 0);

        int len = str.size();
        if (iLo >= len) {
            return {"", len};
        }
        if (isspace(str.at(iLo))) {
            return {"", iLo};
        }

        ostringstream oss;
        int i = iLo;
        while ((i < len) && !isspace(str.at(i))) {
            oss << str.at(i);
            i++;
        }

        return {oss.str(), i};
    }

public:
    friend class SolutionTest;

    string reverseWords(string str) {
        ostringstream oss;

        int len = str.size();
        if (len <= 1) {
            return str;
        }

        int i = 0;
        while (i < len) {
            pair <string, int> whitespaceRes = extractWhitespace(str, i);
            if (whitespaceRes.second > i) {
                oss << whitespaceRes.first;
                i = whitespaceRes.second;
                continue;
            }

            pair <string, int> nonWhitespaceRes = extractNonWhitespace(str, i);
            if (nonWhitespaceRes.second > i) {
                std::reverse(nonWhitespaceRes.first.begin(), nonWhitespaceRes.first.end());
                oss << nonWhitespaceRes.first;
                i = nonWhitespaceRes.second;
                continue;
            }
        }

        return oss.str();
    }
};

class SolutionTest {
public:
    void testExtractWhitespace() {
        string str;
        int iLo;
        pair <string, int> outExpected, outComputed;
        Solution soln = Solution();

        str = "";
        iLo = -1;
        outExpected = {"", 0};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "";
        iLo = 0;
        outExpected = {"", 0};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "a";
        iLo = 0;
        outExpected = {"", 0};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " ";
        iLo = 0;
        outExpected = {" ", 1};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " g";
        iLo = 0;
        outExpected = {" ", 1};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "  g";
        iLo = 0;
        outExpected = {"  ", 2};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "  g";
        iLo = 1;
        outExpected = {" ", 2};
        outComputed = soln.extractWhitespace(str, iLo);
        assert(outExpected == outComputed);
    }

    void testExtractNonWhitespace() {
        string str;
        int iLo;
        pair <string, int> outExpected, outComputed;
        Solution soln = Solution();

        str = "";
        iLo = -1;
        outExpected = {"", 0};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "";
        iLo = 0;
        outExpected = {"", 0};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "a";
        iLo = 0;
        outExpected = {"a", 1};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " ";
        iLo = 0;
        outExpected = {"", 0};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " g";
        iLo = 0;
        outExpected = {"", 0};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " g";
        iLo = 1;
        outExpected = {"g", 2};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " gt ";
        iLo = 1;
        outExpected = {"gt", 3};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = " gt";
        iLo = 1;
        outExpected = {"gt", 3};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "gr ";
        iLo = 0;
        outExpected = {"gr", 2};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);

        str = "gr ";
        iLo = 1;
        outExpected = {"r", 2};
        outComputed = soln.extractNonWhitespace(str, iLo);
        assert(outExpected == outComputed);
    }

    void testReverseWords() {
        string strIn, strOutExpected, strOutComputed;
        Solution soln = Solution();

        strIn = "";
        strOutExpected = "";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = " ";
        strOutExpected = " ";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "f";
        strOutExpected = "f";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "f ";
        strOutExpected = "f ";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "fa";
        strOutExpected = "af";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "f a";
        strOutExpected = "f a";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "f ag";
        strOutExpected = "f ga";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "f  ag";
        strOutExpected = "f  ga";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "fr  a g";
        strOutExpected = "rf  a g";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "fr  ag";
        strOutExpected = "rf  ga";
        strOutComputed = soln.reverseWords(strIn);
        assert(strOutExpected == strOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testExtractWhitespace();
    solnTest.testExtractNonWhitespace();
    solnTest.testReverseWords();

    return 0;
}
