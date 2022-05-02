// LeetCode-47: https://leetcode.com/problems/permutations-ii///
// NeetCode: https://www.youtube.com/watch?v=qhBVWf0YafA&t=354s

// not as easy as it may appear to be

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    void permuteRec(
            unordered_map<int, int>& freqMap,
            vector<int>& crrPerm,
            int idx,
            vector<vector<int> >& permutations
    ) {
        int len = crrPerm.size();
        if (idx > len) {
            return;
        }
        if (idx == len) {
            permutations.push_back(crrPerm);
            return;
        }

        for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            // read current element
            int crrEle = it->first;
            // read it's frequency
            int crrFreq = it->second;
            if (crrFreq <= 0) {
                // if frequency is zero, skip
                continue;
            }

            // decrease frequency of current element
            // to indicate that we've used one occurrence of it
            freqMap[crrEle]--;

            // this should not be done as it results in seg-fault
            // (we can't remove keys from map while iterating over it)
            // if (freqMap[crrEle] == 0) {
            //     freqMap.erase(crrEle);
            // }

            // assign current element in vector and permute
            crrPerm[idx] = crrEle;
            permuteRec(freqMap, crrPerm, idx + 1, permutations);

            // re-increase frequency while back-tracking
            freqMap[crrEle]++;
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return {nums};
        }

        unordered_map<int, int> freqMap = buildFreqMap(nums);

        vector<vector<int>> permutations;
        vector<int> crrPerm(len);
        permuteRec(freqMap, crrPerm, 0, permutations);

        return permutations;
    }
};
