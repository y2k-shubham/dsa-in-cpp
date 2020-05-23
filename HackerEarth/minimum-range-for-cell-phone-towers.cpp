// https://stackoverflow.com/questions/53473661/
/*
Incorrect
1. Will give correct value of rmin for sufficiently small epsilon
2. Will NOT give correct values of tx[]
*/

/*
4
0.2 0.5 1.5 2.2
2

8
1     4   6   8 9  11  13 14
5

8
1     4   6   8 9  11  13 14
4
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <utility>

using namespace std;

void input(vector <float>&, int&);
void output(float, vector <float>);
void showVec(vector <float>);
pair <float, vector <float> > getReffAndTxInitial(vector <float>, int);
pair <float, vector <float> > getReffAndTx(vector <float>, int, float);

int main() {
  int k;
  vector <float> hx;

  // input
  input(hx, k);
  sort(hx.begin(), hx.end());

  // show input
  cout << endl << "Coordinates of houses hx:-";
  showVec(hx);
  cout << "No of towers k: " << k << endl;

  float rmin = FLT_MAX;
  vector <float> tx;
  if (k < hx.size()) {
    pair <float, vector <float> > resPair;

    // get initial distribution
    resPair = getReffAndTxInitial(hx, k);
    rmin = resPair.first;
    tx = resPair.second;

    // show initial distribution
    cout << endl << "-----" << 0 << "-----";
    output(rmin, tx);

    // declare variables for iteration
    float rlo = 0.0f;
    float rhi = 2 * rmin;
    float epsilon = 0.01f;

    float rmidPrev = -rhi;
    float rmidCrr = ((rlo + rhi) / 2);
    int ctr = 1;
    while(fabsf(rmidCrr - rmidPrev) >= epsilon) {
      rmidPrev = rmidCrr;
      float rmid = (rlo + rhi) / 2;

      // show intermediate values
      cout << endl << "-----" << ctr++ << "-----" << endl;
      printf("rlo = %4.2f\n", rlo);
      printf("rhi = %4.2f\n", rhi);
      printf("rmid = %4.2f\n", rmid);

      // get intermediate distribution
      // and update bounds
      resPair = getReffAndTx(hx, k, rmid);
      if (resPair.first < FLT_MAX) {
        rmin = min(rmin, resPair.first);
        tx = resPair.second;
        rhi = rmin;
      } else {
        rlo = rmid;
      }

      // show intermediate distribution
      output(rmin, tx);

      // recalculate rMidCrr for termination
      rmidCrr = ((rlo + rhi) / 2);
    }
  } else {
    rmin = 0.0f;
    tx = hx;
  }

  // final output
  cout << endl << "-----" << "Final" << "-----";
  output(rmin, tx);

  return 0;
}

void input(vector <float>& hx, int& k) {
  int n;

  cout << "Enter no of houses n: ";
  cin >> n;

  cout << "Enter coordinates of houses:-" << endl;
  for (int i = 0; i < n; i++) {
    float hxi;
    cin >> hxi;
    hx.push_back(hxi);
  }

  cout << "Enter no of towers k: ";
  cin >> k;
}

void output(float rmin, vector <float> tx) {
  printf("\nrMin is %4.2f\n", rmin);

  cout << "tx positions are:-";
  showVec(tx);
}

void showVec(vector <float> vec) {
  cout << endl << "Ind:\t";
  for (int i = 0; i < vec.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  cout << "Val:\t";
  for (int i = 0; i < vec.size(); i++) {
    printf("%4.2f\t", vec[i]);
  }
  cout << endl;
}

pair <float, vector <float> > getReffAndTxInitial(vector <float> hx, int k) {
  vector <float> tx;
  float reff = (hx.back() - hx.front()) / (k + 1);
  
  for (int j = 1; j <= k; j++) {
    float txj = reff * j;
    tx.push_back(txj);
  }

  return make_pair(reff, tx);
}

pair <float, vector <float> > getReffAndTx(vector <float> hx, int k, float r) {
  int i = 0;
  int j = 0;
  
  float reff = FLT_MIN;

  int tPlaced = 0;
  vector <float> tx;

  while ((i < hx.size()) && (tPlaced < k)) {
    tPlaced++;

    float hxjf = hx[i];
    float hxjl = hx[i];
    float txj = hxjf + r;
    while ((i < hx.size()) && (hx[i] < (txj + r))) {
      hxjl = hx[i];
      i++;
    }

    txj = (hxjf + hxjl) / 2;
    tx.push_back(txj);
    reff = max(reff, (txj - hxjf));
  }

  if (i == hx.size()) {
    return make_pair(reff, tx);
  } else {
    vector <float> emptyVec;
    return make_pair(FLT_MAX, emptyVec);
  }
}
