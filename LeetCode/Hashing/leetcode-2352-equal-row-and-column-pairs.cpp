// LeetCode-2352: https://leetcode.com/problems/equal-row-and-column/
// solution is accepted, but test-cases are broken (they were written assuming delimiter of "" empty string in 'vecToStr' function)

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
private:
    // convert vector<int> to string
    static string vecToStr(vector<int> &vec) {
        if (vec.empty()) {
            return "";
        }

        std::stringstream result;
        // IMPORTANT: its important for this question to have a comma as a delimiter
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(result, ","));
        return result.str();
    }

    // convert vector<vector<int>> to vector<string>
    vector<string> vecVecToVecStr(vector<vector<int>> &vecVec) {
        vector<string> result;
        for (int i = 0; i < vecVec.size(); i++) {
            result.push_back(vecToStr(vecVec[i]));
        }
        return result;
    }

    // convert vector<vector<int>> to vector<string> taking columns
    vector<string> vecVecToVecStrCol(vector<vector<int>> &vecVec) {
        if (vecVec.empty()) {
            return {};
        }
        if (vecVec[0].empty()) {
            return {""};
        }

        vector<string> result(vecVec[0].size());
        for (int i = 0; i < vecVec[0].size(); i++) {
            vector<int> col(vecVec.size());
            for (int j = 0; j < vecVec.size(); j++) {
                col[j] = vecVec[j][i];
            }
            result[i] = vecToStr(col);
        }
        return result;
    }

    // convert vector<string> to frequency map map<string, int>
    static unordered_map<string, int> vecStrToFreqMap(vector<string> &vecStr) {
        unordered_map<string, int> freqMap;
        for (int i = 0; i < vecStr.size(); i++) {
            freqMap[vecStr[i]]++;
        }
        return freqMap;
    }

    // find sum of frequencies of each string in vector in the freqMap
    static int sumFreq(vector<string> &vecStr, unordered_map<string, int> &freqMap) {
        int sum = 0;
        for (int i = 0; i < vecStr.size(); i++) {
            sum += freqMap[vecStr[i]];
        }
        return sum;
    }

public:
    friend class SolutionTest;

    int equalPairs(vector<vector<int>> &grid) {
        vector<string> rows = vecVecToVecStr(grid);
        vector<string> cols = vecVecToVecStrCol(grid);

        unordered_map<string, int> colsFreqMap = vecStrToFreqMap(cols);
        int sum = sumFreq(rows, colsFreqMap);

        return sum;
    }
};

class SolutionTest {
public:
    void testVecToStr() {
        Solution soln = Solution();

        vector<int> vec = {1, 2, 3, 4, 5};
        string str = soln.vecToStr(vec);
        assert(str == "1,2,3,4,5");

        vec = {1, 2, 3, 4, 5, 6};
        str = soln.vecToStr(vec);
        assert(str == "1,2,3,4,5,6");

        vec = {1};
        str = soln.vecToStr(vec);
        assert(str == "1");

        vec = {};
        str = soln.vecToStr(vec);
        assert(str == "");
    }

    void testVecVecToVecStr() {
        Solution soln = Solution();

        vector<vector<int>> vecVec = {{1, 2, 3, 4, 5},
                                      {1, 2, 3, 4, 5}};
        vector<string> vecStr = soln.vecVecToVecStr(vecVec);
        assert(vecStr.size() == 2);
        assert(vecStr[0] == "1,2,3,4,5");
        assert(vecStr[1] == "1,2,3,4,5");

        vecVec = {{1, 2, 3, 4, 5},
                  {1, 2, 3},
                  {4},
                  {}};
        vecStr = soln.vecVecToVecStr(vecVec);
        assert(vecStr.size() == 4);
        assert(vecStr[0] == "1,2,3,4,5");
        assert(vecStr[1] == "1,2,3");
        assert(vecStr[2] == "4");
        assert(vecStr[3] == "");

        vecVec = {{},
                  {},
                  {}};
        vecStr = soln.vecVecToVecStr(vecVec);
        assert(vecStr.size() == 3);
        assert(vecStr[0] == "");
        assert(vecStr[1] == "");
        assert(vecStr[2] == "");
    }

    void testVecVecToVecStrCol() {
        Solution soln = Solution();

        vector<vector<int>> vecVec = {{1, 2, 3, 4, 5},
                                      {1, 2, 3, 4, 5}};
        vector<string> vecStr = soln.vecVecToVecStrCol(vecVec);
        assert(vecStr.size() == 5);
        assert(vecStr[0] == "1,1");
        assert(vecStr[1] == "2,2");
        assert(vecStr[2] == "3,3");
        assert(vecStr[3] == "4,4");
        assert(vecStr[4] == "5,5");

        vecVec = {{3, 1, 6},
                  {8, 9, 3}};
        vecStr = soln.vecVecToVecStrCol(vecVec);
        assert(vecStr.size() == 3);
        assert(vecStr[0] == "3,8");
        assert(vecStr[1] == "1,9");
        assert(vecStr[2] == "6,3");
    }

    void testVecStrToFreqMap() {
        Solution soln = Solution();

        vector<string> vecStr = {"12345", "12345"};
        unordered_map<string, int> freqMap = soln.vecStrToFreqMap(vecStr);
        assert(freqMap.size() == 1);
        assert(freqMap["12345"] == 2);

        vecStr = {"12345", "123", "4", ""};
        freqMap = soln.vecStrToFreqMap(vecStr);
        assert(freqMap.size() == 4);
        assert(freqMap["12345"] == 1);
        assert(freqMap["123"] == 1);
        assert(freqMap["4"] == 1);
        assert(freqMap[""] == 1);

        vecStr = {"", "", ""};
        freqMap = soln.vecStrToFreqMap(vecStr);
        assert(freqMap.size() == 1);
        assert(freqMap[""] == 3);
    }

    void testSumFreq() {
        Solution soln = Solution();

        vector<string> vecStr = {"12345", "12345"};
        unordered_map<string, int> freqMap = {{"12345", 1},
                                              {"123",   1},
                                              {"4",     1},
                                              {"",      1}};
        int sum = soln.sumFreq(vecStr, freqMap);
        assert(sum == 2);
    }

    void testEqualPairs() {
        Solution soln = Solution();
        vector<vector<int>> grid;
        int sum;

        grid = {{1, 2, 3},
                {4, 5, 6},
                {4, 5, 6}};
        sum = soln.equalPairs(grid);
        assert(sum == 0);

        grid = {{3, 2, 1},
                {1, 7, 6},
                {2, 7, 7}};
        sum = soln.equalPairs(grid);
        assert(sum == 1);

        grid = {{3, 1, 2, 2},
                {1, 4, 4, 5},
                {2, 4, 2, 2},
                {2, 4, 2, 2}};
        sum = soln.equalPairs(grid);
        assert(sum == 3);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testVecToStr();
    solnTest.testVecVecToVecStr();
    solnTest.testVecVecToVecStrCol();
    solnTest.testVecStrToFreqMap();
    solnTest.testSumFreq();
    solnTest.testEqualPairs();

    return 0;
}
