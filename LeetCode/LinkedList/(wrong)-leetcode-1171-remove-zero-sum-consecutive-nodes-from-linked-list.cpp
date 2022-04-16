// LeetCode-1171: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/
// wrong solution (this approach wont work)
// e.g. test case [1 3 2 -3 -2 5 5 -5 1]
// expected output, [1, 5, 1]; computed output [1, 5, 5, -5, 1]

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <list>
#include <cassert>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    bool debug = false;

    ListNode *createNode(int val) {
        ListNode *newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    ListNode *createLinkedList(list<int>& mList) {
        if (mList.empty()) {
            return nullptr;
        }

        ListNode *head = nullptr;
        ListNode *list = nullptr;
        for (auto it = mList.begin(); it != mList.end(); it++) {
            ListNode *newNode = createNode(*it);
            if (head == nullptr) {
                head = newNode;
            } else {
                list->next = newNode;
            }

            list = newNode;
        }

        return head;
    }

    list<int> createStdList(ListNode *head) {
        list<int> mList;
        for (ListNode *list = head; list != nullptr; list = list->next) {
            mList.push_back(list->val);
        }

        return mList;
    }

    void showStdList(list<int>& mList) {
        printf("list is:-\n");
        for (list<int>::iterator it = mList.begin(); it != mList.end(); it++) {
            printf("%d ", *it);
        }
        cout << endl;
    }

public:
    friend class SolutionTest;

    ListNode *removeZeroSumSublists(ListNode *head) {
        unordered_map<int, pair<ListNode *, ListNode *> > prefSumNodeMap;
        prefSumNodeMap[0] = {nullptr, nullptr};

        int sum = 0;
        ListNode *newHead = head;
        ListNode *prev = nullptr;
        for (ListNode *list = head; list != nullptr; list = list->next) {
            sum += list->val;
            if (debug) {
                printf("\n----\n");
                printf("at node=%d, sum=%d\n", list->val, sum);
            }

            if (prefSumNodeMap.find(sum) != prefSumNodeMap.end()) {
                // found a zero-sum sequence

                ListNode *node = prefSumNodeMap[sum].first;

                if (node == nullptr) {
                    if (debug) {
                        printf("at node=%d, found sum=%d repeated; prevNode=null\n", list->val, sum);
                    }
                    newHead = list->next;
                } else {
                    if (debug) {
                        printf("at node=%d, found sum=%d repeated; prevNode=%d\n", list->val, sum, node->val);
                    }
                    node->next = list->next;
                }

//                ListNode *parent = prefSumNodeMap[sum].second;
//                if (parent != nullptr) {
//                    parent->next = list->next;
//                } else {
//                    newHead = list->next;
//                    if (debug) {
//                        printf("updated newHead=%s at node=%d; sum=%d\n", ((newHead == nullptr) ? "null" : to_string(newHead->val).c_str()), list->val, sum);
//                    }
//                }

//                prefSumNodeMap.erase(sum);
            } else {
                prefSumNodeMap[sum] = {list, prev};
            }

            prev = list;
        }

        if (sum == 0) {
            return nullptr;
        }
        return newHead;
    }
};

class SolutionTest {
public:
    void testCreateStdList() {
        Solution soln = Solution();
        ListNode *headIn;
        list<int> listOutExpected;
        list<int> listOutComputed;

        headIn = nullptr;
        listOutExpected = {};
        listOutComputed = soln.createStdList(headIn);
        assert(listOutExpected == listOutComputed);

        headIn = soln.createNode(5);
        listOutExpected = {5};
        listOutComputed = soln.createStdList(headIn);
        assert(listOutExpected == listOutComputed);

        headIn = soln.createNode(6);
        headIn->next = soln.createNode(11);
        listOutExpected = {6, 11};
        listOutComputed = soln.createStdList(headIn);
        assert(listOutExpected == listOutComputed);

        headIn = soln.createNode(7);
        headIn->next = soln.createNode(19);
        headIn->next->next = soln.createNode(-4);
        listOutExpected = {7, 19, -4};
        listOutComputed = soln.createStdList(headIn);
        assert(listOutExpected == listOutComputed);
    }

    void testCreateLinkedList() {
        Solution soln = Solution();
        list<int> listIn;
        ListNode *headOutComputed;
        list<int> listOutComputed;

        listIn = {};
        ListNode *headOutExpected = nullptr;
        headOutComputed = soln.createLinkedList(listIn);
        assert(headOutExpected == headOutComputed);
        listOutComputed = soln.createStdList(headOutComputed);
        assert(listIn == listOutComputed);

        listIn = {6};
        headOutComputed = soln.createLinkedList(listIn);
        listOutComputed = soln.createStdList(headOutComputed);
        assert(listIn == listOutComputed);

        listIn = {19, 9};
        headOutComputed = soln.createLinkedList(listIn);
        listOutComputed = soln.createStdList(headOutComputed);
        assert(listIn == listOutComputed);

        listIn = {8, 1, 3};
        headOutComputed = soln.createLinkedList(listIn);
        listOutComputed = soln.createStdList(headOutComputed);
        assert(listIn == listOutComputed);
    }

    void testRemoveZeroSumSublists() {
        Solution soln = Solution();
        list<int> listIn;
        ListNode *headIn;
        ListNode *headOutComputed;
        list<int> listOutComputed;
        list<int> listOutExpected;

        listIn = {};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {};
        assert(listOutExpected == listOutComputed);

        listIn = {8};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {8};
        assert(listOutExpected == listOutComputed);

        listIn = {8, 1};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {8, 1};
        assert(listOutExpected == listOutComputed);

//        soln.debug = true;
        listIn = {8, 1, 0, -1};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {8};
//        soln.showStdList(listOutComputed);
        assert(listOutExpected == listOutComputed);
//        soln.debug = false;

        listIn = {1, 2, -3, 3, 1};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {3, 1};
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, -3, 4};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {1, 2, 4};
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, -3, -2};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {1};
        assert(listOutExpected == listOutComputed);

        listIn = {1, -2, 3, 0, 1, -1, 0, 0, -3, 0, 1, -1, 2, -1};
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {};
        assert(listOutExpected == listOutComputed);

        soln.debug = true;
        listIn = {1, 3, 2, -3, -2, 5, 5, -5, 1};
        soln.showStdList(listIn);
        headIn = soln.createLinkedList(listIn);
        headOutComputed = soln.removeZeroSumSublists(headIn);
        listOutComputed = soln.createStdList(headOutComputed);
        listOutExpected = {1, 5, 1};
        soln.showStdList(listOutComputed);
        assert(listOutExpected == listOutComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateStdList();
    solnTest.testCreateLinkedList();
    solnTest.testRemoveZeroSumSublists();

    return 0;
}
