// LeetCode-2023: https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/
// please skip

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    // suffix match: https://stackoverflow.com/a/2072890/3679900
    inline bool endsWith(std::string const& value, std::string const& ending) {
        if (ending.size() > value.size()) {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

public:
    int numOfPairs(vector<string>& nums, string target) {
        int targetLen = target.size();
        int numPairs = 0;

        for (int i = 0; i < nums.size(); i++) {
            string iStr = nums[i];

            int iStrLen = iStr.size();
            if (iStrLen >= targetLen) {
                continue;
            }

            // prefix match: https://stackoverflow.com/a/22054031/3679900
            bool isIStrPrefix = target.compare(0, iStrLen, iStr) == 0;
            if (!isIStrPrefix) {
                continue;
            }

            for (int j = 0; j < nums.size(); j++) {
                if (i == j) {
                    continue;
                }

                string jStr = nums[j];

                int jStrLen = jStr.size();
                if ((iStrLen + jStrLen) != targetLen) {
                    continue;
                }

                bool isJStrSuffix = endsWith(target, jStr);
                if (isJStrSuffix) {
                    ++numPairs;
                }
            }
        }

        return numPairs;
    }
};
