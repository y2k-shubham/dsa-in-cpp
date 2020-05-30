// https://www.geeksforgeeks.org/count-of-subarrays-whose-sum-is-a-perfect-square/

/*
2 3 -5 6 -7 4 -9999
Subarrays {2, 3, -5}, {-5, 6}, {3, -5, 6}, {3, -5, 6, -7, 4} and {4} with sum is 0, 1, 4, 1 and 4 repectively have perfect square sum.

3 -6 4 -2 7 -9999
{3, -6, 4}, {4}, {4, -2, 7} are the subarrays with perfect square sum.
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>

using namespace std;

vector<int> input();
void showVec(vector<int>, const char *);
vector<int> findCumSum(vector<int>);
map<int, list<pair<int, int> > > findPerfSquareSubArr(vector <int>, vector<int>, int);
void output(vector<int>, map<int, list<pair<int, int> > >);

int main() {
    vector<int> vec = input();
    showVec(vec, "vec");

    vector<int> cumSum = findCumSum(vec);
    showVec(cumSum, "cumSum");

    // min/max element of vector https://www.geeksforgeeks.org/how-to-find-the-minimum-and-maximum-element-of-a-vector-using-stl-in-c/
    int minCumSum = *min_element(cumSum.begin(), cumSum.end());
    cout << endl
         << "Min cumSum is " << minCumSum << endl;

    map<int, list<pair<int, int> > > perfSquareSubArrs = findPerfSquareSubArr(vec, cumSum, minCumSum);
    output(vec, perfSquareSubArrs);

    return 0;
}

map<int, list<pair<int, int> > > findPerfSquareSubArr(vector <int> vec, vector<int> cumSum, int minCumSum) {
    map<int, list<int> > cumSumEndIndMap;
    map<int, list<pair<int, int> > > squareIndicesMap;

    list<int> zeroIndList;
    zeroIndList.push_back(-1);
    cumSumEndIndMap[0] = zeroIndList;
    for (int i = 0; i < cumSum.size(); i++) {
        int crrCumSum = cumSum[i];
        int crrDiff;
        int sqr;
        // printf("--------\ni=%d, crrVec=vec[i=%d]=%d, crrCumSum=cumSum[i=%d]=%d\n\n", i, i, vec[i], i, crrCumSum);
        for (int j = 0; sqr = (j * j), crrDiff = crrCumSum - sqr, crrDiff >= minCumSum; j++) {
            // printf("j=%d, jSqr=%d, crrDiff=((crrCumSum=%d)-(jSqr=%d))=%d\n", j, sqr, crrCumSum, sqr, crrDiff);
            for (list<int>::iterator it = cumSumEndIndMap[crrDiff].begin(); it != cumSumEndIndMap[crrDiff].end(); it++) {
                if (squareIndicesMap.find(sqr) == squareIndicesMap.end()) {
                    list<pair<int, int> > mIndicesList;
                    squareIndicesMap[sqr] = mIndicesList;
                }
                // printf("adding index pair (%d, %d)\n", (*it + 1), i);
                squareIndicesMap[sqr].push_back(make_pair(*it + 1, i));
            }
            // cout << endl;
        }

        if (cumSumEndIndMap.find(cumSum[i]) == cumSumEndIndMap.end()) {
            list<int> mEndIndList;
            cumSumEndIndMap[crrCumSum] = mEndIndList;
        }

        // printf("\nadding entry cumSumEndIndMap[crrCumSum=%d]=%d\n", crrCumSum, i);
        cumSumEndIndMap[crrCumSum].push_back(i);
        // printf("--------\n");
    }

    return squareIndicesMap;
}

void output(vector<int> vec, map<int, list<pair<int, int> > > perfSquareSubArrs) {
    cout << endl
         << "Perfect square subarrs are:-" << endl;
    for (map<int, list<pair<int, int> > >::iterator it = perfSquareSubArrs.begin(); it != perfSquareSubArrs.end(); it++) {
        int perfSquare = (*it).first;
        printf("Perf square = %d\n", perfSquare);

        list<pair<int, int> > indices = (*it).second;
        for (list<pair<int, int> >::iterator i = indices.begin(); i != indices.end(); i++) {
            int lo = (*i).first;
            int hi = (*i).second;
            printf("vec[%d]=%d .. vec[%d]=%d\n", lo, vec[lo], hi, vec[hi]);
        }
    }
}

vector<int> input() {
    vector<int> vec;
    int ele;

    cout << "Enter elements of vec\n(-9999 to terminate)\n";
    cin >> ele;
    while (ele != -9999) {
        vec.push_back(ele);
        cin >> ele;
    }

    return vec;
}

void showVec(vector<int> vec, const char *name) {
    printf("\n%s vector is:-\n", name);

    cout << "Ind\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "Ele\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

vector<int> findCumSum(vector<int> vec) {
    vector<int> cumSum(vec.size());

    cumSum[0] = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        cumSum[i] = cumSum[i - 1] + vec[i];
    }

    return cumSum;
}
