// LeetCode-1726: https://leetcode.com/problems/tuple-with-same-product/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    int findComplement(vector<int>& vec, int reqProd, int div, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        int crrProd = div * midEle;
        if (crrProd > reqProd) {
            return findComplement(vec, reqProd, div, lo, mid - 1);
        } else if (crrProd == reqProd) {
            return mid;
        } else {
            return findComplement(vec, reqProd, div, mid + 1, hi);
        }
    }

    int nC2(int n) {
        return (n * (n - 1)) / 2;
    }

    list<pair<int, int> > findTuplesWithProd(vector<int>& vec, int reqProd, int lo, int hi) {
        int remLen = hi - lo + 1;
        if (remLen < 2) {
            return {};
        }

        list<pair<int, int> > tuples;

        for (int i = lo; i < hi; i++) {
            int div = vec[i];

            int complementIdx = findComplement(vec, reqProd, div, i + 1, hi);
            if (complementIdx > 0) {
                tuples.push_back({i, complementIdx});
            }
        }

        return tuples;
    }

    void showTuples(vector<int>& vec, int prod, list<pair<int, int> >& indTuples) {
        printf("prod=%d : ", prod);
        for (list<pair<int, int> >::iterator i = indTuples.begin(); i != indTuples.end(); i++) {
            printf("v[%d]=%d x v[%d]=%d, ", i->first, vec[i->first], i->second, vec[i->second]);
        }
        cout << endl;
    }

    // wrong : it misses out pairs
    // sample breaking case [1,2,4,8,16,32,64]
    int findNumTuples1(vector<int>& vec, unordered_set<int>& consideredProds, int left, int right) {
        int remLen = right - left + 1;
        if (remLen < 4) {
            return 0;
        }

        int crrProd = vec[left] * vec[right];

        int numTuples = 1;
        if (consideredProds.find(crrProd) == consideredProds.end()) {
            list<pair<int, int> > indTuples = findTuplesWithProd(vec, crrProd, left + 1, right - 1);
            indTuples.push_front({left, right});

            showTuples(vec, crrProd, indTuples);

            numTuples = indTuples.size();
            //printf("findTuplesWithProd(vec, crrProd=%d, left+1=%d, right-1=%d).size() = %d\n", crrProd, (left + 1), (right - 1), (numTuples - 1));
            consideredProds.insert(crrProd);
        }

        int crrProdPermutations = 0;
        if (numTuples > 1) {
            crrProdPermutations = nC2(numTuples) * 8;
        }

        return crrProdPermutations +
               findNumTuples1(vec, consideredProds, left, right - 1) +
               findNumTuples1(vec, consideredProds, left + 1, right);
    }

    // slow: it runs into TLE;
    // time complexity O(n^3 * logn) [n^2 possible products, nlogn search time per product]
    int findNumTuples2(vector<int>& vec, unordered_set<int>& consideredProds) {
        int len = vec.size();

        int numTuplesTotal = 0;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                int crrProd = vec[i] * vec[j];

                if (consideredProds.find(crrProd) != consideredProds.end()) {
                    continue;
                }
                consideredProds.insert(crrProd);

                list<pair<int, int> > tuplesCrrProd = findTuplesWithProd(vec, crrProd, 0, len - 1);
                int numTuplesCrrProd = tuplesCrrProd.size();
                if (numTuplesCrrProd > 1) {
                    numTuplesTotal += nC2(numTuplesCrrProd) * 8;
                }
            }
        }

        return numTuplesTotal;
    }

    // slow: it runs into TLE
    // time complexity O(n^3) [assuming searching unordered_set is amortized O(1)]
    int findNumTuples3(vector<int>& vec, unordered_set<int>& consideredProds) {
        unordered_set<int> vecSet(vec.begin(), vec.end());

        int len = vec.size();

        int numTuplesTotal = 0;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                int crrProd = vec[i] * vec[j];

                if (consideredProds.find(crrProd) != consideredProds.end()) {
                    continue;
                }
                consideredProds.insert(crrProd);

                int crrProdSqrt = (int)ceil(sqrt(crrProd));
                int numTuplesCrrProd = 0;
                int crrEle;
                for (int k = 0; crrEle = vec[k], crrEle < crrProdSqrt; k++) {
                    if (((crrProd % crrEle) == 0) && (vecSet.find(crrProd / crrEle) != vecSet.end())) {
                        numTuplesCrrProd++;
                    }
                }

                if (numTuplesCrrProd > 1) {
                    numTuplesTotal += nC2(numTuplesCrrProd) * 8;
                }
            }
        }

        return numTuplesTotal;
    }

   public:
    int tupleSameProduct(vector<int>& nums) {
        int len = nums.size();
        if (len <= 3) {
            return 0;
        }

        sort(nums.begin(), nums.end());
        unordered_set<int> consideredProds;

        // wrong : it misses out pairs
        // sample breaking case [1,2,4,8,16,32,64]
        // return findNumTuples1(nums, consideredProds, 0, len - 1);

        // slow: it runs into TLE
        // time complexity O(n^3 * logn) [n^2 possible products, nlogn search time per product]
        // return findNumTuples2(nums, consideredProds);

        // slow: it runs into TLE
        // time complexity O(n^3) [assuming searching unordered_set is amortized O(1)]
        return findNumTuples3(nums, consideredProds);
    }
};
