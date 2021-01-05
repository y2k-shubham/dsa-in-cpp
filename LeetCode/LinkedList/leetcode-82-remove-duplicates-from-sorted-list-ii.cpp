// LeetCode-82: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// LC Jan 2021 challenge: https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3593/

// Not easy; quite a few edge cases

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
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
   public:
    ListNode* deleteDuplicates(ListNode* list) {
        if (list != nullptr) {
            int val = list->val;

            // eat up duplicate nodes
            bool foundDupes = false;
            if (list->next != nullptr && list->next->val == val) {
                while (list != nullptr && list->val == val) {
                    list = list->next;
                    foundDupes = true;
                }
            }

            if (foundDupes) {
                // if duplicates were found (and therefore consumed), then
                // (1) dedupRec(list) would NOT lead to infinite recursion
                // (2) also in that case we need not do any 'wiring'
                list = deleteDuplicates(list);
            } else if (list != nullptr) {
                // else we do just a basic 'wiring'
                // (and converging recursive call)
                list->next = deleteDuplicates(list->next);
            }
        }

        return list;
    }
};
