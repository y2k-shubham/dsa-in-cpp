// LeetCode-92: https://leetcode.com/problems/reverse-linked-list-ii/

#include <utility>
#include <cassert>
#include <list>
#include <iostream>
#include <cstdio>

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

    ListNode* advanceByNNodes(ListNode* head, int n) {
        if (n <= 1) {
            return nullptr;
        }

        ListNode* list = head;
        for (int i = 1; (list != nullptr) && (i < n - 1); i++) {
            list = list->next;
        }

        return list;
    }

    ListNode* revList(ListNode* head) {
        ListNode* prevNode = nullptr;
        ListNode* crrNode = head;

        while (crrNode != nullptr) {
            ListNode* nextNode = crrNode->next;
            crrNode->next = prevNode;

            prevNode = crrNode;
            crrNode = nextNode;
        }

        return prevNode;
    }

public:
    friend class SolutionTest;

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if ((head == nullptr) || (head->next == nullptr) || (left == right)) {
            return head;
        }

        ListNode* tailLeft = advanceByNNodes(head, left);
//        printf("1\n");

        ListNode* headMid = (tailLeft == nullptr) ? head : tailLeft->next;
        ListNode* tailMid = advanceByNNodes(headMid, right - left + 2);
//        printf("2\n");
////        printf("tailLeft=%d, headMid=%d\n", tailLeft->val, headMid->val);

        if (tailLeft == nullptr) {
            //        printf("tailLeft is null\n");
        }
        if (headMid == nullptr) {
            //        printf("headMid is null\n");
        }
        if (tailMid == nullptr) {
            //        printf("tailMid is null\n");
        }
        ListNode* headRight = tailMid->next;
        tailMid->next = nullptr;
//        printf("3\n");

        ListNode* revTailMid = headMid;
        ListNode* revHeadMid = revList(headMid); // actually revHeadMid is same as tailMid
//        printf("4\n");

        if (tailLeft != nullptr) {
            tailLeft->next = revHeadMid;
        }
        revTailMid->next = headRight;
//        printf("5\n");

        return (left == 1) ? revHeadMid : head;
    }
};

class SolutionTest {
public:
    void testAdvanceByNNodes() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* lListIn;
        int nIn;
        ListNode* lListOutComputed;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;

        stdListIn = {};
        nIn = 5;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {3, 4, 1};

        nIn = 0;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        nIn = 1;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        nIn = 2;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {3, 4, 1};
        assert(stdListOutExpected == stdListOutComputed);

        nIn = 3;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {4, 1};
        assert(stdListOutExpected == stdListOutComputed);

        nIn = 4;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {1};
        assert(stdListOutExpected == stdListOutComputed);

        nIn = 5;
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.advanceByNNodes(lListIn, nIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);
    }

    void testRevList() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* lListIn;
        ListNode* lListOutComputed;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4};
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {4};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 5};
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {5, 4};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {7, 8, 6};
        lListIn = soln.convertToLinkedList(stdListIn);
        lListOutComputed = soln.revList(lListIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {6, 8, 7};
        assert(stdListOutExpected == stdListOutComputed);
    }

    void testReverseBetween() {
        Solution soln = Solution();
        list<int> stdListIn;
        int leftIn, rightIn;
        ListNode* lListIn;
        ListNode* lListOutComputed;
        list<int> stdListOutExpected;
        list<int> stdListOutComputed;

        stdListIn = {};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 1;
        rightIn = 1;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 1;
        rightIn = 1;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {5};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 6, 3, 7, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 3;
        rightIn = 3;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {5, 6, 3, 7, 2};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 6, 3, 7, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 3;
        rightIn = 4;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {5, 6, 7, 3, 2};
//        soln.showLinkedList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 6, 3, 7, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 3;
        rightIn = 5;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {5, 6, 2, 7, 3};
//        soln.showLinkedList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 6, 3, 7, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 1;
        rightIn = 2;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {6, 5, 3, 7, 2};
//        soln.showLinkedList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {5, 6, 3, 7, 2};
        lListIn = soln.convertToLinkedList(stdListIn);
        leftIn = 1;
        rightIn = 5;
        lListOutComputed = soln.reverseBetween(lListIn, leftIn, rightIn);
        stdListOutComputed = soln.convertToStdList(lListOutComputed);
        stdListOutExpected = {2, 7, 3, 6, 5};
//        soln.showLinkedList(lListOutComputed);
        assert(stdListOutExpected == stdListOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testAdvanceByNNodes();
    solnTest.testRevList();
    solnTest.testReverseBetween();

    return 0;
}
