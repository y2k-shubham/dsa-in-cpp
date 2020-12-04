// LeetCode-338: https://leetcode.com/problems/counting-bits/
// TechDose: https://www.youtube.com/watch?v=awxaRgUB4Kw

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> countBits(int num) {
    vector<int> num1Bits(num + 1);
    num1Bits[0] = 0;  // 0 has no set bits
    if (num >= 1) {
        num1Bits[1] = 1;  // 1 has 1 set bits
    }
    if (num >= 2) {
        num1Bits[2] = 1;  // 2 has 1 set bits
    }

    for (int i = 3; i <= num; i++) {
        if ((i % 2) == 0) {
            // no of set bits for even no will be
            // same as no of set bits int it's half
            num1Bits[i] = num1Bits[i / 2];
        } else {
            // no of set bits for odd no will be
            // 1 more than the no of set bits int it's half
            num1Bits[i] = num1Bits[i / 2] + 1;
        }
    }

    return num1Bits;
}

void testCountBits() {
    int num;
    vector<int> vecOutExpected;
    vector<int> vecOutComputed;

    num = 0;
    vecOutExpected = {0};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 1;
    vecOutExpected = {0, 1};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 2;
    vecOutExpected = {0, 1, 1};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 3;
    vecOutExpected = {0, 1, 1, 2};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 4;
    vecOutExpected = {0, 1, 1, 2, 1};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 5;
    vecOutExpected = {0, 1, 1, 2, 1, 2};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 6;
    vecOutExpected = {0, 1, 1, 2, 1, 2, 2};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 7;
    vecOutExpected = {0, 1, 1, 2, 1, 2, 2, 3};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 8;
    vecOutExpected = {0, 1, 1, 2, 1, 2, 2, 3, 1};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 9;
    vecOutExpected = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);

    num = 10;
    vecOutExpected = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2};
    vecOutComputed = countBits(num);
    assert(vecOutExpected == vecOutComputed);
}

int main() {
    testCountBits();

    return 0;
}