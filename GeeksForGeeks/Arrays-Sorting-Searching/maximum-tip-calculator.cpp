// Amazon Interview Question
// https://practice.geeksforgeeks.org/problems/maximum-tip-calculator/0

/*
5 3 3
1 2 3 4 5
5 4 3 2 1

8 4 4
1 4 3 2 7 5 9 6 
1 2 3 6 5 4 9 8
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

using namespace std;
#define MAX 110

void inputVec(vector <int>&, int, const char *);
void outputVec(vector <int>, const char *);
void outputVec(vector <pair <int, int> >, const char *);
void findDiff(vector <int>, vector <int>, vector <pair <int, int> >&);
bool comparator(const pair <int, int>&, const pair <int, int>&);
void findCumSum(vector <pair <int, int> >, int, int, vector <int>&);
void negateVec(vector <int>&);
int findInflexionIndex(vector <int>, vector <int>);
void createIndSet(vector <pair <int, int> >, int, int, set <int>&);
void showResult(vector <int>, set <int>, vector <int>, set <int>);

int main() {
  int N;
  int X, Y;
  int T;

  cin >> N >> X >> Y;

  vector <int> A(N), B(N);
  vector <pair <int, int> > diffAB(N);
  vector <int> cumSumLeft(N), cumSumRight(N);
  set <int> setA, setB;

  inputVec(A, N, "A");
  outputVec(A, "A");

  inputVec(B, N, "B");
  outputVec(B, "B");

  findDiff(A, B, diffAB);
  outputVec(diffAB, "Before sorting, diffAB");

  sort(diffAB.begin(), diffAB.end(), comparator);
  outputVec(diffAB, "After  sorting, diffAB");

  findCumSum(diffAB, 0, N - 1, cumSumLeft);
  outputVec(cumSumLeft, "cumSumLeft");

  findCumSum(diffAB, N - 1, 0, cumSumRight);
  negateVec(cumSumRight);
  outputVec(cumSumRight, "cumSumRight");

  int infInd = ((X + Y) == N) ? (X - 1) : findInflexionIndex(cumSumLeft, cumSumRight);
  printf("\nInflexion index = %d\n", infInd);

  createIndSet(diffAB, 0, infInd, setA);
  createIndSet(diffAB, infInd + 1, N - 1, setB);

  showResult(A, setA, B, setB);

  return 0;
}

void inputVec(vector <int>& vec, int len, const char * name) {
  printf("\nEnter vector %s:-\n", name);
  for (int i = 0; i < len; i++) {
    cin >> vec[i];
  }
}

void outputVec(vector <int> vec, const char * name) {
  int len = vec.size();
  printf("\n%s vec is:-", name);

  printf("\nInd:\t");
  for (int i = 0; i < len; i++) {
    printf("[%d]\t", i);
  }

  printf("\nVal:\t");
  for (int i = 0; i < len; i++) {
    printf("%d\t", vec[i]);
  }

  cout << endl;
}

void outputVec(vector <pair <int, int> > diff, const char * name) {
  int len = diff.size();
  printf("\n%s vec is:-", name);

  printf("\nInd:\t");
  for (int i = 0; i < len; i++) {
    printf("[%d]\t", i);
  }

  printf("\nDiff:\t");
  for (int i = 0; i < len; i++) {
    printf("%d\t", diff[i].first);
  }

  printf("\nPos:\t");
  for (int i = 0; i < len; i++) {
    printf("(%d)\t", diff[i].second);
  }

  cout << endl;
}

void findDiff(vector <int> A, vector <int> B, vector <pair <int, int> >& diffAB) {
  for (int i = 0; i < A.size(); i++) {
    diffAB[i] = make_pair(A[i] - B[i], i);
  }
}

bool comparator(const pair <int, int>& p1, const pair <int, int>& p2) {
  if (p1.first == p2.first) {
    return p1.second <= p2.second;
  } else {
    return p1.first >= p2.first;
  }
}

void findCumSum(vector <pair <int, int> > vec, int start, int end, vector <int>& cumSum) {
  int diff = (start < end) ? 1 : -1;

  cumSum[start] = vec[start].first;
  for (int i = start + diff; i != end; i += diff) {
    cumSum[i] = cumSum[i - diff] + vec[i].first;
  }
}

void negateVec(vector <int>& vec) {
  for (int i = 0; i < vec.size(); i++) {
    vec[i] *= -1;
  }
}

int findInflexionIndex(vector <int> cumSumLeft, vector <int> cumSumRight) {
  int len = cumSumLeft.size();

  int maxSum = -1;
  int maxSumInd = -1;

  for (int i = -1; i < len; i++) {
    int vLeft = (i >= 0) ? cumSumLeft[i] : 0;
    int vRight = ((i + 1) < len) ? cumSumRight[i + 1] : 0;
    int crrSum = vLeft + vRight;

    if (crrSum > maxSum) {
      crrSum = maxSum;
      maxSumInd = i;
    }
  }

  return maxSumInd;
}

void createIndSet(vector <pair <int, int> > vec, int start, int end, set <int>& indSet) {
  for (int i = start; i <= end; i++) {
    indSet.insert(vec[i].second);
  }
}

void showResult(vector <int> vecA, set <int> setA, vector <int> vecB, set <int> setB) {
  int len = vecA.size();

  printf("\nActual selection of tasks is:-\n");

  printf("Ind:\t");
  for (int i = 0; i < len; i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  printf("Boy:\t");
  for (int i = 0; i < len; i++) {
    char person = (setA.find(i) != setA.end()) ? 'A' : 'B';
    printf("%c\t", person);
  }
  cout << endl;

  printf("Tip:\t");
  for (int i = 0; i < len; i++) {
    int tip = (setA.find(i) != setA.end()) ? vecA[i] : vecB[i];
    printf("%d\t", tip);
  }
  cout << endl;
}
