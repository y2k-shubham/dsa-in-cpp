// LeetCode-445: https://leetcode.com/problems/add-two-numbers-ii/
// easier soln, also faster & lower space
// LC-submission: speed 90% tile

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>

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

    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

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

    ListNode* addLists(ListNode* head1, ListNode* head2) {
        ListNode* headSum = nullptr;
        ListNode* listSum = nullptr;

        ListNode* list1 = head1;
        ListNode* list2 = head2;
        int carry = 0;
        while ((list1 != nullptr) || (list2 != nullptr) || (carry > 0)) {
            int list1Val = 0;
            if (list1 != nullptr) {
                list1Val = list1->val;
                list1 = list1->next;
            }

            int list2Val = 0;
            if (list2 != nullptr) {
                list2Val = list2->val;
                list2 = list2->next;
            }

            int sum = list1Val + list2Val + carry;

            int dig = sum % 10;
            carry = sum / 10;

            ListNode* newNode = createNode(dig);
            if (headSum == nullptr) {
                headSum = listSum = newNode;
            } else {
                listSum->next = newNode;
                listSum = newNode;
            }
        }

        return headSum;
    }

    ListNode* convertToLL(list<int>& mList) {
        ListNode* llHead = nullptr;
        ListNode* llList;

        for (list<int>::iterator it = mList.begin(); it != mList.end(); it++) {
            ListNode* newNode = createNode(*it);
            if (llHead == nullptr) {
                llHead = llList = newNode;
            } else {
                llList->next = newNode;
                llList = newNode;
            }
        }

        return llHead;
    }

    list<int> convertToList(ListNode* llHead) {
        list<int> mList;
        for (ListNode* llList = llHead; llList != nullptr; llList = llList->next) {
            mList.push_back(llList->val);
        }

        return mList;
    }

    void showList(list<int>& mList) {
        printf("List is:-\n");
        for (list<int>::iterator it = mList.begin(); it != mList.end(); it++) {
            printf("%d ", *it);
        }
        cout << endl;
    }

   public:
    friend class SolutionTest;
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        ListNode* l1Rev = reverseList(l1);
        ListNode* l2Rev = reverseList(l2);

        ListNode* lSumRev = addLists(l1Rev, l2Rev);
        ListNode* lSum = reverseList(lSumRev);

        return lSum;
    }
};

class SolutionTest {
   public:
    void testReverseList() {
        Solution soln = Solution();
        list<int> inList;
        ListNode* inLLHead;
        ListNode* outLLHeadComputed;
        list<int> outListComputed;
        list<int> outListExpected;

        inList = {};
        outListExpected = {};
        inLLHead = soln.convertToLL(inList);
        outLLHeadComputed = soln.reverseList(inLLHead);
        outListComputed = soln.convertToList(outLLHeadComputed);
        assert(outListExpected == outListComputed);

        inList = {4};
        outListExpected = {4};
        inLLHead = soln.convertToLL(inList);
        outLLHeadComputed = soln.reverseList(inLLHead);
        outListComputed = soln.convertToList(outLLHeadComputed);
        assert(outListExpected == outListComputed);

        inList = {4, 5};
        outListExpected = {5, 4};
        inLLHead = soln.convertToLL(inList);
        outLLHeadComputed = soln.reverseList(inLLHead);
        outListComputed = soln.convertToList(outLLHeadComputed);
        assert(outListExpected == outListComputed);

        inList = {9, 1, 7};
        outListExpected = {7, 1, 9};
        inLLHead = soln.convertToLL(inList);
        outLLHeadComputed = soln.reverseList(inLLHead);
        outListComputed = soln.convertToList(outLLHeadComputed);
        assert(outListExpected == outListComputed);
    }

    void testAddLists() {
        Solution soln = Solution();
        list<int> inList1, inList2;
        ListNode* inLL1;
        ListNode* inLL2;
        ListNode* outLL;
        list<int> outListExpected;
        list<int> outListComputed;

        inList1 = {};
        inList2 = {};
        outListExpected = {};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {5};
        inList2 = {};
        outListExpected = {5};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {4, 5};
        inList2 = {};
        outListExpected = {4, 5};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {4, 5, 9};
        inList2 = {};
        outListExpected = {4, 5, 9};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {4, 5, 9, 6};
        inList2 = {};
        outListExpected = {4, 5, 9, 6};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {4, 5, 9};
        inList2 = {2};
        outListExpected = {6, 5, 9};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {4, 5, 9};
        inList2 = {8, 7};
        outListExpected = {2, 3, 0, 1};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addLists(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);
    }

    void testAddTwoNumbers() {
        Solution soln = Solution();
        list<int> inList1, inList2;
        ListNode* inLL1;
        ListNode* inLL2;
        ListNode* outLL;
        list<int> outListExpected;
        list<int> outListComputed;

        inList1 = {};
        inList2 = {};
        outListExpected = {};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addTwoNumbers(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        assert(outListExpected == outListComputed);

        inList1 = {7, 2, 4, 3};
        inList2 = {5, 6, 4};
        outListExpected = {7, 8, 0, 7};
        inLL1 = soln.convertToLL(inList1);
        inLL2 = soln.convertToLL(inList2);
        outLL = soln.addTwoNumbers(inLL1, inLL2);
        outListComputed = soln.convertToList(outLL);
        // soln.showList(outListComputed);
        assert(outListExpected == outListComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testReverseList();
    solnTest.testAddLists();
    solnTest.testAddTwoNumbers();

    return 0;
}
