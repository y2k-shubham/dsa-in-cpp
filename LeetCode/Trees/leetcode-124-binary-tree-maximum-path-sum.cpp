// LeetCode-124: https://leetcode.com/problems/binary-tree-maximum-path-sum/
// https://www.interviewbit.com/problems/max-sum-path-in-binary-tree/
// https://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
// condensed soln: https://www.youtube.com/watch?v=mOdetMWwtoI
// Hard problem

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

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
void inOrderTravRec(TreeNode*);
void lvlOrderTrav(TreeNode* root);
TreeNode* createNode(int);
TreeNode* getPath(int);
TreeNode* insert(TreeNode*, TreeNode*, TreeNode*);
TreeNode* buildTree(vector<int> lvlOrder);
void testMaxPathSumRec();
pair <int, int> maxPathSumRec(TreeNode* root, bool debug);
int maxPathSumRec(TreeNode* root, int* maxSum, bool debug);
int maxPathSum(TreeNode* root);

int main() {
    testMaxPathSumRec();

    return 0;
}

void testMaxPathSumRec() {
    vector <int> lvlOrder;
    TreeNode* root;

    lvlOrder = {
        1,
        2, 3
    };
    root = buildTree(lvlOrder);
    // inOrderTrav(root);
    // lvlOrderTrav(root);
    assert(maxPathSumRec(root, false).second == 6);

    lvlOrder = {
        -10,
        9, 20,
        INT_MIN, INT_MIN, 15, 7
    };
    root = buildTree(lvlOrder);
    // inOrderTrav(root);
    // lvlOrderTrav(root);
    assert(maxPathSumRec(root, false).second == 42);

    lvlOrder = {
        -3
    };
    root = buildTree(lvlOrder);
    // inOrderTrav(root);
    // lvlOrderTrav(root);
    // cout << maxPathSumRec(root, true).second << endl; 
    assert(maxPathSumRec(root, true).second == -3);

    lvlOrder = {
        -10,
        -20, -30
    };
    root = buildTree(lvlOrder);
    // inOrderTrav(root);
    // lvlOrderTrav(root);
    // cout << maxPathSumRec(root, true).second << endl; 
    assert(maxPathSumRec(root, true).second == -10);
}

// poor performance on LC: beats only 10% submissions
pair <int, int> maxPathSumRec(TreeNode* root, bool debug) {
    if (root == nullptr) {
        // this is important
        return make_pair(INT_MIN, INT_MIN);
    } else {
        pair <int, int> lRes = maxPathSumRec(root->left, debug);
        pair <int, int> rRes = maxPathSumRec(root->right, debug);

        int crrLChainSum =  max(lRes.first, 0);
        int crrRChainSum = max(rRes.first, 0);

        // max sum of continuous chain (either left or right) of nodes starting at current node
        int crrMaxContChainSum = max(crrLChainSum, crrRChainSum) + root->val;
        
        // overall max sum (either coninuous chain as above or chain bending across sublings) for subtree rooted at this node
        // (basically the final result for this node)
        int crrRootSubTreeSum = crrLChainSum + root->val + crrRChainSum;
        int crrMaxSubTreeSum = max(crrMaxContChainSum, max(crrRootSubTreeSum, max(lRes.second, rRes.second)));

        return make_pair(crrMaxContChainSum, crrMaxSubTreeSum);
    }
}

// better performance on LC: beats 45% submissions
// https://www.youtube.com/watch?v=mOdetMWwtoI
int maxPathSumRec(TreeNode* root, int* maxSum, bool debug) {
    if (root == nullptr) {
        return 0;
    } else {
        int lSum = max(maxPathSumRec(root->left, maxSum, debug), 0);
        int rSum = max(maxPathSumRec(root->right, maxSum, debug), 0);

        *maxSum = max(*maxSum, (lSum + rSum + root->val));

        int crrSum = max(lSum, rSum) + root->val;
        return crrSum;
    }
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumRec(root, &maxSum, false);
    return maxSum;
    // return maxPathSumRec(root, false).second;
}

// tree construction

void inOrderTrav(TreeNode* root) {
    printf("\nInOrder traversal is:-\n");
    inOrderTravRec(root);
    cout << endl;
}

void inOrderTravRec(TreeNode* root) {
    if (root != NULL) {
        inOrderTravRec(root->left);
        printf("%d ", root->val);
        inOrderTravRec(root->right);
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

    head = new TreeNode(val);
    val /= 2;

    while (val >= 1) {
        TreeNode* newNode = new TreeNode(val);
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
        if (ele != INT_MIN) {
            TreeNode* path = getPath(pos);
            // printf("path determined\n");
            TreeNode* newNode = new TreeNode(ele);
            // printf("newNode created\n");
            root = insert(root, path->right, newNode);
            // printf("newNode inserted\n");
        }
    }

    return root;
}
