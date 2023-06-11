// incomplete (wrong answer)
// LeetCode-1146: https://leetcode.com/problems/snapshot-array/

/**
 * failing test
 * Input
["SnapshotArray","set","snap","snap","snap","get","snap","snap","get"]
[[1],[0,15],[],[],[],[0,2],[],[],[0,0]]
Use Testcase
Output
[null,null,0,1,2,0,3,4,15]
Expected
[null,null,0,1,2,15,3,4,15]
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

class SnapshotArray {
private:
    vector<vector<int> > snapArr;
    int numSnaps;

public:
    SnapshotArray(int length) {
        snapArr.resize(length);
        numSnaps = 0;
    }

    void showSnapArr() {
        printf("SnapArr is:-\n");

        printf("Ind:\t");
        for (int i = 0; i < snapArr.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        for (int i = 0; i <= numSnaps; i++) {
            printf("Snap-%d:\t", (i + 1));
            for (int j = 0; j < snapArr.size(); j++) {
                if (snapArr[j].size() > i) {
                    printf("%d\t", snapArr[j][i]);
                } else {
                    printf("-\t");
                }
            }
            printf("\n");
        }

        printf("-------------\n");
    }

    void set(int index, int val) {
        if (snapArr[index].size() > numSnaps) {
            snapArr[index][numSnaps] = val;
        } else {
            while (snapArr[index].size() < numSnaps) {
                snapArr[index].push_back(0);
            }
            snapArr[index].push_back(val);
        }
    }

    int snap() {
        return numSnaps++;
    }

    int get(int index, int snap_id) {
        if (index >= snapArr.size()) {
//            printf("int_min here1\n");
            return INT_MIN;
        } else if (snap_id >= numSnaps) {
//            printf("int_min here2\n");
            return INT_MIN;
        } else if (snapArr[index].size() <= snap_id) {
//            printf("int_min here3\n");
//            printf("snapArr[index=%d].size() = %lu\t, snap_id=%d\n", index, snapArr[index].size(), snap_id);
            return 0;
        } else {
//            printf("normal here4\n");
            return snapArr[index][snap_id];
        }
    }
};

class SnapshotArrayTest {
public:
    void test1() {
        SnapshotArray *obj = new SnapshotArray(3);
//        obj->showSnapArr();

//        printf("here 1\n");
        obj->set(0, 5);
//        obj->showSnapArr();

//        printf("here 2\n");
        assert(obj->snap() == 0);
//        obj->showSnapArr();

//        printf("here 3\n");
        obj->set(0, 6);
//        obj->showSnapArr();

//        printf("here 4\n");
        assert(obj->get(0, 0) == 5);
//        obj->showSnapArr();
    }

    void test2() {
        SnapshotArray *obj = new SnapshotArray(3);

        assert(obj->get(0, 0) == INT_MIN);
        obj->set(1, 101);
        assert(obj->get(0, 2) == INT_MIN);
        assert(obj->get(19, 0) == INT_MIN);
        obj->set(2, 102);
        assert(obj->get(0, 1) == INT_MIN);
        assert(obj->get(0, 2) == INT_MIN);
        assert(obj->get(0, 0) == INT_MIN);
        assert(obj->get(1, 0) == INT_MIN);
        assert(obj->get(2, 0) == INT_MIN);

        assert(obj->snap() == 0);

        assert(obj->get(0, 0) == 0);
        assert(obj->get(0, 1) == INT_MIN);
        assert(obj->get(0, 2) == INT_MIN);
        assert(obj->get(1, 0) == 101);
        assert(obj->get(2, 0) == 102);
        assert(obj->get(0, 2) == INT_MIN);
        assert(obj->get(19, 0) == INT_MIN);
    }

    void test3() {
        SnapshotArray *obj = new SnapshotArray(4);

        assert(obj->snap() == 0);
        assert(obj->snap() == 1);
        assert(obj->get(3, 1) == 0);
        obj->set(2, 4);
        assert(obj->snap() == 2);
        obj->set(1, 4);
    }
};

int main() {
    SnapshotArrayTest *test = new SnapshotArrayTest();
    test->test1();
    test->test2();
    test->test3();

    return 0;
}

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
