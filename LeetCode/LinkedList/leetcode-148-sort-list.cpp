// LeetCode-148: https://leetcode.com/problems/sort-list/
// standard merge-sort on linked list

#include <cstdio>
#include <iostream>
#include <cassert>
#include <utility>
#include <list>

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
    // only for testing / debugging
    bool debug = false;

    // only for testing / debugging
    ListNode *createNode(int val) {
        ListNode *newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    // only for testing / debugging
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

    // only for testing / debugging
    list<int> createStdList(ListNode *head) {
        list<int> mList;
        for (ListNode *list = head; list != nullptr; list = list->next) {
            mList.push_back(list->val);
        }

        return mList;
    }

    // only for testing / debugging
    void showStdList(list<int>& mList) {
        printf("list is:-\n");
        for (list<int>::iterator it = mList.begin(); it != mList.end(); it++) {
            printf("%d ", *it);
        }
        cout << endl;
    }

    ListNode* findMidNode(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr) || (head->next->next == nullptr)) {
            return head;
        }
        
        ListNode* slowPtr = head;
        ListNode* fastPtr = head;
        while ((fastPtr != nullptr) && (fastPtr->next != nullptr) && (fastPtr->next->next != nullptr)) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        
        return slowPtr;
    }
    
    ListNode* mergeSort(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return head;
        }
        
        ListNode* midNode = findMidNode(head);
        ListNode* rHead = nullptr;
        if (midNode != nullptr) {
            rHead = midNode->next;
            midNode->next = nullptr;
        }
        
        ListNode* lSortedHead = mergeSort(head);
        ListNode* rSortedHead = mergeSort(rHead);
        
        ListNode* sortedHead = merge(lSortedHead, rSortedHead);
        
        return sortedHead;
    }
    
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* headSorted = nullptr;
        ListNode* listSorted = nullptr;
        
        ListNode* list1 = head1;
        ListNode* list2 = head2;
        
        while ((list1 != nullptr) && (list2 != nullptr)) {
            ListNode* newNode = nullptr;
            
            if (list1->val <= list2->val) {
                newNode = list1;
                list1 = list1->next;
            } else {
                newNode = list2;
                list2 = list2->next;
            }
            
            if (headSorted == nullptr) {
                headSorted = newNode;
                listSorted = newNode;
            } else {
                listSorted->next = newNode;
                listSorted = newNode;
            }
        }
        
        if (list1 != nullptr) {
            listSorted->next = list1;
        } else if (list2 != nullptr) {
            listSorted->next = list2;
        }
        
        return headSorted;
    }
    
public:
    friend class SolutionTest;

    // poor runtime; LC submission: speed 6 %tile, memory 53 %tile
    ListNode* sortList(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return head;
        }
        
        return mergeSort(head);
    }
};

class SolutionTest {
public:
     void testFindMidNode() {
       Solution soln = Solution();
       list <int> stdListIn;
       ListNode* lListIn;
       ListNode* lListOutComputed;
       list <int> stdListOutExpected;
       list <int> stdListOutComputed;

       stdListIn = {};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {};
       assert(stdListOutExpected == stdListOutComputed);

       stdListIn = {6};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {6};
       assert(stdListOutExpected == stdListOutComputed);

       stdListIn = {6, 5};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {6, 5};
       assert(stdListOutExpected == stdListOutComputed);

       stdListIn = {6, 5, 9};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {5, 9};
       assert(stdListOutExpected == stdListOutComputed);

       stdListIn = {6, 5, 9, 1};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {5, 9, 1};
       assert(stdListOutExpected == stdListOutComputed);

       stdListIn = {6, 5, 9, 1, 3};
       lListIn = soln.createLinkedList(stdListIn);
       lListOutComputed = soln.findMidNode(lListIn);
       stdListOutComputed = soln.createStdList(lListOutComputed);
       stdListOutExpected = {9, 1, 3};
       assert(stdListOutExpected == stdListOutComputed);
     }
};

int main() {
  SolutionTest solnTest = SolutionTest();

  solnTest.testFindMidNode();

  return 0;
}
