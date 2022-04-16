// LeetCode-725: https://leetcode.com/problems/split-linked-list-in-parts/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

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

    int findLength(ListNode *head) {
        int len = 0;
        for (ListNode *list = head; list != nullptr; list = list->next) {
            len++;
        }

        return len;
    }

    ListNode *splitListHead(ListNode *head, int reqNumNodes) {
        if (reqNumNodes <= 0) {
            return head;
        }

        ListNode *list;
        int gotNumNodes = 0;
        for (list = head; gotNumNodes < (reqNumNodes - 1); list = list->next) {
            gotNumNodes++;
        }

        ListNode *listNext = nullptr;
        if (list != nullptr) {
            listNext = list->next;
            list->next = nullptr;
        }

        return listNext;
    }

    string stringify(ListNode *head) {
        if (head == nullptr) {
            return "[]";
        }

        ostringstream oss;
        oss << "[" << head->val;

        for (ListNode *list = head->next; list != nullptr; list = list->next) {
            oss << "," << list->val;
        }

        oss << "]";
        return oss.str();
    }

    string stringify(vector<ListNode *>& listVec) {
        if (listVec.empty()) {
            return "[]";
        }

        ostringstream oss;
        oss << "[" << stringify(listVec[0]);

        for (int i = 1; i < listVec.size(); i++) {
            oss << "," << stringify(listVec[i]);
        }

        oss << "]";

        return oss.str();
    }

public:
    vector<ListNode *> splitListToParts(ListNode *head, int k) {
        vector<ListNode *> listParts(k, nullptr);

        int len = findLength(head);
        ListNode *list = head;

        if (k >= len) {
            for (int i = 1; i <= len; i++) {
                listParts[i - 1] = list;
                list = splitListHead(list, 1);
            }
        } else {
            int avgNumNodes = len / k;
            int numExtraNodes = len % k;
            if (debug) {
                printf("avgNumNodes=%d, numExtraNodes=%d\n", avgNumNodes, numExtraNodes);
            }

            for (int i = 1; i <= k; i++) {
                listParts[i - 1] = list;
                if (numExtraNodes > 0) {
                    list = splitListHead(list, avgNumNodes + 1);
                    numExtraNodes--;
                } else {
                    list = splitListHead(list, avgNumNodes);
                }

                if (debug) {
                    printf("\n----------\n");
                    printf("after iter i=%d\n\n", i);

                    printf("..........\n");
                    printf("listParts are:-\n%s\n", stringify(listParts).c_str());

                    printf("..........\n");
                    printf("list is:-\n%s\n", stringify(list).c_str());
                }
            }
        }

        return listParts;
    }
};
