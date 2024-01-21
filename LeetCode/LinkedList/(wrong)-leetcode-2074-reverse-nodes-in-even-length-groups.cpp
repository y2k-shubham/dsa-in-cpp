// LeetCode-2074: https://leetcode.com/problems/reverse-nodes-in-even-length-groups/
// wrong: that 3rd sample test case is not understandable

#include <cstdio>
#include <utility>
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
    pair<pair<ListNode*, ListNode*>, ListNode*> reverseFirstNNodes(ListNode* head, int n) {
        if ((n == 0) || (head == nullptr)) {
            return {{nullptr, nullptr}, head};
        }

        ListNode* orgHead = head;
        ListNode* prev = nullptr;
        ListNode* list = head;
        ListNode* next = nullptr;
        for (int i = 1; (list != nullptr) && (i <= n); i++) {
//            printf("at node %d\n", list->val);
            next = list->next;
            list->next = prev;
            prev = list;
            list = next;
        }

        orgHead->next = nullptr;
        return {{prev, orgHead}, next};
    }

    int findLen(ListNode* head) {
        int len = 0;
        while (head != nullptr) {
            len++;
            head = head->next;
        }
        return len;
    }

    ListNode* getNthNode(ListNode* head, int n) {
        int i = 1;
        while (i < n) {
            head = head->next;
            i++;

            if (head == nullptr) {
                break;
            }
        }

        return head;
    }

    void showList(ListNode* head) {
        printf("List is: ");
        for (ListNode* list = head; list != nullptr; list = list->next) {
            cout << list->val << " ";
        }
        cout << endl;
    }

public:
    friend class SolutionTest;

    ListNode* reverseEvenLengthGroups(ListNode* head) {
        int nextSeqLen = 2;
        int length = findLen(head);

        ListNode* list = head;
        int idx = 1;
        while (idx <= length) {
//            printf("--------idx=%d--------\n", idx);

            list = (idx == 1) ? head : getNthNode(list, nextSeqLen - 1);
            if ((list == nullptr) || (list->next == nullptr)) {
//                printf("nth=%dth node is null, breaking\n",  nextSeqLen - 2);
                break;
            }
//            printf("nth=%dth node = %d\n",  nextSeqLen - 2, list->val);

            pair <pair <ListNode*, ListNode*>, ListNode*> nextEvenLenSeqReversed = reverseFirstNNodes(list->next, nextSeqLen);
//            printf("nextEvenLenSeqReversed.first.first = %d\n", nextEvenLenSeqReversed.first.first->val);
//            showList(nextEvenLenSeqReversed.first.first);
//            printf("nextEvenLenSeqReversed.second = %d\n", nextEvenLenSeqReversed.second->val);
//            showList(nextEvenLenSeqReversed.second);

//            printf("linking %d->next=%d\n", list->val, nextEvenLenSeqReversed.first.first->val);
            list->next = nextEvenLenSeqReversed.first.first;
//            printf("linking %d->next=%d\n", nextEvenLenSeqReversed.first.second->val, nextEvenLenSeqReversed.second->val);
            nextEvenLenSeqReversed.first.second->next = nextEvenLenSeqReversed.second;
//            printf("setting list=%d\n", nextEvenLenSeqReversed.second->val);
            list = nextEvenLenSeqReversed.second;

            idx += (nextSeqLen * 2) - 1;
            nextSeqLen += 2;
        }

        return head;
    }
};

class SolutionTest {
private:
    static ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    static ListNode* convertToLinkedList(list<int>& mList) {
        if (mList.empty()) {
            return nullptr;
        }

        ListNode* head = nullptr;
        ListNode* list = nullptr;
        for (auto it = mList.begin(); it != mList.end(); it++) {
            ListNode* newNode = createNode(*it);
//            printf("created node %d\n", newNode->val);
            if (head == nullptr) {
                head = newNode;
                list = newNode;
            } else {
                list->next = newNode;
                list = newNode;
            }
        }

        return head;
    }

    list<int> convertToList(ListNode* head) {
        list<int> mList;
        while (head != nullptr) {
            mList.push_back(head->val);
            head = head->next;
        }

        return mList;
    }

public:
    void testReverseFirstNNodes() {
        Solution soln = Solution();
        list<int> listIn;
        ListNode* linkedListIn;
        pair<pair<ListNode*, ListNode*>, ListNode*> linkedListsOutComputed;
        list<int> list1OutComputed, list2OutComputed;
        list<int> list1OutExpected, list2OutExpected;
        int n;

        listIn = {};
        linkedListIn = convertToLinkedList(listIn);
        n = 0;
        linkedListsOutComputed = soln.reverseFirstNNodes(linkedListIn, n);
//        showList(linkedListsOutComputed.first.first);
//        showList(linkedListsOutComputed.first.second);
//        showList(linkedListsOutComputed.second);
        list1OutComputed = convertToList(linkedListsOutComputed.first.first);
        list2OutComputed = convertToList(linkedListsOutComputed.second);
        list1OutExpected = {};
        list2OutExpected = {};
        assert(list1OutExpected == list1OutComputed);
        assert(list2OutExpected == list2OutComputed);

//        printf("\n------------\n");

        listIn = {4};
        linkedListIn = convertToLinkedList(listIn);
        n = 0;
        linkedListsOutComputed = soln.reverseFirstNNodes(linkedListIn, n);
//        showList(linkedListsOutComputed.first.first);
//        showList(linkedListsOutComputed.first.second);
//        showList(linkedListsOutComputed.second);
//        printf("here-6\n");
        list1OutComputed = convertToList(linkedListsOutComputed.first.first);
//        printf("here-5\n");
        list2OutComputed = convertToList(linkedListsOutComputed.second);
        list1OutExpected = {};
        list2OutExpected = {4};
//        printf("here-4\n");
        assert(list1OutExpected == list1OutComputed);
//        printf("here-3\n");
        assert(list2OutExpected == list2OutComputed);

//        printf("\n------------\n");

//        printf("here-2\n");
        listIn = {4, 5, 6};
//        printf("here-1\n");
        linkedListIn = convertToLinkedList(listIn);
        n = 1;
//        printf("here0\n");
        linkedListsOutComputed = soln.reverseFirstNNodes(linkedListIn, n);
//        printf("here1\n");
//        showList(linkedListsOutComputed.first.first);
//        showList(linkedListsOutComputed.first.second);
//        showList(linkedListsOutComputed.second);
        list1OutComputed = convertToList(linkedListsOutComputed.first.first);
        list2OutComputed = convertToList(linkedListsOutComputed.second);
        list1OutExpected = {4};
        list2OutExpected = {5, 6};
        assert(list1OutExpected == list1OutComputed);
        assert(list2OutExpected == list2OutComputed);

        listIn = {4, 5, 6};
        linkedListIn = convertToLinkedList(listIn);
        n = 2;
        linkedListsOutComputed = soln.reverseFirstNNodes(linkedListIn, n);
        list1OutComputed = convertToList(linkedListsOutComputed.first.first);
        list2OutComputed = convertToList(linkedListsOutComputed.second);
        list1OutExpected = {5, 4};
        list2OutExpected = {6};
        assert(list1OutExpected == list1OutComputed);
        assert(list2OutExpected == list2OutComputed);

        listIn = {4, 5, 6};
        linkedListIn = convertToLinkedList(listIn);
        n = 3;
        linkedListsOutComputed = soln.reverseFirstNNodes(linkedListIn, n);
        list1OutComputed = convertToList(linkedListsOutComputed.first.first);
        list2OutComputed = convertToList(linkedListsOutComputed.second);
        list1OutExpected = {6, 5, 4};
        list2OutExpected = {};
        assert(list1OutExpected == list1OutComputed);
        assert(list2OutExpected == list2OutComputed);
    }

    void testReverseEvenLengthGroups() {
        Solution soln = Solution();
        list<int> listIn, listOutExpected, listOutComputed;
        ListNode* linkedListIn;
        ListNode* linkedListOutComputed;

        listIn = {1, 2, 3, 4, 5};
        listOutExpected = {1, 3, 2, 4, 5};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        listOutExpected = {1, 3, 2, 4, 5, 6, 9, 8, 7};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        soln.showList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        listOutExpected = {1, 3, 2, 4, 5, 6, 10, 9, 8, 7, 11, 12, 13, 14};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        listOutExpected = {1, 3, 2, 4, 5, 6, 10, 9, 8, 7, 11, 12, 13, 14};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        listOutExpected = {1, 3, 2, 4, 5, 6, 10, 9, 8, 7, 11, 12, 13, 14, 15};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        listOutExpected = {1, 3, 2, 4, 5, 6, 10, 9, 8, 7, 11, 12, 13, 14, 15, 16};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);

        listIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
        listOutExpected = {1, 3, 2, 4, 5, 6, 10, 9, 8, 7, 11, 12, 13, 14, 15, 18, 17, 16};
        linkedListIn = convertToLinkedList(listIn);
//        printf("here1\n");
        linkedListOutComputed = soln.reverseEvenLengthGroups(linkedListIn);
//        printf("here2\n");
        listOutComputed = convertToList(linkedListOutComputed);
//        printf("here3\n");
        assert(listOutExpected == listOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testReverseFirstNNodes();
    solnTest.testReverseEvenLengthGroups();

    return 0;
}
