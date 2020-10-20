// LeetCode-152: https://leetcode.com/problems/maximum-product-subarray/

#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <map>

using namespace std;

class RangeMetaData {

  public:
  int numZeroes;
  int sInd;
  int eInd;
  int firstNegInd;
  int lastNegInd;
  int prod;
  int lFNProd;
  int rLNProd;

  

};


