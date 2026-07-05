// LeetCode-604: https://leetcode.com/problems/design-compressed-string-iterator/
// Took help of Kiro to debug and fix

#include <string>

using namespace std;

#define CHAR_SPACE ' '

class StringIterator {
private:
    string compressedString;
    char crrChar;
    int crrCharFreq;
    int crrIdx;

    /**
     * Parse the multi-digit number starting at position idx.
     * Returns {frequency, number of digits parsed}.
     *
     * Note: This function was entirely written by Kiro.
     */
    pair<int, int> parseFreq(int idx) {
        size_t digits = 0;
        // stoi parses consecutive digits from the substring and writes the count
        // of characters consumed into 'digits' (output param passed by pointer)
        int freq = stoi(compressedString.substr(idx), &digits);

        return {freq, (int)digits};
    }

public:
    StringIterator(string compressedString) {
        this->compressedString = compressedString;
        this->crrIdx = 0;
        this->crrChar = CHAR_SPACE;
        this->crrCharFreq = 0;
    }

    char next() {
        if (!hasNext()) {
            return CHAR_SPACE;
        }

        // if current char is fully consumed, read the next char and its frequency
        if (crrCharFreq == 0) {
            // read current character
            crrChar = compressedString[crrIdx];

            // read frequency of current character
            auto [freq, digits] = parseFreq(crrIdx + 1);
            crrCharFreq = freq;

            // advance iterator past char + it's frequency
            crrIdx += 1 + digits;
        }

        // consume and return crrChar
        crrCharFreq--;
        return crrChar;
    }

    bool hasNext() {
        return crrCharFreq > 0 || crrIdx < (int)compressedString.length();
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
