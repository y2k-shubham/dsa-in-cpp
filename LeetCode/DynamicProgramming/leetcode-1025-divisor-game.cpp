// LeetCode-1025: https://leetcode.com/problems/divisor-game/
// explaination: (@LeadCoding) https://www.youtube.com/watch?v=UbE4-ONpJcc

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

// LC submission => speed: 8 %tile, memory: 6 %tile
int doesAliceWin1a(map<pair<int, int>, int>& winsMemo, int isAlice, int N) {
    if (winsMemo.find({isAlice, N}) == winsMemo.end()) {
        int result;

        if (N == 1) {
            result = 1 - isAlice;
            winsMemo[{isAlice, N}] = result;
        } else {
            // this someMoveMade is redundant since
            // 'result' is already being initialized to take care of that
            bool someMoveMade = false;

            if (isAlice == 1) {
                // determining victory path for alice
                result = 0;

                for (int i = 1; i <= (N / 2); i++) {
                    if ((N % i) == 0) {
                        someMoveMade = true;
                        result = result | doesAliceWin1a(winsMemo, 0, N - i);

                        if (result == 1) {
                            break;
                        }
                    }
                }
            } else {
                // determining victory path for bob
                result = 1;

                for (int i = 1; i <= (N / 2); i++) {
                    if ((N % i) == 0) {
                        someMoveMade = true;
                        result = result & doesAliceWin1a(winsMemo, 1, N - i);

                        if (result == 0) {
                            break;
                        }
                    }
                }
            }

            if (someMoveMade) {
                winsMemo[{isAlice, N}] = result;
            } else {
                winsMemo[{isAlice, N}] = 1 - isAlice;
            }

            // printf("stored winsMemo[(isAlice=%d, N=%d)] = %d\n", isAlice, N, winsMemo[{isAlice, N}]);
        }
    }
    return winsMemo[{isAlice, N}];
}

void testDoesAliceWin1a() {
    map<pair<int, int>, int> winsMemo;
    int doesAliceWinComputed;
    int N;

    winsMemo = {};
    N = 2;
    doesAliceWinComputed = doesAliceWin1a(winsMemo, 1, N);
    // cout << doesAliceWinComputed << endl;
    assert(doesAliceWinComputed == 1);

    winsMemo = {};
    N = 3;
    doesAliceWinComputed = doesAliceWin1a(winsMemo, 1, N);
    // cout << doesAliceWinComputed << endl;
    assert(doesAliceWinComputed == 0);
}

// only slightly condensed version of above -> logic wise identical
int doesAliceWin1b(map<pair<int, int>, int>& winsMemo, int isAlice, int N) {
    if (N == 1) {
        return 1 - isAlice;
    } else {
        pair<int, int> crrNodePair = {isAlice, N};

        if (winsMemo.find(crrNodePair) == winsMemo.end()) {
            int result;
            if (isAlice == 1) {
                result = 0;
                for (int i = 1; i <= (N / 2); i++) {
                    if ((N % i) == 0) {
                        result = result | doesAliceWin1b(winsMemo, 0, N - i);

                        if (result == 1) {
                            break;
                        }
                    }
                }
            } else {
                result = 1;
                for (int i = 1; i <= (N / 2); i++) {
                    if ((N % i) == 0) {
                        result = result & doesAliceWin1b(winsMemo, 1, N - i);

                        if (result == 0) {
                            break;
                        }
                    }
                }
            }

            winsMemo[crrNodePair] = result;
            return result;
        } else {
            return winsMemo[crrNodePair];
        }
    }
}

// identical to 1 except that to check factors we loop from 1 to root-N only
// but with that change, time complexity comes down from n^2 to n^(3/2)
// -------
// but as you would expect, net computation won't change (only loop iterations would decrease)
// and it shows => LC submission results are identical to 1a & 1b above
int doesAliceWin2(map<pair<int, int>, int>& winsMemo, int isAlice, int N) {
    if (N == 1) {
        return 1 - isAlice;
    } else {
        pair<int, int> crrNodePair = {isAlice, N};

        if (winsMemo.find(crrNodePair) == winsMemo.end()) {
            int result;
            if (isAlice == 1) {
                result = 0;
                for (int i = 1; (i * i) <= N; i++) {
                    if ((N % i) == 0) {
                        result = result | doesAliceWin2(winsMemo, 0, N - i);
                        if (result == 1) {
                            break;
                        }

                        // complementary divisor can only be considered in case of i > 1
                        // because for i=1, N/i = N; then N - N/i becomes 0
                        if (i > 1) {
                            result = result | doesAliceWin2(winsMemo, 0, N - N / i);
                            if (result == 1) {
                                break;
                            }
                        }
                    }
                }
            } else {
                result = 1;
                for (int i = 1; (i * i) <= N; i++) {
                    if ((N % i) == 0) {
                        result = result & doesAliceWin2(winsMemo, 1, N - i);
                        if (result == 0) {
                            break;
                        }

                        // complementary divisor can only be considered in case of i > 1
                        // because for i=1, N/i = N; then N - N/i becomes 0
                        if (i > 1) {
                            result = result & doesAliceWin2(winsMemo, 1, N - N / i);
                            if (result == 0) {
                                break;
                            }
                        }
                    }
                }
            }

            // printf("stored winsMemo[(isAlice=%d, N=%d)] = %d\n", isAlice, N, winsMemo[crrNodePair]);
            winsMemo[crrNodePair] = result;
            return result;
        } else {
            return winsMemo[crrNodePair];
        }
    }
}

void testDoesAliceWin2() {
    map<pair<int, int>, int> winsMemo;
    int doesAliceWinComputed;
    int N;

    // winsMemo = {};
    // N = 2;
    // doesAliceWinComputed = doesAliceWin2(winsMemo, 1, N);
    // // cout << doesAliceWinComputed << endl;
    // assert(doesAliceWinComputed == 1);

    winsMemo = {};
    N = 3;
    doesAliceWinComputed = doesAliceWin2(winsMemo, 1, N);
    // cout << doesAliceWinComputed << endl;
    assert(doesAliceWinComputed == 0);
}

int main() {
    testDoesAliceWin1a();
    testDoesAliceWin2();

    return 0;
}
