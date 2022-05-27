// https://leetcode.com/problems/multiply-strings/
// https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
// https://www.hackerearth.com/problem/algorithm/multiply-two-strings/description/

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> convertToVec(string);
void testConvertToVec();
vector<int> multiplyVecWithDig(vector<int>, int);
void testMultiplyVecWithDig();
void showVec(vector<int> vec, string name);
vector<int> addVecs(vector<int> vec1, vector<int> vec2);
void testAddVecs();
string convertToString(vector<int>);
void testConvertToString();
string multiply(string num1, string num2);
string multiplyDebug(string num1, string num2, bool);
void testMultiplyDebug();

int main() {
    testConvertToVec();
    testMultiplyVecWithDig();
    testAddVecs();
    testConvertToString();
    testMultiplyDebug();

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

void testConvertToVec() {
    vector<int> outExpected;
    vector<int> outComputed;

    outExpected = {};
    outComputed = convertToVec("");
    assert(outExpected == outComputed);

    outExpected = {0};
    outComputed = convertToVec("0");
    assert(outExpected == outComputed);

    outExpected = {1};
    outComputed = convertToVec("1");
    assert(outExpected == outComputed);

    outExpected = {1, 0, 1, 1};
    outComputed = convertToVec("1011");
    assert(outExpected == outComputed);

    outExpected = {8, 1, 3, 7, 4, 2, 9};
    outComputed = convertToVec("8137429");
    assert(outExpected == outComputed);
}

vector<int> convertToVec(string numStr) {
    int numDigs = numStr.size();
    if (numDigs == 0) {
        return {};
    } else {
        vector<int> numVec(numDigs);
        for (int i = numDigs - 1; i >= 0; i--) {
            numVec[i] = (int)(numStr.at(i) - '0');
        }
        return numVec;
    }
}

void testMultiplyVecWithDig() {
    vector<int> outExpected;

    outExpected = {};
    assert(multiplyVecWithDig({}, 0) == outExpected);

    outExpected = {0};
    assert(multiplyVecWithDig({0}, 0) == outExpected);

    outExpected = {0, 0};
    assert(multiplyVecWithDig({1, 2}, 0) == outExpected);

    outExpected = {1, 2};
    assert(multiplyVecWithDig({1, 2}, 1) == outExpected);

    outExpected = {3, 6};
    // showVec(multiplyVecWithDig({1, 2}, 3), "");
    assert(multiplyVecWithDig({1, 2}, 3) == outExpected);

    outExpected = {7, 2};
    assert(multiplyVecWithDig({1, 2}, 6) == outExpected);

    outExpected = {1, 0, 8};
    assert(multiplyVecWithDig({1, 2}, 9) == outExpected);

    outExpected = {8, 9, 1};
    assert(multiplyVecWithDig({9, 9}, 9) == outExpected);
}

vector<int> multiplyVecWithDig(vector<int> vec, int dig) {
    int minLen = vec.size();
    vector<int> prod(minLen, 0);

    reverse(vec.begin(), vec.end());
    int rem = 0;
    for (int i = 0; i < minLen; i++) {
        int crrProd = vec[i] * dig;
        int crrSum = crrProd + rem;

        prod[i] = crrSum % 10;
        rem = crrSum / 10;
    }

    while (rem > 0) {
        prod.push_back(rem % 10);
        rem /= 10;
    }

    reverse(prod.begin(), prod.end());

    return prod;
}

void testAddVecs() {
    vector<int> outExpected;

    outExpected = {};
    assert(addVecs({}, {}) == outExpected);

    outExpected = {0};
    assert(addVecs({0}, {}) == outExpected);

    outExpected = {2};
    assert(addVecs({}, {2}) == outExpected);

    outExpected = {0};
    assert(addVecs({0}, {0}) == outExpected);

    outExpected = {2};
    assert(addVecs({1}, {1}) == outExpected);

    outExpected = {4, 9};
    assert(addVecs({1, 2}, {3, 7}) == outExpected);

    outExpected = {5, 5};
    // showVec(addVecs({3, 6}, {1, 9}), "");
    assert(addVecs({3, 6}, {1, 9}) == outExpected);

    outExpected = {1, 2, 2, 5};
    // showVec(addVecs({3, 6}, {1, 1, 8, 9}), "");
    assert(addVecs({3, 6}, {1, 1, 8, 9}) == outExpected);

    outExpected = {1, 2, 2, 5};
    assert(addVecs({1, 1, 8, 9}, {3, 6}) == outExpected);

    outExpected = {1, 0, 2, 5};
    // showVec(addVecs({3, 6}, {9, 8, 9}), "");
    assert(addVecs({3, 6}, {9, 8, 9}) == outExpected);

    outExpected = {1, 0, 2, 5};
    assert(addVecs({9, 8, 9}, {3, 6}) == outExpected);
}

vector<int> addVecs(vector<int> vec1, vector<int> vec2) {
    if (vec1.empty()) {
        return vec2;
    } else if (vec2.empty()) {
        return vec1;
    } else {
        int len1 = vec1.size();
        int len2 = vec2.size();
        int minLen = min(len1, len2);
        int maxLen = max(len1, len2);

        reverse(vec1.begin(), vec1.end());
        reverse(vec2.begin(), vec2.end());

        vector<int> vecSum(minLen, 0);
        int rem = 0;
        int i;
        for (i = 0; i < minLen; i++) {
            int sum = vec1[i] + vec2[i] + rem;
            vecSum[i] = sum % 10;
            rem = sum / 10;
        }

        if (len1 == len2) {
            while (rem > 0) {
                vecSum.push_back(rem % 10);
                rem /= 10;
            }
        } else if (maxLen == len1) {
            while (rem > 0 || i < len1) {
                int sum = rem;
                if (i < len1) {
                    sum += vec1[i];
                    i++;
                }
                vecSum.push_back(sum % 10);
                rem = sum / 10;
            }
        } else {
            while (rem > 0 || i < len2) {
                int sum = rem;
                if (i < len2) {
                    sum += vec2[i];
                    i++;
                }
                vecSum.push_back(sum % 10);
                rem = sum / 10;
            }
        }

        reverse(vecSum.begin(), vecSum.end());

        return vecSum;
    }
}

void testConvertToString() {
    assert(convertToString({}) == "");
    assert(convertToString({0}) == "0");
    assert(convertToString({1}) == "1");
    assert(convertToString({1, 0}) == "10");
    assert(convertToString({0, 1, 0}) == "10");
    assert(convertToString({1, 2, 7, 1, 8, 0}) == "127180");
    assert(convertToString({0, 0, 1, 2, 7, 1, 8, 0}) == "127180");
}

string convertToString(vector<int> numVec) {
    string numStr;

    int i = 0;
    if (numVec.size() > 1) {
        // consume all leading zeroes
        while (numVec[i] == 0) {
            i++;
        }
    }

    for (; i < numVec.size(); i++) {
        numStr = numStr + (char)('0' + numVec[i]);
    }

    return numStr;
}

void testMultiplyDebug() {
    assert(multiplyDebug("", "", false) == "");
    assert(multiplyDebug("1", "", false) == "1");
    assert(multiplyDebug("", "2", false) == "2");
    assert(multiplyDebug("0", "2", false) == "0");
    assert(multiplyDebug("2", "0", false) == "0");
    assert(multiplyDebug("3", "2", false) == "6");
    // cout << multiplyDebug("11", "13", false) << endl;
    assert(multiplyDebug("11", "13", false) == "143");
    assert(multiplyDebug("13", "11", false) == "143");
    assert(multiplyDebug("14", "7", false) == "98");
    assert(multiplyDebug("7", "14", false) == "98");
    assert(multiplyDebug("901", "6195", false) == "5581695");
    assert(multiplyDebug("6195", "901", false) == "5581695");
    assert(multiplyDebug("0", "9133", false) == "0");
    assert(multiplyDebug("9133", "0", false) == "0");
    assert(multiplyDebug("-901", "6195", false) == "-5581695");
    assert(multiplyDebug("6195", "-901", false) == "-5581695");
    assert(multiplyDebug("-901", "-6195", false) == "5581695");
}

string multiplyDebug(string num1, string num2, bool debug) {
    if (num1.empty()) {
        return num2;
    } else if (num2.empty()) {
        return num1;
        /**
         * without following zero check
         * - unit-tests were failing
         * - and giving this error on LeetCode c++ addresssanitizer heap-buffer-overflow on address
         */
    } else if (num1 == "0" || num2 == "0") {
        return "0";
    } else {
        bool num1IsNegative = num1.at(0) == '-';
        bool num2IsNegative = num2.at(0) == '-';
        bool bothNegative = num1IsNegative && num2IsNegative;

        num1 = num1IsNegative ? num1.substr(1, num1.size()) : num1;
        num2 = num2IsNegative ? num2.substr(1, num2.size()) : num2;

        vector<int> vec1 = convertToVec(num1);
        vector<int> vec2 = convertToVec(num2);
        reverse(vec2.begin(), vec2.end());

        if (debug) {
            showVec(vec1, "vec1");
            showVec(vec2, "vec2");
        }

        vector<int> prod;
        for (int i = 0; i < vec2.size(); i++) {
            if (debug) {
                printf("\n-----\n");
                printf("multiplying vec1 with vec2[%d]=%d\n", i, vec2[i]);
            }
            vector<int> crrDigProd = multiplyVecWithDig(vec1, vec2[i]);
            // add x (prod of each digit is multiplied by it's decimal positional value)
            for (int j = 1; j <= i; j++) {
              crrDigProd.push_back(0);
            }
            prod = addVecs(prod, crrDigProd);
            if (debug) {
                showVec(crrDigProd, "crrDigProd");
                showVec(prod, "prod");
            }
        }

        string prodStr = convertToString(prod);

        if ((num1IsNegative || num2IsNegative) && !bothNegative) {
            prodStr = "-" + prodStr;
        }

        return prodStr;
    }
}

string multiply(string num1, string num2) {
    return multiplyDebug(num1, num2, false);
}
