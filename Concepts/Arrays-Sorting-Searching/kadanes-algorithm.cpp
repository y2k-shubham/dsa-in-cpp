// Tech Dose: https://www.youtube.com/watch?v=YxuK6A3SvTs
// GFG: https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

// normal
int impl1(int arr[], int n) {
    int maxSum = 0;

    int crrSum = 0;
    for (int i = 0; i < n; i++) {
        crrSum = crrSum + arr[i];
        if (crrSum < 0) {
            crrSum = arr[i];
        }

        maxSum = max(maxSum, crrSum);

        if (crrSum < 0) {
            crrSum = 0;
        }
    }

    return maxSum;
}

// tech-dose
int impl2(int arr[], int n) {
    int maxSoFar = INT_MIN;

    int maxEndingHere = 0;
    for (int i = 0; i < n; i++) {
        maxEndingHere = maxEndingHere + arr[i];
        if (maxEndingHere < arr[i]) {
            maxEndingHere = arr[i];
        }

        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }
    }

    return maxSoFar;
}

// Function to find subarray with maximum sum
// arr: input array
// n: size of array
int maxSubarraySum(int arr[], int n) {
    // Your code here
    return impl2(arr, n);
}
