// LeetCode-143: https://leetcode.com/problems/reorder-list/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

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

        newNode->next = nullptr;
        newNode->val = val;

        return newNode;
    }

    ListNode* convertToLinkedList(vector<int>& vec) {
        ListNode* head = nullptr;
        ListNode* list = nullptr;

        for (int i = 0; i < vec.size(); i++) {
            int crrVal = vec[i];
            ListNode* newNode = createNode(crrVal);

            if (head == nullptr) {
                head = list = newNode;
            } else {
                list->next = newNode;
                list = newNode;
            }
        }

        return head;
    }

    stack<ListNode*> convertToStack(vector<int>& vec) {
        stack<ListNode*> stk;
        for (int i = 0; i < vec.size(); i++) {
            stk.push(createNode(vec[i]));
        }

        return stk;
    }

    vector<int> convertToVec(ListNode* list) {
        vector<int> vec;
        while (list != nullptr) {
            vec.push_back(list->val);
            list = list->next;
        }

        return vec;
    }

    vector<int> convertToVec(stack<ListNode*>& stk) {
        int len = stk.size();
        vector<int> vec(len);

        int i = 0;
        while (!stk.empty()) {
            vec[i++] = stk.top()->val;
            stk.pop();
        }

        reverse(vec.begin(), vec.end());

        return vec;
    }

    void showList(ListNode* head) {
        printf("\nLinkedList is:-\n");
        for (ListNode* list = head; list != nullptr; list = list->next) {
            printf("%d ", list->val);
        }
        cout << endl;
    }

    void showStack(stack<ListNode*> stk) {
        printf("\nStack is:-\n");
        while (!stk.empty()) {
            printf("%d ", stk.top()->val);
            stk.pop();
        }
        cout << endl;
    }

    stack<ListNode*> extractEvenPosNodes(ListNode* head) {
        stack<ListNode*> evenPosNodes;

        ListNode *prevNode, *crrNode;
        int i = 1;
        for (prevNode = nullptr, crrNode = head; crrNode != nullptr;) {
            if ((i % 2) == 0) {
                evenPosNodes.push(crrNode);
                prevNode->next = crrNode->next;
            } else {
                prevNode = crrNode;
            }

            crrNode = crrNode->next;
            i++;
        }

        if (prevNode != nullptr) {
            prevNode->next = nullptr;
        }

        return evenPosNodes;
    }

    void interleaveNodes(ListNode* head, stack<ListNode*>& stk) {
        ListNode *crrNode, *nextNode;

        crrNode = head;
        nextNode = (crrNode == nullptr) ? nullptr : crrNode->next;
        while ((nextNode != nullptr) && !stk.empty()) {
            ListNode* interleavedNode = stk.top();
            stk.pop();

            // printf("popped %d here\n", interleavedNode->val);
            // printf("setting crrNode(%d)->next = interleavedNode(%d)\n", crrNode->val, interleavedNode->val);

            crrNode->next = interleavedNode;
            interleavedNode->next = nextNode;

            crrNode = nextNode;
            nextNode = nextNode->next;
        }

        if (!stk.empty() && (crrNode != nullptr)) {
            ListNode* interleavedNode = stk.top();
            stk.pop();

            // printf("setting crrNode(%d)->next = interleavedNode(%d)\n", crrNode->val, interleavedNode->val);

            crrNode->next = interleavedNode;
            interleavedNode->next = nextNode;
        }
    }

   public:
    friend class SolutionTest;

    void reorderList(ListNode* head) {
        stack<ListNode*> evenPosNodes = extractEvenPosNodes(head);
        interleaveNodes(head, evenPosNodes);
    }
};

class SolutionTest {
   private:
   public:
    void testExtractEvenPosNodes() {
        Solution soln = Solution();
        vector<int> inVec;
        ListNode* inHead;
        stack<ListNode*> outStack;
        vector<int> outListVecExpected, outListVecComputed;
        vector<int> outStackVecExpected, outStackVecComputed;

        inVec = {};
        outListVecExpected = {};
        outStackVecExpected = {};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {3};
        outListVecExpected = {3};
        outStackVecExpected = {};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {3, 4};
        outListVecExpected = {3};
        outStackVecExpected = {4};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {9, 8, 3};
        outListVecExpected = {9, 3};
        outStackVecExpected = {8};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {9, 8, 3, 5};
        outListVecExpected = {9, 3};
        outStackVecExpected = {8, 5};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {9, 8, 3, 5, 6};
        outListVecExpected = {9, 3, 6};
        outStackVecExpected = {8, 5};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);

        inVec = {9, 8, 3, 5, 6, 1};
        outListVecExpected = {9, 3, 6};
        outStackVecExpected = {8, 5, 1};
        inHead = soln.convertToLinkedList(inVec);
        outStack = soln.extractEvenPosNodes(inHead);
        outStackVecComputed = soln.convertToVec(outStack);
        assert(outStackVecExpected == outStackVecComputed);
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);
    }

    void testInterleaveNodes() {
        Solution soln = Solution();
        ListNode* inHead = nullptr;
        vector<int> inListVec, inStackVec;
        vector<int> outListVecExpected, outListVecComputed;
        stack<ListNode*> inStack;

        inListVec = {};
        inStackVec = {};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {};
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());

        inListVec = {3};
        inStackVec = {};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {3};
        outListVecComputed = soln.convertToVec(inHead);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());

        inListVec = {2};
        inStackVec = {1};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        // soln.showStack(inStack);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {2, 1};
        outListVecComputed = soln.convertToVec(inHead);
        // soln.showList(inHead);
        // soln.showStack(inStack);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());

        inListVec = {2, 3};
        inStackVec = {1, 9};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        // soln.showStack(inStack);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {2, 9, 3, 1};
        outListVecComputed = soln.convertToVec(inHead);
        // soln.showList(inHead);
        // soln.showStack(inStack);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());

        inListVec = {2, 3, 4};
        inStackVec = {1, 9};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        // soln.showStack(inStack);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {2, 9, 3, 1, 4};
        outListVecComputed = soln.convertToVec(inHead);
        // soln.showList(inHead);
        // soln.showStack(inStack);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());

        inListVec = {2, 3, 4};
        inStackVec = {1, 9, 8};
        inHead = soln.convertToLinkedList(inListVec);
        inStack = soln.convertToStack(inStackVec);
        // soln.showStack(inStack);
        soln.interleaveNodes(inHead, inStack);
        outListVecExpected = {2, 8, 3, 9, 4, 1};
        outListVecComputed = soln.convertToVec(inHead);
        // soln.showList(inHead);
        // soln.showStack(inStack);
        assert(outListVecExpected == outListVecComputed);
        assert(inStack.empty());
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testExtractEvenPosNodes();
    solnTest.testInterleaveNodes();

    return 0;
}
