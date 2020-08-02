// https://leetcode.com/problems/kth-largest-element-in-a-stream/
// https://www.geeksforgeeks.org/kth-largest-element-in-a-stream/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
   private:
    priority_queue<int, vector<int>, greater<int> > que;
    int k;

    void pushEles(int k, vector<int>& nums) {
        int i;

        // push first 'k' elements in queue
        for (i = 0; i < min(k, (int)nums.size()); i++) {
            que.push(nums[i]);
        }

        // showPQue("after first k elements insertion");

        // for remaining elements, use 'add' method
        for (; i < nums.size(); i++) {
            add(nums[i]);
        }

        // showPQue("after all nums insertion");
    }

    void showPQue(string where) {
        printf("\n%s, pQue is:-\n", where.c_str());
        priority_queue<int, vector<int>, greater<int> > queCopy = this->que;
        while (!queCopy.empty()) {
            printf("%d ", queCopy.top());
            queCopy.pop();
        }
        cout << endl;
    }

   public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        pushEles(k, nums);
    }

    int add(int val) {
        // printf("\n--------\n");
        // printf("before adding %d:-\n", val);
        // printf("k = %d\n", this->k);
        // showPQue();

        if (que.size() < this->k) {
            // if all 'k' elements haven't been added to heap yet
            // (this is the kth element being added)
            que.push(val);
        } else if (val > que.top()) {
            // remove the kth largest element
            que.pop();
            // and add the new element (new kth largest will be automatically recomputed)
            que.push(val);
        }

        // printf("\nafter adding %d:-\n", val);
        // showPQue();

        return que.top();
    }

    friend class KthLargestTest;
};

class KthLargestTest {
   public:
    void testAdd() {
        vector<int> nums;

        nums = {};
        KthLargest kl = KthLargest(1, nums);
        assert(kl.add(0) == 0);
        // 0
        assert(kl.add(1) == 1);
        // 1
        assert(kl.add(-1) == 1);
        // 1
        assert(kl.add(1) == 1);
        // 1
        assert(kl.add(5) == 5);
        // 5

        nums = {1, 13, 12, 1};
        kl = KthLargest(4, nums);
        // 1 1 12 13
        assert(kl.add(0) == 1);
        // 1 1 12 13
        assert(kl.add(1) == 1);
        // 1 1 12 13
        assert(kl.add(12) == 1);
        // 1 12 12 13
        assert(kl.add(10) == 10);
        // 10 12 12 13
        assert(kl.add(15) == 12);
        // 12 12 13 15

        nums = {1, 13, 12, 1};
        kl = KthLargest(2, nums);
        // 12 13
        // kl.showPQue("after constructor");
        assert(kl.add(0) == 12);
        // kl.showPQue("after add(0)");

        // 12 13
        assert(kl.add(14) == 13);
        // 13 14
        assert(kl.add(12) == 13);
        // 13 14
        assert(kl.add(13) == 13);
        // 13 14
        assert(kl.add(14) == 14);
        // 14 14
    }
};

int main() {
    KthLargestTest tester = KthLargestTest();
    tester.testAdd();

    return 0;
}
