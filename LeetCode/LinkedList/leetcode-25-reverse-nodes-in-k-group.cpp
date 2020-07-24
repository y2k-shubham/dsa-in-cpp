// LeetCode 25: https://leetcode.com/problems/reverse-nodes-in-k-group/
// http://buttercola.blogspot.com/2014/09/leetcode-reverse-nodes-in-k-group.html
// quite hard problem

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node() : val(0), next(nullptr) {}
    Node(int x) : val(x), next(nullptr) {}
    Node(int x, Node* next) : val(x), next(next) {}
};

Node* createNode(int val);
void showList(Node* head, int k, string name);
void testBuildList();
Node* buildList(vector<int> vec);
vector<int> getListEles(Node* head);
void testRevListRec();
Node* revListRec(Node* head);
pair<Node*, Node*> splitAtKthNode(Node*, int);
void testSplitAtKthNode();
void testGetLength();
int getLength(Node*);
void testReverseKGroupRec();
Node* reverseKGroupRec(Node* head, int k);
// TODO
void testReverseKGroup();
Node* reverseKGroup(Node* head, int k);

int main() {
    testBuildList();
    testRevListRec();
    testSplitAtKthNode();
    testGetLength();
    testReverseKGroupRec();
    // TODO
    // testReverseKGroup();

    return 0;
}

Node* createNode(int val) {
    Node* newNode = new Node;
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void showList(Node* head, int k, string name) {
    int i;
    Node* list;

    printf("\n%s list is:-\n", name.c_str());

    printf("Ind:\t");
    for (list = head, i = 0; list != NULL && i < k; list = list->next, i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (list = head, i = 0; list != NULL && i < k; list = list->next, i++) {
        printf("%d -> \t", list->val);
    }
    cout << endl;
}

void testBuildList() {
    Node* list;
    vector<int> outExpected;
    vector<int> outComputed;

    outExpected = {};
    list = buildList(outExpected);
    outComputed = getListEles(list);
    assert(outExpected == outComputed);

    outExpected = {1};
    list = buildList(outExpected);
    outComputed = getListEles(list);
    assert(outExpected == outComputed);

    outExpected = {1, 2};
    list = buildList(outExpected);
    // showList(list, 999, "");
    outComputed = getListEles(list);
    assert(outExpected == outComputed);

    outExpected = {1, 2, 3};
    list = buildList(outExpected);
    outComputed = getListEles(list);
    assert(outExpected == outComputed);

    outExpected = {1, 2, 3, 4};
    list = buildList(outExpected);
    outComputed = getListEles(list);
    assert(outExpected == outComputed);
}

Node* buildList(vector<int> vec) {
    if (vec.empty()) {
        return NULL;
    } else {
        Node* head;
        Node* list;

        head = createNode(vec[0]);
        list = head;
        for (int i = 1; i < vec.size(); i++) {
            Node* newNode = createNode(vec[i]);
            list->next = newNode;
            list = newNode;
        }

        return head;
    }
}

vector<int> getListEles(Node* head) {
    vector<int> eles;
    for (Node* list = head; list != NULL; list = list->next) {
        eles.push_back(list->val);
    }
    return eles;
}

void testRevListRec() {
    Node* inpList;
    Node* outList;
    vector<int> outExpected;
    vector<int> outComputed;

    inpList = buildList({});
    outExpected = {};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    outExpected = {2, 1};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3});
    outExpected = {3, 2, 1};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {4, 3, 2, 1};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5});
    outExpected = {5, 4, 3, 2, 1};
    outList = revListRec(inpList);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);
}

Node* revListRec(Node* list) {
    if (list == NULL || list->next == NULL) {
        return list;
    } else {
        Node* nextNode = list->next;
        list->next = NULL;

        Node* newHead = revListRec(nextNode);
        nextNode->next = list;

        return newHead;
    }
}

void testSplitAtKthNode() {
    Node* inpList;
    pair<Node*, Node*> outLists;
    vector<int> outExp1;
    vector<int> outExp2;
    vector<int> outComp1;
    vector<int> outComp2;

    inpList = buildList({});
    outLists = splitAtKthNode(inpList, 0);
    outExp1 = {};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({});
    outLists = splitAtKthNode(inpList, 10);
    outExp1 = {};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1});
    outLists = splitAtKthNode(inpList, 0);
    outExp1 = {};
    outExp2 = {1};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1});
    outLists = splitAtKthNode(inpList, 1);
    outExp1 = {1};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1});
    outLists = splitAtKthNode(inpList, 2);
    outExp1 = {1};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2});
    outLists = splitAtKthNode(inpList, 0);
    outExp1 = {};
    outExp2 = {1, 2};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2});
    outLists = splitAtKthNode(inpList, 1);
    outExp1 = {1};
    outExp2 = {2};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2});
    outLists = splitAtKthNode(inpList, 2);
    outExp1 = {1, 2};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2});
    outLists = splitAtKthNode(inpList, 3);
    outExp1 = {1, 2};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3});
    outLists = splitAtKthNode(inpList, 2);
    outExp1 = {1, 2};
    outExp2 = {3};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3, 4, 5});
    outLists = splitAtKthNode(inpList, 2);
    outExp1 = {1, 2};
    outExp2 = {3, 4, 5};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3, 4, 5});
    outLists = splitAtKthNode(inpList, 3);
    outExp1 = {1, 2, 3};
    outExp2 = {4, 5};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3, 4, 5});
    outLists = splitAtKthNode(inpList, 4);
    outExp1 = {1, 2, 3, 4};
    outExp2 = {5};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3, 4, 5});
    outLists = splitAtKthNode(inpList, 5);
    outExp1 = {1, 2, 3, 4, 5};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);

    inpList = buildList({1, 2, 3, 4, 5});
    outLists = splitAtKthNode(inpList, 6);
    outExp1 = {1, 2, 3, 4, 5};
    outExp2 = {};
    outComp1 = getListEles(outLists.first);
    outComp2 = getListEles(outLists.second);
    assert(outExp1 == outComp1);
    assert(outExp2 == outComp2);
}

pair<Node*, Node*> splitAtKthNode(Node* head, int k) {
    if (head == NULL) {
        return make_pair(nullptr, nullptr);
    } else if (k == 0) {
        return make_pair(nullptr, head);
    } else {
        Node* list;
        int i;

        for (list = head, i = 1; list != NULL && i < k; list = list->next, i++)
            ;

        if (list == NULL) {
            return make_pair(head, nullptr);
        } else {
            Node* rHead = list->next;
            list->next = NULL;
            return make_pair(head, rHead);
        }
    }
}

void testGetLength() {
    Node* inp;

    inp = buildList({});
    assert(getLength(inp) == 0);

    inp = buildList({1});
    assert(getLength(inp) == 1);

    inp = buildList({1, 2});
    assert(getLength(inp) == 2);

    inp = buildList({1, 2, 3});
    assert(getLength(inp) == 3);

    inp = buildList({1, 2, 3, 4});
    assert(getLength(inp) == 4);

    inp = buildList({1, 2, 3, 4, 5});
    assert(getLength(inp) == 5);
}

int getLength(Node* head) {
    int i;
    Node* list;

    for (i = 0, list = head; list != NULL; list = list->next, i++)
        ;

    return i;
}

void testReverseKGroupRec() {
    Node* inpList;
    Node* outList;
    vector<int> outExpected;
    vector<int> outComputed;

    inpList = buildList({});
    outExpected = {};
    outList = reverseKGroupRec(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({});
    outExpected = {};
    outList = reverseKGroupRec(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroupRec(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroupRec(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroupRec(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    outExpected = {1, 2};
    outList = reverseKGroupRec(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    // showList(inpList, 999, "in1");
    outExpected = {2, 1};
    // showList(buildList(outExpected), 999, "out1");
    outList = reverseKGroupRec(inpList, 2);
    // showList(outList, 999, "out2");
    outComputed = getListEles(outList);
    // showList(buildList(outComputed), 999, "out3");
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    outExpected = {1, 2};
    outList = reverseKGroupRec(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroupRec(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroupRec(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {2, 1, 4, 3};
    outList = reverseKGroupRec(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {3, 2, 1, 4};
    outList = reverseKGroupRec(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {4, 3, 2, 1};
    outList = reverseKGroupRec(inpList, 4);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroupRec(inpList, 5);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {2, 1, 4, 3, 6, 5, 7};
    outList = reverseKGroupRec(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {3, 2, 1, 6, 5, 4, 7};
    outList = reverseKGroupRec(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {4, 3, 2, 1, 5, 6, 7};
    outList = reverseKGroupRec(inpList, 4);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);
}

Node* reverseKGroupRec(Node* head, int k) {
    if (head == NULL) {
        return nullptr;
        // following getLength converts this into O(n^2)
    } else if (k <= 1 || getLength(head) < k) {
        return head;
    } else {
        pair<Node*, Node*> splits = splitAtKthNode(head, k);

        Node* leftTail = head;
        Node* firstHead = revListRec(splits.first);

        Node* remList = splits.second;

        Node* rightHead = reverseKGroupRec(remList, k);
        leftTail->next = rightHead;

        return firstHead;
    }
}

void testReverseKGroup() {
    Node* inpList;
    Node* outList;
    vector<int> outExpected;
    vector<int> outComputed;

    inpList = buildList({});
    outExpected = {};
    outList = reverseKGroup(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({});
    outExpected = {};
    outList = reverseKGroup(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroup(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroup(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1});
    outExpected = {1};
    outList = reverseKGroup(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    outExpected = {1, 2};
    outList = reverseKGroup(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    // showList(inpList, 999, "in1");
    outExpected = {2, 1};
    // showList(buildList(outExpected), 999, "out1");
    outList = reverseKGroup(inpList, 2);
    // showList(outList, 999, "out2");
    outComputed = getListEles(outList);
    // showList(buildList(outComputed), 999, "out3");
    assert(outExpected == outComputed);

    inpList = buildList({1, 2});
    outExpected = {1, 2};
    outList = reverseKGroup(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroup(inpList, 0);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroup(inpList, 1);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {2, 1, 4, 3};
    outList = reverseKGroup(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {3, 2, 1, 4};
    outList = reverseKGroup(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {4, 3, 2, 1};
    outList = reverseKGroup(inpList, 4);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4});
    outExpected = {1, 2, 3, 4};
    outList = reverseKGroup(inpList, 5);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {2, 1, 4, 3, 6, 5, 7};
    outList = reverseKGroup(inpList, 2);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {3, 2, 1, 6, 5, 4, 7};
    outList = reverseKGroup(inpList, 3);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);

    inpList = buildList({1, 2, 3, 4, 5, 6, 7});
    outExpected = {4, 3, 2, 1, 5, 6, 7};
    outList = reverseKGroup(inpList, 4);
    outComputed = getListEles(outList);
    assert(outExpected == outComputed);
}

Node* reverseKGroup(Node* head, int k) {
    // TODO implement iterative algorithm with O(n) complexity
    // refer to this http://buttercola.blogspot.com/2014/09/leetcode-reverse-nodes-in-k-group.html
}
