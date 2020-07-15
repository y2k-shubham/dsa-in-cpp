// https://leetcode.com/problems/merge-k-sorted-lists/
// https://www.geeksforgeeks.org/merge-k-sorted-linked-lists-set-2-using-min-heap/
// priority-queue reference: https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
// C++ structs: https://www.geeksforgeeks.org/difference-c-structures-c-structures/

#include <cstdio>
#include <iostream>
#include <queue>
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

ListNode* mergeKLists(vector<ListNode*>&, bool);
// min priority queue using STL https://www.geeksforgeeks.org/implement-min-heap-using-stl/
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > buildPQue(vector<ListNode*>&);
ListNode* buildList(vector<int>);
void showList(ListNode*);
void showVec(vector<ListNode*> lists);
void showPQue(priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >);

int main() {
    vector<ListNode*> lists;

    // g++ -std=c++11 LeetCode/Heap-PriorityQueue/merge-k-sorted-lists.cpp
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));

    showVec(lists);

    bool debug = false;
    ListNode* mergedList = mergeKLists(lists, debug);
    showList(mergedList);

    return 0;
}

ListNode* mergeKLists(vector<ListNode*>& lists, bool debug) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pQue = buildPQue(lists);
    if (debug) {
        showPQue(pQue);
    }

    ListNode* mergedListHead = nullptr;
    ListNode* mergedList = nullptr;
    while (!pQue.empty()) {
        // retrieve the smallest value from pQue
        pair<int, int> smallestValIndPair = pQue.top();
        int smallestVal = smallestValIndPair.first;
        int smallestValInd = smallestValIndPair.second;
        pQue.pop();

        if (debug) {
            printf("\n-------\n");
            printf("popped smallest element [%d]=%d from pQue\n", smallestValInd, smallestVal);
        }

        // push smallest value into merged list
        ListNode* smallestNode = lists[smallestValInd];
        if (mergedList == nullptr) {
            mergedListHead = mergedList = smallestNode;
        } else {
            mergedList->next = smallestNode;
            mergedList = smallestNode;
        }

        // advance the list in which smallest value was found
        lists[smallestValInd] = smallestNode->next;
        mergedList->next = nullptr;

        // post advancing, add the new node in pQue
        if (lists[smallestValInd] != nullptr) {
            ListNode* node = lists[smallestValInd];
            pQue.push(make_pair(node->val, smallestValInd));
        }
    }

    return mergedListHead;
}

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > buildPQue(vector<ListNode*>& lists) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pQue;
    for (int i = 0; i < lists.size(); i++) {
        // fuckers had passed null linked list inputs in test cases
        if (lists[i] != nullptr) {
            pQue.push(make_pair(lists[i]->val, i));
        }
    }
    return pQue;
}

ListNode* buildList(vector<int> vec) {
    ListNode* head = nullptr;
    ListNode* list = nullptr;

    for (int i = 0; i < vec.size(); i++) {
        ListNode* newNode = new ListNode;
        newNode->val = vec[i];
        newNode->next = nullptr;

        if (list == nullptr) {
            head = list = newNode;
        } else {
            list->next = newNode;
            list = newNode;
        }
    }

    return head;
}

void showList(ListNode* head) {
    for (ListNode* list = head; list != nullptr; list = list->next) {
        printf("%d, ", list->val);
    }
    cout << endl;
}

void showVec(vector<ListNode*> lists) {
    for (int i = 0; i < lists.size(); i++) {
        printf("[%d] : ", i);
        showList(lists[i]);
    }
}

void showPQue(priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pQue) {
    while (!pQue.empty()) {
        pair<int, int> topPair = pQue.top();
        printf("[%d] -> %d\n", topPair.second, topPair.first);
        pQue.pop();
    }
}
