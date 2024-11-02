// LeetCode-1710: https://leetcode.com/problems/maximum-units-on-a-truck/

#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

class Pojo {
public:
    int numUnitsPerBox;
    int numBoxes;

    Pojo(int numUnitsPerBox, int numBoxes) {
        this->numUnitsPerBox = numUnitsPerBox;
        this->numBoxes = numBoxes;
    }
};

class Solution {
private:
    vector<Pojo> convertToPojoVec(vector<vector<int> >& boxTypesVec) {
        vector<Pojo> pojoVec;

        for (int i = 0; i < boxTypesVec.size(); i++) {
            Pojo pojo = Pojo(boxTypesVec[i][1], boxTypesVec[i][0]);
            pojoVec.push_back(pojo);
        }

        return pojoVec;
    }

    vector<Pojo> sortPojoVec(vector<Pojo>& pojoVec) {
        sort(pojoVec.begin(), pojoVec.end(), [](const Pojo& a, const Pojo& b) {
            if (a.numUnitsPerBox == b.numUnitsPerBox) {
                return a.numBoxes <= b.numBoxes;
            }

            return a.numUnitsPerBox > b.numUnitsPerBox;
        });

        return pojoVec;
    }

    int calcMaxUnits(vector<Pojo>& sortedPojoVec, int boxCapacity) {
        int maxUnits = 0;
        for (int i = 0; i < sortedPojoVec.size(); i++) {
            int numBoxes = min(boxCapacity, sortedPojoVec[i].numBoxes);
            int numUnits = numBoxes * sortedPojoVec[i].numUnitsPerBox;

            maxUnits += numUnits;
            boxCapacity -= numBoxes;

            if (boxCapacity == 0) {
                break;
            }
        }

        return maxUnits;
    }

public:
    friend class SolutionTest;

    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        vector<Pojo> pojoVec = convertToPojoVec(boxTypes);
        vector<Pojo> sortedPojoVec = sortPojoVec(pojoVec);

        return calcMaxUnits(sortedPojoVec, truckSize);
    }
};

class SolutionTest {
private:
    vector<vector<int> > convertToVecVec(vector<Pojo>& pojoVec) {
        vector<vector<int> > vecVec;

        for (int i = 0; i < pojoVec.size(); i++) {
            vector<int> vec = {pojoVec[i].numBoxes, pojoVec[i].numUnitsPerBox};
            vecVec.push_back(vec);
        }

        return vecVec;
    }

    vector<Pojo> negateUnitsPerBox(vector<Pojo>& pojoVec) {
        for (int i = 0; i < pojoVec.size(); i++) {
            pojoVec[i].numUnitsPerBox *= -1;
        }

        return pojoVec;
    }

    void showPojoVec(vector<Pojo>& pojoVec, const char* name) {
        printf("\n%s pojoVec is:-\n", name);
        for (int i = 0; i < pojoVec.size(); i++) {
            printf("(numUnitsPerBox=%d, numBoxes=%d)\n", pojoVec[i].numUnitsPerBox, pojoVec[i].numBoxes);
        }
    }

    void showVecVec(vector<vector<int> >& vecVec, const char* name) {
        printf("\n%s vecVec is:-\n", name);
        for (int i = 0; i < vecVec.size(); i++) {
            printf("(numUnitsPerBox=%d, numBoxes=%d)\n", vecVec[i][1], vecVec[i][0]);
        }
    }

public:
    void testSortPojoVec() {
        Solution soln = Solution();
        vector<vector<int> > vecVecIn, vecVecOutExpected, vecVecOutComputed;
        vector<Pojo> pojoVecIn, sortedPojoVecOutComputed;

        vecVecIn = {
                {1, 3},
                {2, 2},
                {3, 1}
        };
        pojoVecIn = soln.convertToPojoVec(vecVecIn);
        vecVecOutExpected = {
                {1, 3},
                {2, 2},
                {3, 1}
        };
        sortedPojoVecOutComputed = pojoVecIn;
        soln.sortPojoVec(sortedPojoVecOutComputed);
        vecVecOutComputed = convertToVecVec(sortedPojoVecOutComputed);
        assert(vecVecOutExpected == vecVecOutComputed);

        vecVecIn = {
                {2, 2},
                {3, 1},
                {1, 3}
        };
        pojoVecIn = soln.convertToPojoVec(vecVecIn);
        vecVecOutExpected = {
                {1, 3},
                {2, 2},
                {3, 1}
        };
        sortedPojoVecOutComputed = pojoVecIn;
        soln.sortPojoVec(sortedPojoVecOutComputed);
        vecVecOutComputed = convertToVecVec(sortedPojoVecOutComputed);
        assert(vecVecOutExpected == vecVecOutComputed);

        vecVecIn = {
                {5, 10},
                {2, 5},
                {4, 7},
                {3, 9}
        };
        pojoVecIn = soln.convertToPojoVec(vecVecIn);
//        showPojoVec(pojoVecIn, "pojoVecIn");
        vecVecOutExpected = {
                {5, 10},
                {3, 9},
                {4, 7},
                {2, 5}
        };
        sortedPojoVecOutComputed = pojoVecIn;
        soln.sortPojoVec(sortedPojoVecOutComputed);
//        showPojoVec(sortedPojoVecOutComputed, "sortedPojoVecOutComputed");
        vecVecOutComputed = convertToVecVec(sortedPojoVecOutComputed);
//        showVecVec(vecVecOutComputed, "vecVecOutComputed");
        assert(vecVecOutExpected == vecVecOutComputed);

        printf("[testSortPojoVec] All test-cases passed!\n");
    }

    void testMaximumUnits() {
        Solution soln = Solution();
        vector<vector<int> > vecVecIn;
        int truckSize, maxUnitsOutExpected, maxUnitsOutComputed;

        vecVecIn = {
                {1, 3},
                {2, 2},
                {3, 1}
        };
        truckSize = 4;
        maxUnitsOutExpected = 8;
        maxUnitsOutComputed = soln.maximumUnits(vecVecIn, truckSize);
        assert(maxUnitsOutExpected == maxUnitsOutComputed);

        vecVecIn = {
                {5, 10},
                {2, 5},
                {4, 7},
                {3, 9}
        };
        truckSize = 10;
        maxUnitsOutExpected = 91;
        maxUnitsOutComputed = soln.maximumUnits(vecVecIn, truckSize);
        assert(maxUnitsOutExpected == maxUnitsOutComputed);

        printf("[testMaximumUnits] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSortPojoVec();
    solnTest.testMaximumUnits();

    return 0;
}
