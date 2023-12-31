// LeetCode-91: https://leetcode.com/problems/decode-ways/

#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

#define FIRST_ALPHABET 'A'
#define FIRST_DIG_CHAR '0'
#define NULL_CHAR '\0'

class Solution {
private:
    inline char getChar(int num) {
        if (num >= 1 && num <= 26) {
            return FIRST_ALPHABET + (num - 1);
        }

        return NULL_CHAR;
    }

    inline int extractNum(string& str, int idx, int numDigits) {
        if (numDigits == 1) {
            return str.at(idx) - FIRST_DIG_CHAR;
        }

        return stoi(str.substr(idx, numDigits));
    }

public:
    friend class SolutionTest;

    int numDecodings(string s) {

    }
};

class SolutionTest {
public:
};

int main() {
    SolutionTest solnTest = SolutionTest();



    return 0;
}
