// LeetCode-806: https://leetcode.com/problems/number-of-lines-to-write-string/

#include <string>
#include <vector>

using namespace std;

#define BEGIN_CHAR 'a'
#define AVAILABLE_PIXELS_IN_LINE 100

class Solution {
public:
    vector <int> numberOfLines(vector <int>& widths, string s) {
        int numLines = 1;
        int usedPixelsInLine = 0;
        for (char ch : s) {
            int crrCharPixelWidth = widths[ch - BEGIN_CHAR];
            usedPixelsInLine += crrCharPixelWidth;

            if (usedPixelsInLine > AVAILABLE_PIXELS_IN_LINE) {
                numLines++;
                usedPixelsInLine = crrCharPixelWidth;
            }
        }

        return {numLines, usedPixelsInLine};
    }
};
