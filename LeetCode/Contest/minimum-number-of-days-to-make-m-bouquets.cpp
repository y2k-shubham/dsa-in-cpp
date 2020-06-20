// https://leetcode.com/contest/weekly-contest-193/problems/minimum-number-of-days-to-make-m-bouquets/#
// got TLE
// dynamic programming

/*
1 10 3 10 2 -1
3 1

1 10 3 10 2 -1
3 2

7 7 7 7 12 7 7 -1
2 3

1 10 2 9 3 8 4 7 5 6 -1
4 2

1000000000 1000000000 -1
1 1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
// g++ -std=c++11 minimum-number-of-days-to-make-m-bouquets.cpp
#include <tuple>
#include <map>
#include <cstring>
#include <algorithm>


using namespace std;

tuple<vector <int>, int, int> input();
void showVec(vector <int>, const char *, int);
vector <int> findWindowMaxVec(vector <int>, int k);
void showMap(map <int, int>, const char *);

vector <vector <int> > createMat(int, int);
void initMat(vector <vector <int> >&, int);
void fillMat(vector <int>, vector <int>, int, vector <vector <int> >&);
void showSeparator(int);
void showMat(vector <int>, vector <int>, int, vector <vector <int> >, const char *);

vector <pair <int, int> > findRanges(vector <int>, int, vector <vector <int> >);
void showRangesVec(vector <pair <int, int> >);
void showRanges(vector <int>, vector <pair <int, int> >);

int main() {
  tuple <vector <int>, int, int> inputs = input();
  vector <int> bloomDay = get<0>(inputs);
  int m = get<1>(inputs);
  int k = get<2>(inputs);

  cout << endl;
  showVec(bloomDay, "bloomDay", 0);
  printf("m = %d\nk = %d\n", m, k);

  if (bloomDay.size() < m * k) {
    printf("\nWe can't make m=%d bouquets of k=%d flowers each with %d flowers\n", m, k, ((int) bloomDay.size()));
    return 0;
  }

  vector <int> windowMaxVec = findWindowMaxVec(bloomDay, k);
  showVec(windowMaxVec, "windowMaxVec", 0);

  int rows = m + 1;
  int cols = (int) bloomDay.size() + 1;
  vector <vector <int> > mat = createMat(rows, cols);
  initMat(mat, k);
  showMat(bloomDay, windowMaxVec, k, mat, "after init, mat");

  fillMat(bloomDay, windowMaxVec, k, mat);
  showMat(bloomDay, windowMaxVec, k, mat, "after filling, mat");

  printf("\nMin days to make m=%d bouquets of k=%d flowers each are %d\n", m, k, mat[rows - 1][cols - 1]);

  vector <pair <int, int> > ranges = findRanges(bloomDay, k, mat);
  // showRangesVec(ranges);
  showRanges(bloomDay, ranges);

  return 0;
}

tuple <vector <int>, int, int> input() {
  vector <int> bloomDay;
  int m;
  int k;

  int ele;
  printf("Enter elements of vector bloomDay:-\n(-1 to terminate)\n");
  cin >> ele;
  while (ele != -1) {
    bloomDay.push_back(ele);
    cin >> ele;
  }

  printf("Enter 'm' (no of bouquets): ");
  cin >> m;

  printf("Enter 'k' (no of adjacent flowers needed in bouquet): ");
  cin >> k;

  return make_tuple(bloomDay, m, k);
}

void showVec(vector <int> vec, const char * name, int skipTabs) {
  if (name != NULL) {
    printf("\n%s vector is:-\n", name);
  }

  cout << "Ind:\t";
  for (int i = 1; i <= skipTabs; i++) {
    cout << "\t";
  }
  for (int i = 0; i < vec.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  cout << "Val:\t";
  for (int i = 1; i <= skipTabs; i++) {
    cout << "\t";
  }
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] < 0) {
      printf("\t");
    } else {
      printf("%d\t", vec[i]);
    }
  }
  cout << endl;
}

void showMap(map <int, int> myMap, const char * name) {
  cout << "Ind:\t";
  for (int i = 0; i < myMap.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  for (map<int, int>::iterator it = myMap.begin(); it != myMap.end(); it++) {
    printf("%d=> %d\t", (*it).first, (*it).second);
  }
  cout << endl;
}

vector <int> findWindowMaxVec(vector <int> vec, int k) {
  map <int, int> freqMap;
  vector <int> windowMax;

  // printf("\n++++++\npreliminary loop:-\n");
  for (int i = 0; i < k; i++) {
    if (freqMap.find(vec[i]) == freqMap.end()) {
      freqMap[vec[i]] = 1;
    } else {
      freqMap[vec[i]]++;
    }

    windowMax.push_back(-1);
    // printf("after i=%d, bloomDay[%d]=%d\n", i, i, vec[i]);
    // showMap(freqMap, "freqMap");
  }
  windowMax.pop_back();
  windowMax.push_back((*(--freqMap.end())).first);

  // printf("\n++++++\nactual sliding-window loop:-\n");
  for (int i = k; i < vec.size(); i++) {
    int outgoingNum = vec[i - k];
    int incomingNum = vec[i];

    if (freqMap.find(incomingNum) == freqMap.end()) {
      freqMap[incomingNum] = 1;
    } else {
      freqMap[incomingNum]++;
    }

    if (freqMap[outgoingNum] == 1) {
      freqMap.erase(outgoingNum);
    } else {
      freqMap[outgoingNum]--;
    }

    windowMax.push_back((*(--freqMap.end())).first);

    // cout << "---------" << endl;
    // printf("after i=%d, bloomDay[%d]=%d\n", i, i, vec[i]);

    // showVec(vec, "bloomDay", 0);
    // cout << endl;

    // showVec(windowMax, "windowMax", k - 1);
    // cout << endl;
    
    // showMap(freqMap, "freqMap");
    // cout << "---------" << endl;
  }

  return windowMax;
}

vector <vector <int> > createMat(int rows, int cols) {
  vector <vector <int> > mat(rows);
  for (int i = 0; i < rows; i++) {
    vector <int> row(cols);
    mat[i] = row;
  }
  return mat;
}

void initMat(vector <vector <int> > &mat, int k) {
  for (int j = 0; j < mat[0].size(); j++) {
    mat[0][j] = 0;
  }
  for (int i = 1; i < mat.size(); i++) {
    for (int j = 0; j < mat[0].size(); j++) {
      if (j < (i*k)) {
        mat[i][j] = 0;
      } else {
        mat[i][j] = -1;
      }
    }
  }
}

void showSeparator(int cols) {
  for (int j = 0; j <= cols; j++) {
    printf("--------");
  }
  cout << endl;
}

void showMat(vector <int> bloomDay, vector <int> windowMax, int k, vector <vector <int> > mat, const char * name) {
  printf("\n%s[][] is:-\n", name);

  showVec(windowMax, NULL, 1);
  showSeparator(mat[0].size());
  showVec(bloomDay, NULL, 1);
  showSeparator(mat[0].size());

  cout << "\t";
  for (int j = 0; j < mat[0].size(); j++) {
    printf("[%d]\t", j);
  }
  cout << endl;

  for (int i = 0; i < mat.size(); i++) {
    printf("[%d]\t", i);
    for (int j = 0; j < mat[0].size(); j++) {
      if (mat[i][j] == -1) {
        printf("\t");
      } else {
        printf("%d\t", mat[i][j]);
      }
    }
    cout << endl;
  }
}

void fillMat(vector <int> bloomDay, vector <int> windowMax, int k, vector <vector <int> >& mat) {
  char msg[50];
  for (int i = 1; i < mat.size(); i++) {
    for (int j = i*k; j < mat[0].size(); j++) {
      // printf("\nfilling mat[i=%d][j=%d]\n", i, j);
      if (j == i*k) {
        mat[i][j] = max(mat[i - 1][j - k], windowMax[j - 1]);
        // printf("forcefully picki bloomDay[j-1=%d] = %d, cost is max(mat[i-1=%d][j-k=%d], windowMax[j-1=%d]) = max(%d, %d) = %d\n", (j - 1), bloomDay[j - 1], (i - 1), (j - k), j, mat[i - 1][j - k], windowMax[j - 1], mat[i][j]);
      } else {
        mat[i][j] = min(mat[i][j - 1], max(mat[i - 1][j - k], windowMax[j - 1]));
        // printf("if we don't pick bloomDay[j-1=%d] = %d, cost is mat[i=%d][j-1=%d] = %d\n", (j - 1), bloomDay[j - 1], i, (j - 1), mat[i][j - 1]);
        // printf("if we       pick bloomDay[j-1=%d] = %d, cost is max(mat[i-1=%d][j-k=%d], windowMax[j-1=%d]) = max(%d, %d) = %d\n", (j - 1), bloomDay[j - 1], (i - 1), (j - k), j, mat[i - 1][j - k], windowMax[j - 1], max(mat[i - 1][j - k], windowMax[j - 1]));
      }
      // printf("coclusively, mat[i=%d][j=%d] = %d\n", i, j, mat[i][j]);

      // printf("\nafter filling at i=%d, j=%d\n", i, j);
      // showMat(bloomDay, windowMax, k, mat, "mat");

      // printf("\n///////////////////////////////////\n");
    }
  }
}

vector <pair <int, int> > findRanges(vector <int> bloomDay, int k, vector <vector <int> > mat) {
  // cout << endl;
  vector<pair <int, int> > ranges;

  int rows = mat.size();
  int cols = mat[0].size();
  for (int i = rows - 1, j = cols - 1; i > 0 && j > 0; ) {
    // printf("at mat[i=%d][j=%d] = %d, comparing it to mat[i=%d][j-k=%d] = %d\n", i, j, mat[i][j], i, (j - k), mat[i][j - k]);
    if (mat[i][j] != mat[i][j - k]) {
      // printf("unequal: picking range bl[%d] = %d .. bl[%d] = %d\n", (j - k), bloomDay[j - k], (j - 1), bloomDay[j - 1]);
      ranges.push_back(make_pair(j - k, j - 1));
      i--;
      j -= k;
    } else {
      // printf("equal  : decrementing j\n");
      j--;
    }
    // cout << "---------" << endl;
  }

  reverse(ranges.begin(), ranges.end());
  return ranges;
}

void showRangesVec(vector <pair <int, int> > ranges) {
  printf("\nRanges are:-\n");
  
  printf("Ind:\t");
  for (int i = 0; i < ranges.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  printf("Ranges:\t");
  for (int i = 0; i < ranges.size(); i++) {
    printf("(%d, %d)\t", ranges[i].first, ranges[i].second);
  }
  cout << endl;
}

void showRanges(vector <int> bloomDay, vector <pair <int, int> > ranges) {
  printf("\nThe picked ranges are:-\n");

  showVec(bloomDay, NULL, 0);

  int k = ranges[0].second - ranges[0].first + 1;

  int crrRangeInd = 0;
  pair <int, int> crrRange = ranges[crrRangeInd];
  cout << "\t";
  for (int j = 0; j < bloomDay.size(); j++) {
    if (j < crrRange.first) {
      printf("\t");
    } else if (crrRange.second < j) {
      printf("\t");
    } else {
      if (k == 1) {
        printf("(%d)\t", crrRangeInd + 1);
        crrRangeInd++;
        if (crrRangeInd < ranges.size()) {
          crrRange = ranges[crrRangeInd];
        }
      } else {
        if (crrRange.first == j) {
          printf("(s=%d\t", crrRangeInd + 1);
        } else if (crrRange.first < j && j < crrRange.second) {
          printf("^\t");
        } else if (j == crrRange.second) {
          printf("e=%d)\t", crrRangeInd + 1);
          crrRangeInd++;
          if (crrRangeInd < ranges.size()) {
            crrRange = ranges[crrRangeInd];
          }
        }
      }
    }
  }
  cout << endl;
}
