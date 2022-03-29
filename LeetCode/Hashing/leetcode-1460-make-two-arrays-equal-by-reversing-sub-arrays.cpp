// LeetCode-1460: https://leetcode.com/problems/make-two-arrays-equal-by-reversing-sub-arrays/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> buildFreqMap(vector<int> &vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    bool compareMaps(unordered_map<int, int> &refMap, unordered_map<int, int> &cmpMap) {
        for (unordered_map<int, int>::iterator it = refMap.begin(); it != refMap.end(); it++) {
            int val = it->first;
            int freq = it->second;

            if ((cmpMap.find(val) == cmpMap.end()) || (cmpMap[val] != freq)) {
                return false;
            }
        }

        return true;
    }

    bool areEqual(unordered_map<int, int> &map1, unordered_map<int, int> &map2) {
        return compareMaps(map1, map2) && compareMaps(map2, map1);
    }

public:
    bool canBeEqual(vector<int> &target, vector<int> &arr) {
        unordered_map<int, int> freqMapTarget = buildFreqMap(target);
        unordered_map<int, int> freqMapArr = buildFreqMap(arr);

        return areEqual(freqMapTarget, freqMapArr);
    }
};

