// LeetCode-1669: https://leetcode.com/problems/merge-in-between-linked-lists/
// wrong answer; same test case passing locally but failing on LeetCode

#include <utility>
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
    ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    ListNode* convertToLinkedList(list<int>& mList) {
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

    // unused method accidentally written earlier when we mis-interpreted the question
    pair<ListNode*, ListNode*> splitListAtNodeVal(ListNode* head, int target) {
        if (head == nullptr) {
            return {nullptr, nullptr};
        }

        ListNode* list = head;
        while ((list != nullptr) && (list->val != target)) {
            list = list->next;
        }

        if (list == nullptr) {
            return {head, nullptr};
        }

        ListNode* headNext = list->next;
        list->next = nullptr;
        return {head, headNext};
    }

    pair<ListNode*, ListNode*> splitListAtNodeIdx(ListNode* head, int idx) {
        if (head == nullptr) {
            return {nullptr, nullptr};
        }

        ListNode* list = head;
        int i = 0;
        while ((list != nullptr) && (i != idx)) {
            list = list->next;
            i++;
        }

        if (list == nullptr) {
            return {head, nullptr};
        }

        ListNode* headNext = list->next;
        list->next = nullptr;
        return {head, headNext};
    }

    // unused method accidentally written earlier when we mis-interpreted the question
    pair<ListNode*, ListNode*> splitListBeforeNodeVal(ListNode* head, int target) {
        if (head == nullptr) {
            return {nullptr, nullptr};
        }

        ListNode* prev = nullptr;
        ListNode* list = head;
        while ((list != nullptr) && (list->val != target)) {
            prev = list;
            list = list->next;
        }

        if (prev == nullptr) {
            return {nullptr, head};
        }

        prev->next = nullptr;
        return {head, list};
    }

    pair<ListNode*, ListNode*> splitListBeforeNodeIdx(ListNode* head, int idx) {
        if (head == nullptr) {
            return {nullptr, nullptr};
        }

        ListNode* prev = nullptr;
        ListNode* list = head;
        int i = 0;
        while ((list != nullptr) && (i != idx)) {
            prev = list;
            list = list->next;
            i++;
        }

        if (prev == nullptr) {
            return {nullptr, head};
        }

        prev->next = nullptr;
        return {head, list};
    }

    ListNode* getTail(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* list = head;
        while (list->next != nullptr) {
            list = list->next;
        }
        return list;
    }

    void showSplit(pair<ListNode*, ListNode*> split) {
        printf("split.first: ");
        showList(split.first);

        printf("split.second: ");
        showList(split.second);
    }

    void showList(ListNode* head) {
        for (ListNode* list = head; list != nullptr; list = list->next) {
//            printf("(%d) ", list->val);
            cout << list->val << " ";
        }
        cout << endl;
    }

public:
    friend class SolutionTest;

    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        pair<ListNode*, ListNode*> split1 = splitListAtNodeIdx(list1, b);
//        printf("after splitting at b=%d\n", b);
//        showSplit(split1);

        if (split1.first == nullptr) {
            getTail(list2)->next = split1.second;
            return list2;
        }

        pair<ListNode*, ListNode*> split2 = splitListBeforeNodeIdx(list1, a);
//        printf("after splitting at a=%d\n", a);
//        showSplit(split2);

        if (split2.first == nullptr) {
            getTail(list2)->next = split1.second;
            return list2;
        }

        getTail(split2.first)->next = list2;
        getTail(list2)->next = split1.second;
        return split2.first;
    }
};

class SolutionTest {
public:
    void testMergeInBetween() {
        Solution soln = Solution();
        list<int> list1In;
        ListNode* linkedList1In;
        list<int> list2In;
        ListNode* linkedList2In;
        int a, b;
        ListNode* linkedListOutComputed;
        list<int> listOutExpected;
        list<int> listOutComputed;

        list1In = {0, 1, 2, 3, 4, 5, 6};
        list2In = {1000000, 1000001, 1000002};
        a = 6;
        b = 6;
        listOutExpected = {0, 1, 2, 3, 4, 5, 1000000, 1000001, 1000002};
//        printf("came here -3\n");
        linkedList1In = soln.convertToLinkedList(list1In);
//        printf("came here -2\n");
//        soln.showList(linkedList1In);
//        printf("came here -1\n");
        linkedList2In = soln.convertToLinkedList(list2In);
//        printf("came here 0\n");
//        soln.showList(linkedList1In);
//        soln.showList(linkedList2In);
        linkedListOutComputed = soln.mergeInBetween(linkedList1In, a, b, linkedList2In);
//        printf("came here 1\n");
        listOutComputed = soln.convertToList(linkedListOutComputed);
//        printf("came here 2\n");
//        soln.showList(linkedListOutComputed);
//        printf("came here 3\n");
        assert(listOutExpected == listOutComputed);

        list1In = {0, 1, 2, 3, 4, 5, 6};
        list2In = {1000000, 1000001, 1000002};
        a = 1;
        b = 6;
        listOutExpected = {0, 1000000, 1000001, 1000002};
        linkedList1In = soln.convertToLinkedList(list1In);
        linkedList2In = soln.convertToLinkedList(list2In);
        linkedListOutComputed = soln.mergeInBetween(linkedList1In, a, b, linkedList2In);
        listOutComputed = soln.convertToList(linkedListOutComputed);
        assert(listOutExpected == listOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMergeInBetween();

    return 0;
}
