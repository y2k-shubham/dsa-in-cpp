// LeetCode-1696: https://leetcode.com/problems/jump-game-vi/
// gives SEGFAULT on LC; otherwise basic test-cases are passing

#include <cstdio>
#include <string>
#include <unordered_map>
#include <utility>
#include <set>
#include <vector>
#include <queue>
#include <cassert>
#include <list>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    void showSet(set<pair<int, int>>& mSet, string name) {
        printf("%s set is:-\n", name.c_str());
        for (auto& p: mSet) {
            printf("(%d, %d) ", p.first, p.second);
        }
        printf("\n");
    }

    pair<set<pair<int, int> >, queue<pair<int, int> > > createKWindowMaxScoresSet(vector<int>& vec, int k) {
        int len = vec.size();

        set<pair<int, int> > kWindowMaxScoresSet;
        queue<pair<int, int> > kWindowMaxScoresQue;
        kWindowMaxScoresSet.insert({-vec[0], 0});
        kWindowMaxScoresQue.push({-vec[0], 0});

        for (int i = 1; i < k; i++) {
            pair<int, int> maxPrecedingScore = *(kWindowMaxScoresSet.begin());

            int maxCrrScore = (-maxPrecedingScore.first) + vec[i];
            kWindowMaxScoresSet.insert({-maxCrrScore, i});
            kWindowMaxScoresQue.push({-maxCrrScore, i});
        }

        return {kWindowMaxScoresSet, kWindowMaxScoresQue};
    }

    int findMaxEndScore(
            vector<int>& vec, int k,
            set<pair<int, int> >& kWindowMaxScoresSet,
            queue<pair<int, int> >& kWindowMaxScoresQue
    ) {
        int lastCrrScore = 0;
        for (int i = k; i < vec.size(); i++) {
            pair<int, int> maxPrecedingScore = *(kWindowMaxScoresSet.begin());

            int maxCrrScore = (-maxPrecedingScore.first) + vec[i];
            lastCrrScore = maxCrrScore;

            kWindowMaxScoresSet.insert({-maxCrrScore, i});
            kWindowMaxScoresQue.push({-maxCrrScore, i});

            pair<int, int> firstQueScore = kWindowMaxScoresQue.front();
            kWindowMaxScoresSet.erase(firstQueScore);
            kWindowMaxScoresQue.pop();
        }

        return lastCrrScore;
    }

    list<pair<int, int> > convertToList(set<pair<int, int> >& mSet) {
        list<pair<int, int> > mList;
        for (auto& p: mSet) {
            mList.push_back(p);
        }
        return mList;
    }

    // convert que to list
    list<pair<int, int> > convertToList(queue<pair<int, int> >& mQue) {
        list<pair<int, int> > mList;

        while (!mQue.empty()) {
            mList.push_back(mQue.front());
            mQue.pop();
        }

        return mList;
    }

    bool customAssert(set<pair<int, int>>& mSet1, set<pair<int, int>>& mSet2) {
        if (mSet1.size() != mSet2.size()) {
            return false;
        }

        list<pair<int, int> > mList1 = convertToList(mSet1);
        list<pair<int, int> > mList2 = convertToList(mSet2);

        return mList1.size() == mList2.size();
    }

    bool customAssert(queue<pair<int, int> >& mQue1, queue<pair<int, int> >& mQue2) {
        if (mQue1.size() != mQue2.size()) {
            return false;
        }

        list<pair<int, int> > mList1 = convertToList(mQue1);
        list<pair<int, int> > mList2 = convertToList(mQue2);

        return mList1.size() == mList2.size();
    }

public:
    friend class SolutionTest;

    int maxResult(vector<int>& nums, int k) {
        pair<set<pair<int, int> >, queue<pair<int, int> > > firstKWindowRes = createKWindowMaxScoresSet(nums, k);
        int maxEndScore = findMaxEndScore(nums, k, firstKWindowRes.first, firstKWindowRes.second);
        return maxEndScore;
    }
};

class SolutionTest {
public:
    void testCreateKWindowMaxScoresSet() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        pair<set<pair<int, int> >, queue<pair<int, int> > > resComputed;
        set<pair<int, int> > kWindowMaxScoresSetOutExpected;
        set<pair<int, int> > kWindowMaxScoresSetOutComputed;
        queue<pair<int, int> > kWindowMaxScoresQueOutExpected;
        queue<pair<int, int> > kWindowMaxScoresQueOutComputed;

        vecIn = {1, 2, 3, 4, 5};

        kIn = 2;
        kWindowMaxScoresSetOutExpected = {
                {-3, 1},
                {-1, 0}
        };
        kWindowMaxScoresQueOutExpected.push({-3, 1});
        kWindowMaxScoresQueOutExpected.push({-1, 0});
        resComputed = soln.createKWindowMaxScoresSet(vecIn, kIn);
        kWindowMaxScoresSetOutComputed = resComputed.first;
        kWindowMaxScoresQueOutComputed = resComputed.second;
//        soln.showSet(kWindowMaxScoresSetOutComputed, "kWindowMaxScoresSetOutComputed");
//        soln.showSet(kWindowMaxScoresSetOutExpected, "kWindowMaxScoresSetOutExpected");
//        assert(kWindowMaxScoresSetOutExpected == kWindowMaxScoresSetOutComputed);
        soln.customAssert(kWindowMaxScoresSetOutExpected, kWindowMaxScoresSetOutComputed);
//        assert(kWindowMaxScoresQueOutExpected == kWindowMaxScoresQueOutComputed);
        soln.customAssert(kWindowMaxScoresQueOutExpected, kWindowMaxScoresQueOutComputed);
    }

    void testMaxResult() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        int maxResultOutExpected, maxResultOutComputed;

        vecIn = {1, 2, 3, 4, 5};

        kIn = 2;
        maxResultOutExpected = 15;
        maxResultOutComputed = soln.maxResult(vecIn, kIn);
        assert(maxResultOutExpected == maxResultOutComputed);

        vecIn = {1, -1, -2, 4, -7, 3};

        kIn = 2;
        maxResultOutExpected = 7;
        maxResultOutComputed = soln.maxResult(vecIn, kIn);
        assert(maxResultOutExpected == maxResultOutComputed);

        vecIn = {10, -5, -2, 4, 0, 3};

        kIn = 3;
        maxResultOutExpected = 17;
        maxResultOutComputed = soln.maxResult(vecIn, kIn);
        assert(maxResultOutExpected == maxResultOutComputed);

        vecIn = {1, -5, -20, 4, -1, 3, -6, -3};

        kIn = 2;
        maxResultOutExpected = 0;
        maxResultOutComputed = soln.maxResult(vecIn, kIn);
        assert(maxResultOutExpected == maxResultOutComputed);

        vecIn = {122, -2920, 1798, 2421, -7678, -9915, 4320, -2000, -9548, 597, 8936, -9358, -6455, -7726, 2073, -6663,
                 1692, -6049, 7086, 6556, -3851, 2229, 4559, 5206, -7787, -9155, -3245, 9256, 3611, -824, 4315, 7473,
                 3114, 5157, 7587, 1557, 4669, 7989, -218, 3401, -3125, -2048, 5370, 1400, -5237, -7032, -8641, 4352,
                 1629, 2465, -8563, -9017, -1026, -4173, 5364, -4536, -5932, -72, 9829, -1258, -2851, 6419, -2574,
                 -7016, 530, -1683, -6110, -1125, 1840, 1016, -1132, 1182, 4656, -7152, 5582, -8187, 1886, 3212, 4233,
                 4357, -9575, 6296, -8957, 3862, -5852, -5324, 8833, 8524, 7539, -2600, 9462, -4339, 8798, -3992, -8367,
                 2108, 7453, -417, 3774, -9929, -7923, -4271, -2013, 2064, 6298, -8484, 1326, -5976, 3084, -2359, 8769,
                 4773, 8942, 6170, 5976, 2811, 5729, -6190, -8586, 1679, 5360, -288, -8812, 6095, -1925, -9241, -9614,
                 -5734, -7241, 6009, -4365, 6289, 3118, -3706, -4178, -276, 8478, 2308, 530, 7092, -3753, 8659, 9214,
                 -3315, 490, -5174, 5388, 5175, -9594, 3510, 3090, 8307, 2285, -141, -6180, -8067, 7132, -6010, -5869,
                 -7063, -8040, -6359, -1765, -7626, 310, 519, 180, -1969, -8832, 4021, -6416, 6907, 3997, -6163, 8854,
                 1643, 1948, -7314, 7365, 2801, -5467, 8881, 8946, -5075, -9173, 97, -8494, -1272, 8937, -9555, 4846,
                 -8103, 9108, -4791, -1482, 5676, -9773, -8090, 5213, -1120, -5134, 3495, -8866, 2134, 8063, -980,
                 -6785, 8527, -2256, 1667, -4011, -1112, 4385, 823, -5881, 5120, 9221, 5020, 8779, -6911, -6773, -6492,
                 -9569, -5344, 7569, 2978, 764, -4126, -5557, 2125, -1516, 6111, 5163, -6171, -2255, -6969, 1314, -9761,
                 1809, 4941, 818, -7955, -9997, 4786, -1799, 325, -5192, 7103, 8185, 7932, -2441, 3971, -980, 8356,
                 8670, 1083, -3384, -5976, -7204, -5421, 8214, 3339, 1166, 7744, 2934, 6059, -4570, -4115, -8947, -1087,
                 -6579, 2345, 5423, 9177, -6461, 8056, 6595, 2085, 4103, 4020, 8250, 2887, 8409, 1104, -7105, 4617,
                 -9401, -4199, 6050, 5978, -4432, 124, -8064, 3653, -3889, -2973, -4933, -8635, 3564, 2494, 5363, 1704,
                 5883, 4193, 8338, 1381, -3674, 7456, -2562, 8542, 9236, -1359, 7870, 9463, 9824, 7976, -1854, 6992,
                 4174, 9718, -9535, 8085, -7278, 7543, 5108, -3992, -4699, -9787, -5361, 312, 3437, -9579, -8575, 2648,
                 4702, 1275, 6739, 3302, -6126, -3880, -6179, 2880, 1361, 7618, -7936, -5509, 4246, 610, -7184, -2450,
                 3701, -7819, 4670, -4258, -6430, 7796, 7660, -4199, 3461, -6917, -2327, 2020, -4675, 9407, -7613, 3078,
                 -6082, 1335, 6908, 4676, -6180, 2706, -6643, -714, -7122, -2017, -3377, 2413, 4275, 6847, -9655, -1448,
                 -9924, -7361, -2400, -6232, 3949, 7406, 9737, 3761, -8771, 6060, 1845, 5717, -446, -5682, 6041, 461,
                 -2502, 4019, 9256, 3326, 9201, 8623, -2373, 1057, 3575, 6198, 4142, -9247, -754, 1245, 3762};

        kIn = 743;
        maxResultOutExpected = 0;
        maxResultOutComputed = soln.maxResult(vecIn, kIn);
//        cout << maxResultOutComputed << endl;
        assert(maxResultOutExpected == maxResultOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateKWindowMaxScoresSet();
    solnTest.testMaxResult();

    return 0;
}
