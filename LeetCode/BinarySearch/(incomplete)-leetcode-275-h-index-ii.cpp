// LeetCode-275: https://leetcode.com/problems/h-index-ii/
// incomplete

#include <vector>

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size();
        if (len <= 0) {
            return 0;
        }
        if (len == 1) {
            return (citations[0] >= 1) ? 1 : 0;
        }

        int maxHIndex = 0;

        int lo = 0;
        int hi = len - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            int numCrrCitations = citations[mid];
            // printf("\nv[lo=%d]=%d, v[mid=%d]=%d, v[hi=%d]=%d\n", lo, citations[lo], mid, numCrrCitations, hi, citations[hi]);

            int numGreaterOrEqualCitations = hi - mid + 1;
            if (numCrrCitations >= numGreaterOrEqualCitations) {
                int crrHIndex = min(numCrrCitations, numGreaterOrEqualCitations);
                // printf("numCrrCitations=%d >= numGreaterOrEqualCitations=%d = true\n", numCrrCitations, numGreaterOrEqualCitations);
                maxHIndex = max(maxHIndex, crrHIndex);
                lo = mid + 1;
                // printf("got _hIndex=%d, updated lo=(mid=%d+1)=%d\n", _hIndex, mid, lo);
            } else {
                hi = mid - 1;
                // printf("numCrrCitations=%d >= numGreaterOrEqualCitations=%d = false\n", numCrrCitations, numGreaterOrEqualCitations);
                // printf("updated hi=(mid=%d-1)=%d\n", mid, hi);
            }
        }

        return maxHIndex;
    }
};
