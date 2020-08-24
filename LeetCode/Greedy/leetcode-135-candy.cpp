// https://leetcode.com/problems/candy/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> leftPassCandyAssign(vector<int>, bool);
void testLeftPassCandyAssign();
vector<int> rightPassCandyAssign(vector<int>, bool);
void testRightPassCandyAssign();
void showVec(vector<int>, string);
vector<int> candyAssign(vector<int>, bool);
void testCandyAssign();

int main() {
    testLeftPassCandyAssign();
    testRightPassCandyAssign();

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

void testLeftPassCandyAssign() {
    vector<int> ratingsIn;
    vector<int> candiesOutExpected;
    vector<int> candiesOutComputed;

    ratingsIn = {};
    candiesOutExpected = {};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4};
    candiesOutExpected = {1};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 5};
    candiesOutExpected = {1, 2};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {5, 4};
    candiesOutExpected = {1, 1};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18};
    candiesOutExpected = {1, 2, 3};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 7, 9};
    candiesOutExpected = {1, 2, 3, 1, 2};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18};
    candiesOutExpected = {1, 2, 3, 1, 1, 2};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18, 9};
    candiesOutExpected = {1, 2, 3, 1, 1, 2, 1};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 18, 17, 17, 18, 9};
    candiesOutExpected = {1, 2, 3, 1, 1, 1, 1, 2, 1};
    candiesOutComputed = leftPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);
}

vector<int> leftPassCandyAssign(vector<int> ratings, bool debug) {
    int len = ratings.size();

    if (len == 0) {
        return {};
    } else if (len == 1) {
        return {1};
    } else {
        vector<int> candies(len, 1);

        int i = 0;
        while (i < len - 1) {
            if ((i + 1) < len && ratings[i] < ratings[i + 1]) {
                // assign increasing no of candies to rising slope
                int candyCount = 1;
                while ((i + 1) < len && ratings[i] < ratings[i + 1]) {
                    candies[i] = candyCount;
                    candyCount++;
                    i++;
                }

                // after exiting from loop, assign candies to current element
                // (because we'll always exit the loop with possibly current assign-able element still unassigned)
                if (i < len && ratings[i - 1] < ratings[i]) {
                    candies[i] = candies[i - 1] + 1;
                }
            } else {
                i++;
            }

            if (debug) {
                printf("at ratings[i=%d] = %d\n", i, ratings[i]);
            }
        }

        // when array length is 2, the above loop won't run
        if (ratings[len - 2] < ratings[len - 1]) {
            candies[len - 1] = candies[len - 2] + 1;
        }

        return candies;
    }
}

void testRightPassCandyAssign() {
    vector<int> ratingsIn;
    vector<int> candiesOutExpected;
    vector<int> candiesOutComputed;

    ratingsIn = {};
    candiesOutExpected = {};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4};
    candiesOutExpected = {1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 5};
    candiesOutExpected = {1, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {5, 4};
    candiesOutExpected = {2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    // showVec(candiesOutComputed, "candiesOutComputed");
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18};
    candiesOutExpected = {1, 1, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {18, 9, 4};
    candiesOutExpected = {3, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 7, 9};
    candiesOutExpected = {1, 1, 2, 1, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 7, 18, 9, 4};
    candiesOutExpected = {2, 1, 3, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18};
    candiesOutExpected = {1, 1, 1, 2, 1, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {18, 17, 18, 18, 9, 4};
    candiesOutExpected = {2, 1, 1, 3, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18, 9};
    candiesOutExpected = {1, 1, 1, 2, 1, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 18, 17, 18, 18, 9, 4};
    ;
    candiesOutExpected = {1, 2, 1, 1, 3, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 18, 17, 17, 18, 9};
    candiesOutExpected = {1, 1, 1, 1, 2, 1, 1, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 18, 17, 17, 18, 18, 18, 9, 4};
    candiesOutExpected = {1, 2, 1, 1, 1, 1, 3, 2, 1};
    candiesOutComputed = rightPassCandyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);
}

vector<int> rightPassCandyAssign(vector<int> ratings, bool debug) {
    int len = ratings.size();

    if (len == 0) {
        return {};
    } else if (len == 1) {
        return {1};
    } else {
        vector<int> candies(len, 1);

        int i = len - 1;
        while (i > 1) {
            if ((i - 1) >= 0 && ratings[i - 1] > ratings[i]) {
                // assign increasing no of candies to rising slope
                int candyCount = 1;
                while ((i - 1) >= 0 && ratings[i - 1] > ratings[i]) {
                    candies[i] = candyCount;
                    candyCount++;
                    i--;
                }

                // after exiting from loop, assign candies to current element
                // (because we'll always exit the loop with possibly current assign-able element still unassigned)
                if (i >= 0 && ratings[i] > ratings[i + 1]) {
                    candies[i] = candies[i + 1] + 1;
                }
            } else {
                i--;
            }

            if (debug && i >= 0) {
                printf("at ratings[i=%d] = %d, candies[i=%d] = %d\n", i, ratings[i], i, candies[i]);
            }
        }

        // when array length is 2, the above loop won't run
        if (ratings[0] > ratings[1]) {
            candies[0] = candies[1] + 1;
        }

        return candies;
    }
}

void testCandyAssign() {
    vector<int> ratingsIn;
    vector<int> candiesOutExpected;
    vector<int> candiesOutComputed;

    ratingsIn = {};
    candiesOutExpected = {};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4};
    candiesOutExpected = {1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 5};
    candiesOutExpected = {1, 2};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {5, 4};
    candiesOutExpected = {2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    // showVec(candiesOutComputed, "candiesOutComputed");
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18};
    candiesOutExpected = {1, 2, 3};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {18, 9, 4};
    candiesOutExpected = {3, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 7, 9};
    candiesOutExpected = {1, 1, 2, 1, 2};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 7, 18, 9, 4};
    candiesOutExpected = {2, 1, 3, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18};
    candiesOutExpected = {1, 2, 3, 2, 1, 2};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {18, 17, 18, 18, 9, 4};
    candiesOutExpected = {2, 1, 1, 3, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 17, 18, 9};
    candiesOutExpected = {1, 2, 3, 2, 1, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 18, 17, 18, 18, 9, 4};
    candiesOutExpected = {1, 2, 1, 2, 3, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {4, 9, 18, 18, 18, 17, 17, 18, 9};
    candiesOutExpected = {1, 2, 3, 1, 2, 1, 1, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);

    ratingsIn = {9, 18, 17, 17, 18, 18, 18, 9, 4};
    candiesOutExpected = {1, 2, 1, 1, 2, 1, 3, 2, 1};
    candiesOutComputed = candyAssign(ratingsIn, false);
    assert(candiesOutExpected == candiesOutComputed);
}

vector<int> candyAssign(vector<int> ratings, bool debug) {
    vector<int> lCandies = leftPassCandyAssign(ratings, debug);
    vector<int> rCandies = rightPassCandyAssign(ratings, debug);

    int len = ratings.size();
    vector<int> candies(len);
    for (int i = 0; i < len; i++) {
        candies[i] = max(lCandies[i], rCandies[i]);
    }

    return candies;
}

int candy(vector <int>& ratings) {
  vector <int> candies = candyAssign(ratings, false);

  int sum = 0;
  for (int i = 0; i < ratings.size(); i++) {
    sum += candies[i];
  }

  return sum;
}
