// https://www.interviewbit.com/problems/min-steps-in-infinite-grid/
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int minMoves(int, int, int, int);
int coverPoints(vector <int>, vector <int>);

int main() {
  cout << minMoves(1, 0, -1, 5);
}

int coverPoints(vector <int> &x, vector <int> &y) {
  int sum = 0;
  
  for (int i = 0; i < x.size() - 1; i++) {
    sum += minMoves(x[i], y[i], x[i + 1], y[i + 1]);
  }

  return sum;
}

int minMoves(int p1x, int p1y, int p2x, int p2y) {
  int delX = abs(p2x - p1x);
  int delY = abs(p2y - p1y);

  if (delX == delY) {
    return delX;
  } else {
    int diagonalMoves = min(delX, delY);
    int linearMoves = max(delX, delY) - diagonalMoves;

    return (diagonalMoves + linearMoves);
  }
}
