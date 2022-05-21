// LeetCode-328: https://leetcode.com/problems/odd-even-linked-list/

#include <cstdio>
#include <iostream>
#include <utility>
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

    list<int> convertToStdList(ListNode* head) {
        list<int> stdList;

        for (ListNode* list = head; list != nullptr; list = list->next) {
            stdList.push_back(list->val);
        }

        return stdList;
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

    void terminateList(pair<ListNode*, ListNode*> headTail) {
        if (headTail.second != nullptr) {
            headTail.second->next = nullptr;
        }
    }

    void joinList(
            pair<ListNode*, ListNode*> evenHeadTail,
            pair<ListNode*, ListNode*> oddHeadTail
    ) {
        if (evenHeadTail.second != nullptr) {
            evenHeadTail.second->next = oddHeadTail.first;
        }
    }

public:
    friend class SolutionTest;

    ListNode* oddEvenList(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr) || (head->next->next == nullptr)) {
            return head;
        }

        pair<ListNode*, ListNode*> evenHeadTail = {nullptr, nullptr};
        pair<ListNode*, ListNode*> oddHeadTail = {nullptr, nullptr};

        int i = 0;
        for (ListNode* list = head; list != nullptr; i++, list = list->next) {
            if ((i % 2) == 0) {
                evenHeadTail = addNode(evenHeadTail, list);
            } else {
                oddHeadTail = addNode(oddHeadTail, list);
            }
        }

        terminateList(evenHeadTail);
        terminateList(oddHeadTail);

        joinList(evenHeadTail, oddHeadTail);

        return head;
    }
};

class SolutionTest {
public:
    void testOddEvenList() {
        Solution soln = Solution();
        list<int> stdListIn;
        ListNode* listIn;
        list<int> stdListOutExpected;
        ListNode* listOutExpected;
        ListNode* listOutComputed;
        list<int> stdListOutComputed;

        stdListIn = {};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {4};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 5};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {4, 5};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 5, 8};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {4, 8, 5};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 5, 8, 11};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {4, 8, 5, 11};
        assert(stdListOutExpected == stdListOutComputed);

        stdListIn = {4, 5, 8, 11, 19};
        listIn = soln.convertToLinkedList(stdListIn);
        listOutComputed = soln.oddEvenList(listIn);
        stdListOutComputed = soln.convertToStdList(listOutComputed);
        stdListOutExpected = {4, 8, 19, 5, 11};
        assert(stdListOutExpected == stdListOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testOddEvenList();

    return 0;
}
