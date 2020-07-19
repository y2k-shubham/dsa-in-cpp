// LeetCode-45: https://leetcode.com/problems/jump-game-ii/
// https://www.interviewbit.com/problems/jump-game-array/
// not very hard, but also not as straightforward as it seems

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

void testCalcMinJmpSrcInd();
vector <int> calcMinJmpSrcInd(vector <int>);
void showVec(vector<int>, string);
void testCalcMinHops();
vector <int> calcMinHops(vector <int>);
void testCalcMinHopsOpt();
vector <int> calcMinHopsOpt(vector <int>);
void testJump();
int jump(vector <int>&);

int main() {
  // testCalcMinJmpSrcInd();

  // testCalcMinHops();
  testCalcMinHopsOpt();
  testJump();

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

void testCalcMinJmpSrcInd() {
  vector <int> outExpected;

  outExpected = {INT_MAX, 0, 0, 0, 0, 0, 0};
  assert(calcMinJmpSrcInd({8, 1, 3, 7, 4, 2, 9}) == outExpected);

  outExpected = {INT_MAX, 0, 0, 1, 1};
  assert(calcMinJmpSrcInd({2,3,1,1,4}) == outExpected);

  outExpected = {INT_MAX, 0, 0, 0, INT_MAX};
  assert(calcMinJmpSrcInd({3,2,1,0,4}) == outExpected);
}

// not required, thought it might help, but unnecessary
vector <int> calcMinJmpSrcInd(vector <int> jmp) {
  vector <int> minJmpSrcInd(jmp.size(), INT_MAX);
  for (int i = 0; i < jmp.size() - 1; i++) {
    for (int j = 1; ((i + j) < jmp.size()) && (j <= jmp[i]); j++) {
      minJmpSrcInd[i + j] = min(minJmpSrcInd[i + j], i);
    }
  }
  return minJmpSrcInd;
}

void testCalcMinHops() {
  vector <int> outExpected;

  outExpected = {0, 1, 1, 1, 1, 1, 1};
  assert(calcMinHops({8, 1, 3, 7, 4, 2, 9}) == outExpected);

  outExpected = {0, 1, 1, 2, 2};
  assert(calcMinHops({2,3,1,1,4}) == outExpected);

  outExpected = {0, 1, 1, 1, INT_MAX};
  assert(calcMinHops({3,2,1,0,4}) == outExpected);
}

/**
 * TimeLimitExceeded
 * this implementation is suboptimal - in fact, if closely observed,
 * it can pretty much be treated as being a brute force approach
 * 
 * consider the case when input array is in descending order
 * 5 4 3 2 1 0
 * 
 *  - here all indices can reach final indices in single hop
 *    (excluding the hop needed to get to the source index itself)
 *  - however the best solution will only ever come from source index (5),
 *    which will get to last index in single hop
 *  - rest of them will take 2 hops (including 1 hop to get to source index itself)
 * 
 * but if we loop in naive fashion like we've done here,
 * we'll be scanning entire remaining array in each iteration,
 * resulting in O(n^2) operations
 */
vector <int> calcMinHops(vector <int> jmp) {
  vector <int> minHops(jmp.size(), INT_MAX);

  minHops[0] = 0;
  for (int i = 0; i < jmp.size() - 1; i++) {
    for (int j = 1; ((i + j) < jmp.size()) && (j <= jmp[i]); j++) {
      minHops[i + j] = min(minHops[i + j], minHops[i] + 1);
    }
  }

  return minHops;
}

void testCalcMinHopsOpt() {
  vector <int> outExpected;

  outExpected = {0, 1, 1, 1, 1, 1, 1};
  assert(calcMinHopsOpt({8, 1, 3, 7, 4, 2, 9}) == outExpected);

  outExpected = {0, 1, 1, 2, 2};
  assert(calcMinHopsOpt({2,3,1,1,4}) == outExpected);

  outExpected = {0, 1, 1, 1, INT_MAX};
  assert(calcMinHopsOpt({3,2,1,0,4}) == outExpected);
}

/**
 * here we optimize by inverting the inner loop, which enables us to 'prune'
 * unnecessary, redundant computations
 * 
 * Starting from last index up-till which a single hop can let us reach
 * from a given node,
 *  - we keep moving backwards and updating (decreasing) the hops
 *    till it is possible to do so
 *  - once we get to a node where we can no longer minimize the hops, we break
 *    out of the loop. The reasoning is that if we are unable to optimize reaching
 *    till this point, we woud naturally be unable to optimize for reaching
 *    anything closer than this
 */
vector <int> calcMinHopsOpt(vector <int> jmp) {
  vector <int> minHops(jmp.size(), INT_MAX);

  minHops[0] = 0;
  for (int i = 0; i < jmp.size() - 1; i++) {
    int jMax = min(i + jmp[i], ((int) jmp.size() - 1));

    for (int j = jMax; j >= i + 1; j--) {
      int crrHops = minHops[i] + 1;
      if (crrHops < minHops[j]) {
        minHops[j] = crrHops;
      } else {
        // this is crucial pruning step
        break;
      }
    }
  }

  return minHops;
}

void testJump() {
  vector <int> numsInp;

  numsInp = {8, 1, 3, 7, 4, 2, 9};
  assert(jump(numsInp) == 1);

  numsInp = {2,3,1,1,4};
  assert(jump(numsInp) == 2);

  numsInp = {3,2,1,0,4};
  assert(jump(numsInp) == -1);
}

int jump(vector<int>& nums) {
  // vector <int> minHops = calcMinHops(nums);
  vector <int> minHops = calcMinHopsOpt(nums);
  int len = nums.size();
  if (minHops[len - 1] == INT_MAX) {
    return -1;
  } else {
    return minHops[len - 1];
  }
}
