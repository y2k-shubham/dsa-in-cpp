// LeetCode-430: https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

// Definition for a Node.
class Node {
   public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
   private:
    Node* flattenRec(Node* head, stack<Node*>& stk) {
        if (head == nullptr) {
            if (stk.empty()) {
                return nullptr;
            }

            Node* stkTopNode = stk.top();
            stk.pop();

            return flattenRec(stkTopNode, stk);
        }

        if (head->child == nullptr) {
            if ((head->next == nullptr) && !stk.empty()) {
                Node* stkTopNode = stk.top();
                stk.pop();

                head->next = stkTopNode;
                stkTopNode->prev = head;

                flattenRec(stkTopNode, stk);
            } else {
                flattenRec(head->next, stk);
            }
        } else {
            if (head->next != nullptr) {
                stk.push(head->next);
            }

            head->next = head->child;
            head->child->prev = head;

            flattenRec(head->child, stk);

            head->child = nullptr;
        }

        return head;
    }

   public:
    Node* flatten(Node* head) {
        stack<Node*> stk;
        return flattenRec(head, stk);
    }
};
