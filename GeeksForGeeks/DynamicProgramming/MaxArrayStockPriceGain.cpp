#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100
#define maxOf(a, b) ((a > b) ? a : b)
#define minOf(a, b) ((a < b) ? a : b)

struct result {
    int sDay;
    int eDay;
    int diff;
    int minInd;
    int maxInd;
};

void input(int *, int *);
void showList(int *, int);
result findResult(int *, int, int);
void output(int *, result);
void showSubArray(int *, int, int);
void showResult(int *, result);

int main() {
    int prices[MAX];
    int len;
    result res;

    input(&prices[0], &len);
    //showList(&prices[0], len);
    printf("\n");
    res = findResult(&prices[0], 0, (len - 1));
    output(&prices[0], res);

    return 0;
}

void input(int * prices, int * len) {
    int i;

    cout << "Enter the length of stock-prices list:\t";
    cin >> (* len);

    cout << "Enter the stock price list:-\n";
    for (i = 0; i < (* len); i++) {
        cin >> prices[i];
    }
}

void showList(int * prices, int len) {
    int i;

    printf("\nThe stock price list is:-\n");
    for (i = 0; i < len; i++) {
        printf("%d\t", prices[i]);
    }
    printf("\n");
}

result findResult(int * arr, int lo, int hi) {
    //cout << "lo = " << lo << "\thi = " << hi << "\tstarted" << endl;
    if ((hi - lo) <= 1) {
        result thresholdResult;

        thresholdResult.sDay = lo;
        thresholdResult.eDay = hi;
        thresholdResult.diff = arr[hi] - arr[lo];
        thresholdResult.maxInd = (arr[lo] > arr[hi]) ? lo : hi;
        thresholdResult.minInd = (arr[lo] < arr[hi]) ? lo : hi;

        //cout << "lo = " << lo << "\thi = " << hi << "\tterminated" << endl;
        //showSubArray(arr, lo, hi);
        //showResult(arr, thresholdResult);
        //printf("\n");

        return thresholdResult;
    } else {
        int mid;
        result lResult;
        result rResult;
        result fResult;

        mid = (lo + hi) / 2;
        lResult = findResult(arr, lo, mid);
        rResult = findResult(arr, (mid + 1), hi);

        if ((arr[rResult.maxInd] - arr[lResult.minInd]) > maxOf(lResult.diff, rResult.diff)) {
            //printf("if-executed\n");
            fResult.minInd = lResult.minInd;
            fResult.maxInd = rResult.maxInd;
            fResult.sDay = lo;
            fResult.eDay = hi;
            fResult.diff = arr[rResult.maxInd] - arr[lResult.minInd];
        } else if (lResult.diff > rResult.diff) {
            //printf("else-if executed\n");
            fResult = lResult;
        } else {
            //printf("else executed\n");
            fResult = rResult;
        }

        //cout << "lo = " << lo << "\thi = " << hi << "\tterminated" << endl;
        //showSubArray(arr, lo, hi);
        //showResult(arr, fResult);
        //printf("\n");

        return fResult;
    }
}

void showResult(int * arr, result res) {
    printf("min:\tarr[%d] = %d\t\tmax:\tarr[%d] = %d\t\tdiff = %d\n", res.minInd, arr[res.minInd], res.maxInd, arr[res.maxInd], res.diff);
}

void showSubArray(int * arr, int lo, int hi) {
    int i;

    cout << "SubArray:\t";
    for (i = lo; i <= hi; i++) {
        printf("%d\t", arr[i]);
    }
    cout << endl;
}

void output(int * arr, result res) {
    printf("\nThe period with maximum stock prices rise is:-\n");
    printf("Buy:\tDay = %d\t\tPrice = %d\n", res.minInd, arr[res.minInd]);
    printf("Sell:\tDay = %d\t\tPrice = %d\n", res.maxInd, arr[res.maxInd]);
    cout << "Gain:\t" << res.diff << endl;
}
