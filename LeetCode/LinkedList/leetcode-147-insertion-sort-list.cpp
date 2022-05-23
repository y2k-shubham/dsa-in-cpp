// LeetCode-147: https://leetcode.com/problems/insertion-sort-list/

#include <cstdio>
#include <iostream>
#include <list>
#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
private:
    bool debug = false;

    // testing helper methods - begin //
    ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;

        return newNode;
    }

    ListNode* convertToLinkedList(list<int>& stdList) {
        pair<ListNode*, ListNode*> headTail = {nullptr, nullptr};

        for (list<int>::iterator it = stdList.begin(); it != stdList.end(); it++) {
            headTail = addNode(headTail, *it);
        }

        return headTail.first;
    }

    pair<ListNode*, ListNode*> addNode(
            pair<ListNode*, ListNode*> headTail,
            ListNode* node
    ) {
        if (node == nullptr) {
            return headTail;
        }

        if (headTail.first == nullptr) {
            headTail.first = node;
        }

        if (headTail.second == nullptr) {
            headTail.second = node;
        } else {
            headTail.second->next = node;
            headTail.second = node;
        }

        return headTail;
    }

    pair<ListNode*, ListNode*> addNode(
            pair<ListNode*, ListNode*> headTail,
            int val
    ) {
        ListNode* node = createNode(val);
        return addNode(headTail, node);
    }

    list<int> convertToStdList(ListNode* head) {
        list<int> stdList;

        for (ListNode* list = head; list != nullptr; list = list->next) {
            stdList.push_back(list->val);
        }

        return stdList;
    }

    void showStdList(list<int>& stdList) {
        printf("list is:-\n");
        for (auto it = stdList.begin(); it != stdList.end(); it++) {
            printf("%d ", *it);
        }
        cout << endl;
    }

    void showLinkedList(ListNode* head) {
        printf("linked-list is:-\n");

        int i = 1;
        for (ListNode* list = head; list != nullptr; list = list->next) {
            if (i >= 100) {
                break;
            }

            printf("%d ", list->val);
            i++;
        }

        cout << endl;
    }

    // testing helper methods - end //

    ListNode* insertDescSorted(ListNode* head, ListNode* node) {
        if (head == nullptr) {
            if (node != nullptr) {
                // poorly implemented;
                // this side-effect should NOT be required ideally,
                // but over here without it we get seg-fault
                node->next = nullptr;
            }
            return node;
        }
        if (node == nullptr) {
            return head;
        }
        if (node->val >= head->val) {
            node->next = head;
            head = node;
            return head;
        }

        ListNode* list = head;
        ListNode* prev = nullptr;
        while (list != nullptr) {
            if (debug) {
                if (prev == nullptr) {
                    printf("prev=null ");
                } else {
                    printf("prev=%d ", prev->val);
                }
                printf("list = %d\n", list->val);
            }

            if (list->val <= node->val) {
                prev->next = node;
                node->next = list;
                break;
            }

            prev = list;
            list = list->next;
        }

        if (list == nullptr) {
            prev->next = node;
            node->next = nullptr;
        }

        return head;
    }

    ListNode* revList(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* list = head;
        while (list != nullptr) {
            if (debug) {
                if (prev == nullptr) {
                    printf("prev=null ");
                } else {
                    printf("prev=%d ", prev->val);
                }

                printf("list=%d\n", list->val);
            }

            ListNode* next = list->next;

            list->next = prev;

            prev = list;
            list = next;
        }

        head->next = nullptr;

        return prev;
    }

public:
    friend class SolutionTest;

    ListNode* insertionSortList(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return head;
        }

        ListNode* leftRevListDescHead = nullptr;
        ListNode* rightListHead = head;
        while (rightListHead != nullptr) {
            if (debug) {
                printf("rightHead=%d\n", rightListHead->val);
            }
            ListNode* rightListNext = rightListHead->next;

            leftRevListDescHead = insertDescSorted(leftRevListDescHead, rightListHead);

            rightListHead = rightListNext;
        }

        if (debug) {
            printf("going to reverse list\n");
            showLinkedList(leftRevListDescHead);
            list<int> stdList = convertToStdList(leftRevListDescHead);
            showStdList(stdList);
        }

        ListNode* sortedListHead = revList(leftRevListDescHead);
        return sortedListHead;
    }
};

class SolutionTest {
public:
    void testInsertDescSorted() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* lListIn;
        ListNode* nodeIn;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;
        ListNode* lListOutComputed;

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = nullptr;
        stdListOutExpected = {};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {6};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = nullptr;
        stdListOutExpected = {6};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(4);
        stdListOutExpected = {4};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {6};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(4);
        stdListOutExpected = {6, 4};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(6);
        stdListOutExpected = {6, 5};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {6};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(6);
        stdListOutExpected = {6, 6};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {6};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(8);
        stdListOutExpected = {8, 6};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(1);
        stdListOutExpected = {5, 2, 1};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(3);
        stdListOutExpected = {5, 3, 2};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(7);
        stdListOutExpected = {7, 5, 2};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {7, 3, 1, -6};
        lListIn = soln.convertToLinkedList(stdListIn);
        nodeIn = soln.createNode(2);
        stdListOutExpected = {7, 3, 2, 1, -6};
        lListOutComputed = soln.insertDescSorted(lListIn, nodeIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);
    }

    void testRevList() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* lListIn;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;
        ListNode* lListOutComputed;

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {};
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {4};
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 6};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {6, 4};
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 7, 9};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {9, 7, 4};
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);
    }

    void testInsertionSortList() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* lListIn;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;
        ListNode* lListOutComputed;

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {};
        lListOutComputed = soln.insertionSortList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {5};
        lListOutComputed = soln.insertionSortList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

//        soln.debug = true;
        stdListIn = {5, 6};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {5, 6};
        lListOutComputed = soln.insertionSortList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
//        soln.showStdList(stdListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);
//        soln.debug = false;

        stdListIn = {6, 5};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {5, 6};
        lListOutComputed = soln.insertionSortList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {8, 1, 3, 7, 4, 2, 9};
        lListIn = soln.convertToLinkedList(stdListIn);
        stdListOutExpected = {1, 2, 3, 4, 7, 8, 9};
        lListOutComputed = soln.insertionSortList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testRevList();
    solnTest.testInsertDescSorted();
    solnTest.testInsertionSortList();

    return 0;
}
