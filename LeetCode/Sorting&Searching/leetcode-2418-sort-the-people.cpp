// LeetCode-2418: https://leetcode.com/problems/sort-the-people/

#include <vector>Z
#include <algorithm>

using namespace std;

class Solution {
private:
    vector <pair <int, string>> zipVecs(vector <string>& vecStr, vector <int>& vecInt) {
        int len = vecStr.size();
        vector <pair <int, string>> zippedVec(len);

        for (int i = 0; i < len; i++) {
            zippedVec[i] = {vecInt[i], vecStr[i]};
        }

        return zippedVec;
    }

    vector <string> getStrVec(vector <pair <int, string>>& zippedVec) {
        int len = zippedVec.size();
        vector <string> vecStr(len);

        int i = 0;
        for (auto it : zippedVec) {
            vecStr[i++] = it.second;
        }

        return vecStr;
    }

public:
    vector <string> sortPeople(vector <string>& names, vector <int>& heights) {
        vector <pair <int, string>> zippedVec = zipVecs(names, heights);
        sort(zippedVec.begin(), zippedVec.end(), greater <>());
        return getStrVec(zippedVec);
    }
};
