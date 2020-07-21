// LeetCode 42: trapping rain water
// https://leetcode.com/problems/trapping-rain-water/
// https://www.geeksforgeeks.org/trapping-rain-water/
// https://www.interviewbit.com/problems/rain-water-trapped/
// relatively hard problem

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void showVec(vector<int> vec, string name);
void testFindNgeeR();
vector<int> findNgeeR(vector<int> vec);
void testFindNgeeL();
vector<int> findNgeeL(vector<int> vec);
void testFillWaterL();
void fillWaterL(vector<int>, vector<int>, vector<int>&);
void testFillWaterR();
void fillWaterR(vector<int>, vector<int>, vector<int>&);
void testMeasureFilledWater();
int measureFilledWater(vector<int>, vector<int>);
void testCalcFilledWater();
int calcFilledWater(vector <int>);

int main() {
    testFindNgeeR();
    testFindNgeeL();

    testFillWaterL();
    testFillWaterR();
    testMeasureFilledWater();

    testCalcFilledWater();

    return 0;
}

void showVec(vector<int> vec, string name) {
    printf("\n%s vec is:-\n", name.c_str());

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == INT_MAX) {
            printf("+inf\t");
        } else if (vec[i] == INT_MIN) {
            printf("-inf\t");
        } else if (vec[i] <= 0) {
            printf("-\t");
        } else {
            printf("%d\t", vec[i]);
        }
    }
    cout << endl;
}

void testFindNgeeR() {
    vector<int> outExpected;

    // g++ -std=c++11 LeetCode/Arrays-Sorting-Searching/leetcode-42-trapping-rain-water.cpp
    outExpected = {6, 2, 3, 6, 6, 6, INT_MAX};
    assert(findNgeeR({8, 1, 3, 7, 4, 2, 9}) == outExpected);

    outExpected = {INT_MAX, 2, 3, 6, 6, 6, INT_MAX};
    assert(findNgeeR({9, 2, 4, 7, 3, 1, 8}) == outExpected);

    outExpected = {1, INT_MAX, 3, 5, 5, 7, 7, INT_MAX, INT_MAX, INT_MAX};
    assert(findNgeeR({9, 9, 3, 6, 4, 8, 5, 8, 5, 1}) == outExpected);

    outExpected = {1, 2, 4, 4, 5, 6, 9, 8, 9, INT_MAX};
    assert(findNgeeR({0, 3, 3, 0, 4, 5, 5, 1, 4, 9}) == outExpected);

    outExpected = {};
    assert(findNgeeR({}) == outExpected);

    outExpected = {INT_MAX};
    assert(findNgeeR({1}) == outExpected);

    outExpected = {INT_MAX, INT_MAX};
    assert(findNgeeR({1, -12}) == outExpected);

    outExpected = {1, 2, INT_MAX};
    assert(findNgeeR({1, 2, 3}) == outExpected);
}

vector<int> findNgeeR(vector<int> vec) {
    vector<int> ngeeR(vec.size(), INT_MAX);

    stack<int> stk;
    for (int i = (((int)vec.size()) - 1); i >= 0; i--) {
        int crrEle = vec[i];
        while (!stk.empty() && (vec[stk.top()] < crrEle)) {
            stk.pop();
        }

        if (stk.empty()) {
            ngeeR[i] = INT_MAX;
        } else {
            ngeeR[i] = stk.top();
        }

        stk.push(i);
    }

    return ngeeR;
}

void testFindNgeeL() {
    vector<int> outExpected;

    // g++ -std=c++11 LeetCode/Arrays-Sorting-Searching/leetcode-42-trapping-rain-water.cpp
    outExpected = {INT_MIN, 0, 0, 0, 3, 4, INT_MIN};
    assert(findNgeeL({8, 1, 3, 7, 4, 2, 9}) == outExpected);

    outExpected = {INT_MIN, 0, 0, 0, 3, 4, 0};
    assert(findNgeeL({9, 2, 4, 7, 3, 1, 8}) == outExpected);

    outExpected = {INT_MIN, 0, 1, 1, 3, 1, 5, 5, 7, 8};
    assert(findNgeeL({9, 9, 3, 6, 4, 8, 5, 8, 5, 1}) == outExpected);

    outExpected = {INT_MIN, INT_MIN, 1, 2, INT_MIN, INT_MIN, 5, 6, 6, INT_MIN};
    assert(findNgeeL({0, 3, 3, 0, 4, 5, 5, 1, 4, 9}) == outExpected);

    outExpected = {};
    assert(findNgeeL({}) == outExpected);

    outExpected = {INT_MIN};
    assert(findNgeeL({1}) == outExpected);

    outExpected = {INT_MIN, 0};
    assert(findNgeeL({1, -12}) == outExpected);

    outExpected = {INT_MIN, INT_MIN};
    assert(findNgeeL({-121, -12}) == outExpected);

    outExpected = {INT_MIN, INT_MIN, INT_MIN};
    assert(findNgeeL({1, 2, 3}) == outExpected);

    outExpected = {INT_MIN, 0, 1};
    assert(findNgeeL({3, 2, 1}) == outExpected);
}

vector<int> findNgeeL(vector<int> vec) {
    vector<int> ngeeL(vec.size(), INT_MIN);

    stack<int> stk;
    for (int i = 0; i < vec.size(); i++) {
        int crrEle = vec[i];
        while (!stk.empty() && (vec[stk.top()] < crrEle)) {
            stk.pop();
        }

        if (stk.empty()) {
            ngeeL[i] = INT_MIN;
        } else {
            ngeeL[i] = stk.top();
        }

        stk.push(i);
    }

    return ngeeL;
}

void testFillWaterL() {
    vector<int> heightInp;
    vector<int> waterComputedOutExpected;
    vector<int> outComputed;
    vector<int> waterComputed;

    heightInp = {8, 1, 3, 7, 4, 2, 9};
    waterComputed = {0, 0, 0, 0, 0, 0, 0};
    waterComputedOutExpected = {0, 8, 8, 8, 8, 8, 0};
    fillWaterL(heightInp, findNgeeR(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {9, 2, 4, 7, 3, 1, 8};
    waterComputed = {0, 0, 0, 0, 0, 0, 0};
    waterComputedOutExpected = {0, 0, 0, 0, 7, 7, 0};
    fillWaterL(heightInp, findNgeeR(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {9, 9, 3, 6, 4, 8, 5, 8, 5, 1};
    waterComputed = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    waterComputedOutExpected = {0, 0, 0, 0, 6, 0, 8, 0, 0, 0};
    fillWaterL(heightInp, findNgeeR(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {0, 3, 3, 0, 4, 5, 5, 1, 4, 9};
    waterComputed = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    waterComputedOutExpected = {0, 0, 0, 3, 0, 0, 0, 5, 5, 0};
    fillWaterL(heightInp, findNgeeR(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);
}

void fillWaterL(vector<int> height, vector<int> ngeeR, vector<int>& water) {
    for (int i = 0; i < height.size();) {
        int ngeInd = ngeeR[i];
        if ((ngeInd != INT_MAX) && (ngeInd != i + 1)) {
            int waterHeight = min(height[i], height[ngeInd]);
            for (i = i + 1; i < ngeInd; i++) {
                water[i] = max(water[i], waterHeight);
            }
        } else {
            i++;
        }
    }
}

void testFillWaterR() {
    vector<int> heightInp;
    vector<int> waterComputedOutExpected;
    vector<int> outComputed;
    vector<int> waterComputed;

    heightInp = {8, 1, 3, 7, 4, 2, 9};
    waterComputed = {0, 8, 8, 8, 8, 8, 0};
    waterComputedOutExpected = {0, 8, 8, 8, 8, 8, 0};
    fillWaterR(heightInp, findNgeeL(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {9, 2, 4, 7, 3, 1, 8};
    waterComputed = {0, 0, 0, 0, 7, 7, 0};
    waterComputedOutExpected = {0, 8, 8, 8, 8, 8, 0};
    fillWaterR(heightInp, findNgeeL(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {9, 9, 3, 6, 4, 8, 5, 8, 5, 1};
    waterComputed = {0, 0, 0, 0, 6, 0, 8, 0, 0, 0};
    waterComputedOutExpected = {0, 0, 8, 8, 8, 0, 8, 0, 0, 0};
    fillWaterR(heightInp, findNgeeL(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {0, 3, 3, 0, 4, 5, 5, 1, 4, 9};
    waterComputed = {0, 0, 0, 3, 0, 0, 0, 5, 5, 0};
    waterComputedOutExpected = {0, 0, 0, 3, 0, 0, 0, 5, 5, 0};
    fillWaterR(heightInp, findNgeeL(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);

    heightInp = {0, 3, 3, 0, 4, 5, 5, 1, 4, 9};
    waterComputed = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    waterComputedOutExpected = {0, 0, 0, 0, 0, 0, 0, 4, 0, 0};
    fillWaterR(heightInp, findNgeeL(heightInp), waterComputed);
    assert(waterComputedOutExpected == waterComputed);
}

void fillWaterR(vector<int> height, vector<int> ngeeL, vector<int>& water) {
    for (int i = ((int)height.size() - 1); i >= 0;) {
        int ngeInd = ngeeL[i];
        if ((ngeInd != INT_MIN) && (ngeInd != i - 1)) {
            int waterHeight = min(height[i], height[ngeInd]);
            for (i = i - 1; i > ngeInd; i--) {
                water[i] = max(water[i], waterHeight);
            }
        } else {
            i--;
        }
    }
}

void testMeasureFilledWater() {
    assert(measureFilledWater({8, 1, 3, 7, 4, 2, 9}, {0, 8, 8, 8, 8, 8, 0}) == 23);
    assert(measureFilledWater({9, 2, 4, 7, 3, 1, 8}, {0, 8, 8, 8, 8, 8, 0}) == 23);
    assert(measureFilledWater({9, 9, 3, 6, 4, 8, 5, 8, 5, 1}, {0, 0, 8, 8, 8, 0, 8, 0, 0, 0}) == 14);
    assert(measureFilledWater({0, 3, 3, 0, 4, 5, 5, 1, 4, 9}, {0, 0, 0, 3, 0, 0, 0, 5, 5, 0}) == 8);
    assert(measureFilledWater({0, 3, 3, 0, 4, 5, 5, 1, 4, 9}, {0, 0, 0, 0, 0, 0, 0, 4, 0, 0}) == 3);
}

int measureFilledWater(vector<int> height, vector<int> water) {
    int totalWater = 0;
    for (int i = 0; i < height.size(); i++) {
        if (water[i] > 0) {
            totalWater += water[i] - height[i];
        }
    }
    return totalWater;
}

void testCalcFilledWater() {
  assert(calcFilledWater({8, 1, 3, 7, 4, 2, 9}) == 23);
  assert(calcFilledWater({9, 2, 4, 7, 3, 1, 8}) == 23);
  assert(calcFilledWater({9, 9, 3, 6, 4, 8, 5, 8, 5, 1}) == 14);
  assert(calcFilledWater({0, 3, 3, 0, 4, 5, 5, 1, 4, 9}) == 8);
  assert(calcFilledWater({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
  assert(calcFilledWater({2, 0, 2}) == 2);
  assert(calcFilledWater({3, 0, 2, 0, 4}) == 7);
  assert(calcFilledWater({3, 0, 0, 2, 0, 4}) == 10);
  assert(calcFilledWater({1, 2}) == 0);
  assert(calcFilledWater({1, 2, 3, 4, 5, 4, 3, 2, 1}) == 0);
}

int calcFilledWater(vector <int> height) {
  vector <int> ngeeR = findNgeeR(height);
  vector <int> ngeeL = findNgeeL(height);
  vector <int> water((int) height.size(), 0);
  fillWaterL(height, ngeeR, water);
  fillWaterR(height, ngeeL, water);
  return measureFilledWater(height, water);
}
