// https://leetcode.com/problems/integer-to-roman/
// https://www.geeksforgeeks.org/converting-decimal-number-lying-between-1-to-3999-to-roman-numerals/
// https://www.interviewbit.com/problems/integer-to-roman/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

bool isPowOf(int, int);
void testIsPowOf();
map<int, string> createNumRepMap();
int findFloor(map<int, string>, int);
void testFindFloor();
pair <int, string> removeMaxFloor(map <int, string>, int);
void testRemoveMaxFloor();
string intToRoman(int);
void testIntToRoman();


int main() {
    testIsPowOf();
    testFindFloor();
    testRemoveMaxFloor();
    testIntToRoman();


    return 0;
}

map<int, string> createNumRepMap() {
    return {
        {1, "I"},
        {4, "IV"},
        {5, "V"},
        {9, "IX"},
        {10, "X"},
        {40, "XL"},
        {50, "L"},
        {90, "XC"},
        {100, "C"},
        {400, "CD"},
        {500, "D"},
        {900, "CM"},
        {1000, "M"}};
}

void testIsPowOf() {
    assert(isPowOf(10, 1) == true);
    assert(isPowOf(10, 10) == true);
    assert(isPowOf(10, 100) == true);
    assert(isPowOf(10, 1000) == true);

    assert(isPowOf(10, 9) == false);
    assert(isPowOf(10, 11) == false);
    assert(isPowOf(10, 90) == false);
    assert(isPowOf(10, 99) == false);
    assert(isPowOf(10, 101) == false);
    assert(isPowOf(10, 110) == false);
}

// not used, thought would be required, but not needed
bool isPowOf(int base, int n) {
    double exp = log(n) / log(base);
    int intExp = (int)(ceil(exp));
    return ((int)pow(base, intExp)) == n;
}

void testFindFloor() {
    map<int, string> numRepMap = createNumRepMap();
    assert(findFloor(numRepMap, 1) == 1);
    assert(findFloor(numRepMap, 2) == 1);
    assert(findFloor(numRepMap, 3) == 1);
    assert(findFloor(numRepMap, 4) == 4);
    assert(findFloor(numRepMap, 5) == 5);
    assert(findFloor(numRepMap, 6) == 5);
    assert(findFloor(numRepMap, 7) == 5);
    assert(findFloor(numRepMap, 8) == 5);
    assert(findFloor(numRepMap, 9) == 9);
    assert(findFloor(numRepMap, 10) == 10);
    assert(findFloor(numRepMap, 11) == 10);
    assert(findFloor(numRepMap, 12) == 10);
    assert(findFloor(numRepMap, 15) == 10);
    assert(findFloor(numRepMap, 39) == 10);
    assert(findFloor(numRepMap, 40) == 40);
    assert(findFloor(numRepMap, 40) == 40);
    assert(findFloor(numRepMap, 41) == 40);
    assert(findFloor(numRepMap, 49) == 40);
    assert(findFloor(numRepMap, 50) == 50);
}

int findFloor(map<int, string> numRepMap, int n) {
    int floor = 1;
    for (map<int, string>::iterator i = numRepMap.begin(); i != numRepMap.end(); i++) {
        int num = (*i).first;
        if (num <= n) {
            floor = num;
        } else {
            break;
        }
    }
    return floor;
}

void testRemoveMaxFloor() {
  pair <int, string> mPair; 
  map <int, string> numRepMap = createNumRepMap();

  mPair = make_pair(0, "I");
  assert(removeMaxFloor(numRepMap, 1) == mPair);

  mPair = make_pair(0, "II");
  assert(removeMaxFloor(numRepMap, 2) == mPair);

  mPair = make_pair(0, "III");
  assert(removeMaxFloor(numRepMap, 3) == mPair);

  mPair = make_pair(0, "IV");
  assert(removeMaxFloor(numRepMap, 4) == mPair);

  mPair = make_pair(0, "V");
  assert(removeMaxFloor(numRepMap, 5) == mPair);

  mPair = make_pair(1, "V");
  assert(removeMaxFloor(numRepMap, 6) == mPair);

  mPair = make_pair(2, "V");
  assert(removeMaxFloor(numRepMap, 7) == mPair);

  mPair = make_pair(3, "V");
  assert(removeMaxFloor(numRepMap, 8) == mPair);

  mPair = make_pair(0, "IX");
  assert(removeMaxFloor(numRepMap, 9) == mPair);

  mPair = make_pair(0, "X");
  assert(removeMaxFloor(numRepMap, 10) == mPair);

  mPair = make_pair(1, "X");
  assert(removeMaxFloor(numRepMap, 11) == mPair);

  mPair = make_pair(2, "X");
  assert(removeMaxFloor(numRepMap, 12) == mPair);

  mPair = make_pair(9, "XXX");
  assert(removeMaxFloor(numRepMap, 39) == mPair);

  mPair = make_pair(0, "XL");
  assert(removeMaxFloor(numRepMap, 40) == mPair);

  mPair = make_pair(1, "XL");
  assert(removeMaxFloor(numRepMap, 41) == mPair);

  mPair = make_pair(9, "XL");
  assert(removeMaxFloor(numRepMap, 49) == mPair);

  mPair = make_pair(0, "L");
  assert(removeMaxFloor(numRepMap, 50) == mPair);

  mPair = make_pair(6, "L");
  assert(removeMaxFloor(numRepMap, 56) == mPair);

  mPair = make_pair(7, "XC");
  assert(removeMaxFloor(numRepMap, 97) == mPair);
}

pair <int, string> removeMaxFloor(map<int, string> numRepMap, int n) {
  int floor = findFloor(numRepMap, n);
  int quot = n / floor;
  int rem = n % floor;

  string rep;
  for (int i = 1; i <= quot; i++) {
    rep = rep + numRepMap[floor];
  }

  return make_pair(rem, rep);
}

void testIntToRoman() {
  assert(intToRoman(1) == "I");
  assert(intToRoman(2) == "II");
  assert(intToRoman(49) == "XLIX");
  assert(intToRoman(58) == "LVIII");
  assert(intToRoman(194) == "CXCIV");
  assert(intToRoman(1994) == "MCMXCIV");
}

string intToRoman(int num) {
  map <int, string> numRepMap = createNumRepMap();

  string rep;
  while (num > 0) {
    pair <int, string> removedRes = removeMaxFloor(numRepMap, num);
    rep = rep + removedRes.second;
    num = removedRes.first;
  }
  return rep;
}
