// GFG: http://www.geeksforgeeks.org/find-closest-element-binary-search-tree/
// Won't compile at: http://www.practice.geeksforgeeks.org/problem-page.php?pid=700423
// GFG: https://practice.geeksforgeeks.org/problems/find-the-closest-element-in-bst
// LC: https://leetcode.com/problems/closest-binary-search-tree-value/

/*
3

9
9 4 17 3 6 22 5 7 20
4

9
9 4 17 3 6 22 5 7 20
18

9
9 4 17 3 6 22 5 7 20
12
*/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>

struct node {
    int val;
    struct node *lC;
    struct node *rC;
};

using namespace std;

node *createNode(int);
node *insertNode(node *, node *);
void inOrder(node *);
node *input();
int findMinDiff1(node *, int);

int main() {
    int T;

    cin >> T;
    while (T-- > 0) {
        node *root;
        int K;

        root = input();
        cin >> K;

        int minDiff = findMinDiff1(root, K);
        printf("%d\n", (K - minDiff));
    }

    return 0;
}

node *input() {
    int ele;
    int n;
    node *root;

    root = NULL;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> ele;
        node *newNode = createNode(ele);
        root = insertNode(root, newNode);
    }

    return root;
}

node *createNode(int val) {
    node *newNode = new node;
    newNode->val = val;
    newNode->lC = NULL;
    newNode->rC = NULL;
    return newNode;
}

node *insertNode(node *root, node *newNode) {
    if (root == NULL) {
        return newNode;
    } else {
        if (newNode->val < root->val) {
            root->lC = insertNode(root->lC, newNode);
        } else if (newNode->val > root->val) {
            root->rC = insertNode(root->rC, newNode);
        } else {
            cout << "Can't insert duplicate element\n";
        }
        return root;
    }
}

void inOrder(node *root) {
    if (root != NULL) {
        inOrder(root->lC);
        cout << root->val << " ";
        inOrder(root->rC);
    }
}

int findMinDiff1(node *root, int K) {
    if (root == NULL) {
        return INT_MAX;
    } else {
        int diff = K - (root->val);

        if (diff < 0) {
            int lDiff = findMinDiff1(root->lC, K);
            if (abs(diff) < abs(lDiff)) {
                return diff;
            } else {
                return lDiff;
            }
        } else if (diff > 0) {
            int rDiff = findMinDiff1(root->rC, K);
            if (abs(diff) < abs(rDiff)) {
                return diff;
            } else {
                return rDiff;
            }
        } else {
            return 0;
        }
    }
}

int findMminDiff2(node *root, int K) {
    if (root == NULL) {
        return INT_MAX;
    } else if (root->val == K) {
        return 0;
    } else {
        int crrDiff = abs(root->val - K);

        if (K < root->val) {
            return min(crrDiff, findMminDiff2(root->lC, K));
        } else {
            return min(crrDiff, findMminDiff2(root->rC, K));
        }
    }
}
