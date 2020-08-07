// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// https://www.interviewbit.com/problems/zigzag-level-order-traversal-bt/
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// logic is easy to understand, but skewed to implement
// and not it doesnt work on Queue like Level Order traversal

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void inOrderTrav(TreeNode*);
void lvlOrderTrav(TreeNode* root);
void showMat(vector<vector<int>> mat);
TreeNode* createNode(int);
TreeNode* getPath(int);
TreeNode* insert(TreeNode*, TreeNode*, TreeNode*);
TreeNode* buildTree(vector<int> lvlOrder);
vector<vector<int>> zigzagLevelOrder(TreeNode* root);
void testZigzagLevelOrder();

int main() {
    testZigzagLevelOrder();
    return 0;
}

TreeNode* createNode(int val) {
    TreeNode* newNode = new TreeNode;

    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void showMat(vector<vector<int>> mat) {
    printf("\nmat[][] is:-\n");
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            printf("%d ", mat[i][j]);
        }
        cout << endl;
    }
}

void inOrderTrav(TreeNode* root) {
    if (root != NULL) {
        inOrderTrav(root->left);
        printf("%d ", root->val);
        inOrderTrav(root->right);
    }
}

void lvlOrderTrav(TreeNode* root) {
    queue<TreeNode*> que;

    printf("\nLvlOrder traversal is:-\n");
    que.push(root);
    while (!que.empty()) {
        int numNodes = que.size();
        for (int i = 1; i <= numNodes; i++) {
            TreeNode* node = que.front();
            printf("%d ", node->val);
            if (node->left != nullptr) {
                que.push(node->left);
            }
            if (node->right != nullptr) {
                que.push(node->right);
            }
            que.pop();
        }
        cout << endl;
    }
}

TreeNode* getPath(int val) {
    TreeNode* head;

    head = createNode(val);
    val /= 2;

    while (val >= 1) {
        TreeNode* newNode = createNode(val);
        newNode->right = head;
        head = newNode;

        val /= 2;
    }

    return head;
}

TreeNode* insert(TreeNode* root, TreeNode* path, TreeNode* newNode) {
    // actually root == NULL check is redundant
    if (path == NULL || root == NULL) {
        return newNode;
    } else {
        if (path->val % 2 == 1) {
            root->right = insert(root->right, path->right, newNode);
        } else {
            root->left = insert(root->left, path->right, newNode);
        }

        return root;
    }
}

TreeNode* buildTree(vector<int> lvlOrder) {
    TreeNode* root = NULL;

    for (int pos = 1; pos <= lvlOrder.size(); pos++) {
        int ele = lvlOrder[pos - 1];
        // printf("\nat pos = %d, lvl[%d] = %d\n", pos, (pos - 1), ele);
        if (ele > 0) {
            TreeNode* path = getPath(pos);
            // printf("path determined\n");
            TreeNode* newNode = createNode(ele);
            // printf("newNode created\n");
            root = insert(root, path->right, newNode);
            // printf("newNode inserted\n");
        }
    }

    return root;
}

void testZigzagLevelOrder() {
    vector<int> lvlOrder;
    TreeNode* root;
    vector<vector<int>> outExpected;
    vector<vector<int>> outComputed;

    /*
           3
       9       20
             15   7
    */
    lvlOrder = {3, 9, 20, -1, -1, 15, 7};
    root = buildTree(lvlOrder);
    outExpected = {
        {3},
        {20, 9},
        {15, 7}};
    outComputed = zigzagLevelOrder(root);
    // showMat(outComputed);
    assert(outExpected == outComputed);

    /*
    			     1
        2                  3
	4         5         6         7
8   9    10    11      13    14
	     20    22          27
				                   55

    */
    lvlOrder = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, 13, 14, -1, -1, -1, -1, -1, 20, -1, 22, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55};
    root = buildTree(lvlOrder);
    printf("\nInOrder traversal is:-\n");
    inOrderTrav(root);
    lvlOrderTrav(root);
    outExpected = {
        {1},
        {3, 2},
        {4, 5, 6, 7},
        {14, 13, 11, 10, 9, 8},
        {20, 22, 27},
        {55}};
    outComputed = zigzagLevelOrder(root);
    showMat(outComputed);
    assert(outExpected == outComputed);
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr) {
        return {};
    } else {
        vector<vector<int>> zigzagLvlOrderTrav;
        stack<TreeNode*> lStk;
        stack<TreeNode*> rStk;
        int lvlNo = 0;

        lStk.push(root);
        while (!lStk.empty() || !rStk.empty()) {
            lvlNo++;
            bool leftPush = (lvlNo % 2 == 0);

            // printf("\n---------");
            // printf("\nlvl = %d, leftPush = %s\n", lvlNo, (leftPush ? "true" : "fase"));

            int lvlSize = leftPush ? rStk.size() : lStk.size();
            vector<int> lvl(lvlSize);
            for (int i = 1; i <= lvlSize; i++) {
                TreeNode* node;
                if (leftPush) {
                    node = rStk.top();
                    rStk.pop();
                    // printf("\ni = %d, node = %d extracted from rStk\n", i, node->val);
                } else {
                    node = lStk.top();
                    lStk.pop();
                    // printf("\ni = %d, node = %d extracted from lStk\n", i, node->val);
                }

                lvl[i - 1] = node->val;
                // printf("lvl[%d] = node = %d\n", (i - 1), node->val);

                if (leftPush) {
                    if (node->right != nullptr) {
                        lStk.push(node->right);
                        // printf("right child %d pushed to lStk\n", node->right->val);
                    }
                    if (node->left != nullptr) {
                        lStk.push(node->left);
                        // printf("left child %d pushed to lStk\n", node->left->val);
                    }
                } else {
                    if (node->left != nullptr) {
                        rStk.push(node->left);
                        // printf("left child %d pushed to rStk\n", node->left->val);
                    }
                    if (node->right != nullptr) {
                        rStk.push(node->right);
                        // printf("right child %d pushed to rStk\n", node->right->val);
                    }
                }
            }

            zigzagLvlOrderTrav.push_back(lvl);
        }

        return zigzagLvlOrderTrav;
    }
}
