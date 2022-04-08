// LeetCode-703: https://leetcode.com/problems/kth-largest-element-in-a-stream/
// incomplete: problem not clear

#include <map>
#include <vector>
#include <cassert>

using namespace std;

class KthLargest {
private:
    int k;
    map<int, int> freqMap;
    pair<int, int> kthLargestRef;

    void createFreqMap(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }
    }

    void findKthLargestEle() {
        int numEles = 0;

        for (
                map<int, int>::iterator it = freqMap.begin();
                it != freqMap.end();
                it++
                ) {
            int crrEle = it->first;
            int crrEleFreq = it->second;

            if ((numEles + crrEleFreq) >= k) {
                kthLargestRef.first = crrEle;
                kthLargestRef.second = k - numEles;
                break;
            }

            numEles += crrEleFreq;
        }
    }

public:
    friend class KthLargestTest;

    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        createFreqMap(nums);
        findKthLargestEle();
    }

    int add(int val) {
        freqMap[val]++;

        int crrKthLargestEle = kthLargestRef.first;
        if (val < crrKthLargestEle) {
            if (kthLargestRef.second > 1) {
                kthLargestRef.second--;
            } else {
                map<int, int>::iterator it = freqMap.find(crrKthLargestEle);
                it--;
                kthLargestRef.first = it->first;
                kthLargestRef.second = it->second;
            }
        }

        int eleToReturn = kthLargestRef.first;
        freqMap[kthLargestRef.first]--;
        map <int, int>::iterator it = freqMap.find(eleToReturn);
        if (kthLargestRef.second == 1) {
            it--;
            kthLargestRef.first = it->first;
            kthLargestRef.second = it->second;
        } else {
            kthLargestRef.second--;
        }
        freqMap[eleToReturn]--;
        if (freqMap[eleToReturn] == 0) {
            freqMap.erase(eleToReturn);
        }

        return kthLargestRef.first;
    }
};

class KthLargestTest {
public:
    void testFindKthLargestEle() {
        int kIn;
        vector<int> vecIn;
        pair<int, int> kthLargestOutExpected;
        pair<int, int> kthLargestOutComputed;
        KthLargest soln = KthLargest(kIn, vecIn);

        vecIn = {8, 1, 3, 7, 1, 4, 8, 2, 9, 3};
        soln.createFreqMap(vecIn);

        kIn = 1;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {1, 1};
        kthLargestOutComputed = soln.kthLargestRef;
//        printf("(%d, %d)\n", kthLargestOutComputed.first, kthLargestOutComputed.second);
        assert(kthLargestOutExpected == kthLargestOutComputed);

        kIn = 2;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {1, 2};
        kthLargestOutComputed = soln.kthLargestRef;
//        printf("(%d, %d)\n", kthLargestOutComputed.first, kthLargestOutComputed.second);
        assert(kthLargestOutExpected == kthLargestOutComputed);

        kIn = 3;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {2, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        kIn = 4;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {3, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        kIn = 5;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {3, 2};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        kIn = 6;
        soln.k = kIn;
        soln.findKthLargestEle();
        kthLargestOutExpected = {4, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);
    }

    void testAdd() {
        int kIn;
        vector<int> vecIn;
        pair<int, int> kthLargestOutExpected;
        pair<int, int> kthLargestOutComputed;
        int outExpected, outComputed;
        KthLargest soln = KthLargest(kIn, vecIn);

        vecIn = {4, 5, 8, 2};
        soln.createFreqMap(vecIn);
        kIn = 3;
        soln.k = kIn;

        // [2, 4, 5, 8]
        soln.findKthLargestEle();
        kthLargestOutExpected = {5, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        outComputed = soln.add(3);
        // [2, 3, 4, 5, 8]
        outExpected = 4;
        assert(outExpected == outComputed);
        kthLargestOutExpected = {4, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        outComputed = soln.add(5);
        // [2, 3, 4, 5, 5, 8]
        outExpected = 4;
        assert(outExpected == outComputed);
        kthLargestOutExpected = {4, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);

        outComputed = soln.add(5);
        // [2, 3, 4, 5, 5, 8]
        outExpected = 4;
        assert(outExpected == outComputed);
        kthLargestOutExpected = {4, 1};
        kthLargestOutComputed = soln.kthLargestRef;
        assert(kthLargestOutExpected == kthLargestOutComputed);
    }
};

int main() {
    KthLargestTest solnTest = KthLargestTest();

    solnTest.testFindKthLargestEle();
    solnTest.testAdd();

    return 0;
}
