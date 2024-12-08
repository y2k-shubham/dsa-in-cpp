// LeetCode-2053: https://leetcode.com/problems/kth-distinct-string-in-an-array/

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set <string> findUniqueStrs(vector <string>& arr) {
        unordered_set <string> uniqueStrs(arr.begin(), arr.end());
        unordered_map <string, int> freqMap;
        for (string str : arr) {
            freqMap[str]++;

            if (freqMap[str] > 1) {
                uniqueStrs.erase(str);
            }
        }

        return uniqueStrs;
    }

    string findKthUniqueStr(vector <string>& arr, int k, unordered_set <string>& uniqueStrs) {
        int idx = 0;
        for (string str : arr) {
            if (uniqueStrs.find(str) != uniqueStrs.end()) {
                idx++;

                if (idx == k) {
                    return str;
                }
            }
        }

        return "";
    }

public:
    string kthDistinct(vector <string>& arr, int k) {
        unordered_set <string> uniqueStrs = findUniqueStrs(arr);
        return findKthUniqueStr(arr, k, uniqueStrs);
    }
};
