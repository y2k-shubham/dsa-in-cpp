// LeetCode-781: https://leetcode.com/problems/rabbits-in-forest/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <int, int> buildFreqMap(vector <int>& vec) {
        unordered_map <int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    int calcNumRabbits(unordered_map <int, int>& freqMap) {
        int numRabbits = 0;

        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            int groupSize = it->first + 1;
            int reportedFreq = it->second;

            int numGroups = reportedFreq / groupSize;

            if ((reportedFreq % groupSize) != 0) {
                numGroups++;
            }

            numRabbits += numGroups * groupSize;
        }

        return numRabbits;
    }

public:
    int numRabbits(vector <int>& answers) {
        if (answers.empty()) {
            return 0;
        }
        if (answers.size() == 1) {
            return answers[0] + 1;
        }

        unordered_map <int, int> freqMap = buildFreqMap(answers);
        return calcNumRabbits(freqMap);
    }
};
