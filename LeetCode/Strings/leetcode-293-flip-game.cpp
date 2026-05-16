// LeetCode-293: https://leetcode.com/problems/flip-game/
// Code almost entirely written by Amazon Q (IntelliJ / CLion plugin)

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        vector<string> res;

        for (int i = 0; i + 1 < (int)currentState.size(); i++) {
            if (currentState[i] == '+' && currentState[i + 1] == '+') {
                currentState[i] = currentState[i + 1] = '-';
                res.push_back(currentState);

                currentState[i] = currentState[i + 1] = '+';
            }
        }

        return res;
    }
};
