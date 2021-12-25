// https://leetcode.com/problems/largest-rectangle-in-histogram/
// an application of this problem is leetcode-1793: https://leetcode.com/problems/maximum-score-of-a-good-subarray/

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> findNleLeft(vector<int>& heights);
void testFindNleLeft();
vector<int> findNleRight(vector<int>& heights);
void testFindNleRight();
int largestRectangleArea(vector<int>& heights);
void testLargestRectangleArea();
void showVec(vector<int> vec, string name);

int main() {
    testFindNleLeft();
    testFindNleRight();
    testLargestRectangleArea();


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

void testFindNleLeft() {
    vector<int> inp;
    vector<int> outExp;

    inp = {};
    outExp = {};
    assert(findNleLeft(inp) == outExp);

    inp = {5};
    outExp = {-1};
    assert(findNleLeft(inp) == outExp);

    inp = {5, 4};
    outExp = {-1, -1};
    assert(findNleLeft(inp) == outExp);

    inp = {4, 5};
    outExp = {-1, 0};
    assert(findNleLeft(inp) == outExp);

    inp = {0, 9};
    outExp = {-1, 0};
    assert(findNleLeft(inp) == outExp);

    inp = {8, 1, 3, 7, 7, 4, 2, 9};
    outExp = {-1, -1, 1, 2, 2, 2, 1, 6};
    // showVec(findNleLeft(inp), "");
    assert(findNleLeft(inp) == outExp);
}

vector<int> findNleLeft(vector<int>& heights) {
    int len = heights.size();
    vector<int> nleLeft(len, -1);
    stack<int> stk;

    stk.push(0);
    for (int i = 1; i < len; i++) {
        int crrEle = heights[i];
        while (!stk.empty() && heights[stk.top()] >= crrEle) {
            stk.pop();
        }

        if (!stk.empty()) {
            nleLeft[i] = stk.top();
        }
        stk.push(i);
    }

    return nleLeft;
}

void testFindNleRight() {
    vector<int> inp;
    vector<int> outExp;

    inp = {};
    outExp = {};
    assert(findNleRight(inp) == outExp);

    inp = {5};
    outExp = {1};
    assert(findNleRight(inp) == outExp);

    inp = {4, 5};
    outExp = {2, 2};
    assert(findNleRight(inp) == outExp);

    inp = {5, 4};
    outExp = {1, 2};
    assert(findNleRight(inp) == outExp);

    inp = {9, 0};
    outExp = {1, 2};
    assert(findNleRight(inp) == outExp);

    inp = {9, 2, 4, 7, 7, 3, 1, 8};
    outExp = {1, 6, 5, 5, 5, 6, 8, 8};
    // showVec(findNleLeft(inp), "");
    assert(findNleRight(inp) == outExp);
}

vector<int> findNleRight(vector<int>& heights) {
    int len = heights.size();
    vector<int> nleRight(len, len);
    stack<int> stk;

    stk.push(len - 1);
    for (int i = len - 2; i >= 0; i--) {
        int crrEle = heights[i];
        while (!stk.empty() && heights[stk.top()] >= crrEle) {
            stk.pop();
        }

        if (!stk.empty()) {
            nleRight[i] = stk.top();
        }
        stk.push(i);
    }

    return nleRight;
}

void testLargestRectangleArea() {
  vector <int> inp;

  inp = {};
  assert(largestRectangleArea(inp) == 0);

  inp = {4};
  assert(largestRectangleArea(inp) == 4);

  inp = {4, 5};
  assert(largestRectangleArea(inp) == 8);

  inp = {9, 1};
  // cout << largestRectangleArea(inp) << endl;
  assert(largestRectangleArea(inp) == 9);

  inp = {1, 1};
  assert(largestRectangleArea(inp) == 2);

  inp = {0, 9};
  assert(largestRectangleArea(inp) == 9);

  inp = {9, 0};
  assert(largestRectangleArea(inp) == 9);

  inp = {3, 1, 5, 7, 5, 5};
  assert(largestRectangleArea(inp) == 20);
}

int largestRectangleArea(vector<int>& heights) {
    if (heights.empty()) {
        return 0;
    } else if (heights.size() == 1) {
        return heights[0];
    } else {
        int len = heights.size();
        vector<int> nleLeft = findNleLeft(heights);
        vector<int> nleRight = findNleRight(heights);

        int maxArea = -1;
        for (int i = 0; i < len; i++) {
            int lLimit = nleLeft[i];
            int rLimit = nleRight[i];

            // printf("\nfor heights[%d] = %d\n", i, heights[i]);
            // printf("lLimit = %d, rLimit = %d\n", lLimit, rLimit);
            // printf("height[lLimit+1=%d] = %d, height[rLimit-1=%d] = %d\n", (lLimit + 1), heights[lLimit + 1], (rLimit - 1), heights[rLimit - 1]);
            int crrArea = ((rLimit - 1) - (lLimit + 1) + 1) * heights[i];
            if (crrArea > maxArea) {
                maxArea = crrArea;
            }
        }

        return maxArea;
    }
}
