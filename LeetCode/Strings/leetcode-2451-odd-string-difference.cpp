// LeetCode-2451: https://leetcode.com/problems/odd-string-difference

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
private:
    vector <int> getDiffVec(string str) {
        int len = str.size();

        vector <int> diffVec(len - 1);
        for (int i = 0; i < len - 1; i++) {
            diffVec[i] = str[i + 1] - str[i];
        }

        return diffVec;
    }

    string getDiffVecStr(vector <int> diffVec) {
        stringstream ss;
        for (auto diff : diffVec) {
            ss << diff << ",";
        }

        return ss.str();
    }

    string getDiffStr(string str) {
        vector <int> diffVec = getDiffVec(str);
        return getDiffVecStr(diffVec);
    }

public:
    string oddString(vector <string>& words) {
        // calculate frequencies of diff arrays (in string form) of words
        unordered_map <string, int> freqMap;
        unordered_map <string, string> diffStrToStrMap;
        for (auto word : words) {
            string diffStr = getDiffStr(word);

            freqMap[diffStr]++;
            diffStrToStrMap[diffStr] = word;
        }

        // find diff array (in string form) having frequency of 1
        string wordWithFreq1;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second == 1) {
                return diffStrToStrMap[it->first];
            }
        }

        return words[0];
    }
};
