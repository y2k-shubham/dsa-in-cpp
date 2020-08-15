// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
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

class Solution {
   private:
    map<int, int> buildIndMap(vector<int>& vec) {
        map<int, int> indMap;

        for (int i = 0; i < vec.size(); i++) {
            indMap[vec[i]] = i;
        }

        return indMap;
    }

    void inOrderRec(TreeNode* root) {
        if (root != nullptr) {
            inOrderRec(root->left);
            printf("%d ", root->val);
            inOrderRec(root->right);
        }
    }

    // this is useless, since binary search can't be use on inOrder traversal (since it is NOT a BST)
    int binSearch(vector<int>& vec, int ele, int lo, int hi) {
        if (vec.empty() || (lo > hi)) {
            return -1;
        } else {
            int midInd = (lo + hi) / 2;
            int midEle = vec[midInd];
            if (ele < midEle) {
                return binSearch(vec, ele, lo, midInd - 1);
            } else if (ele == midEle) {
                return midInd;
            } else {
                return binSearch(vec, ele, midInd + 1, hi);
            }
        }
    }

    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    TreeNode* buildTreeRec(vector<int>& preorder, int preLo, int preHi, vector<int>& inorder, int inLo, int inHi, map<int, int>& inIndMap) {
        int size = preHi - preLo + 1;

        // printf("\n-------\n");
        // if (size > 0) {
        //     if (size != (inHi - inLo + 1)) {
        //         printf("preLo=%d, preHi=%d\tinLo=%d, inHi=%d\n", preLo, preHi, inLo, inHi);
        //         printf("inconsistent state: sizes of in & pre vecs differ\n");
        //         return NULL;
        //     } else {
        //         printf("preLo=pre[%d]=%d, preHi=pre[%d]=%d\tinLo=in[%d]=%d, inHi=in[%d]=%d\n", preLo, preorder[preLo], preHi, preorder[preHi], inLo, inorder[inLo], inHi, inorder[inHi]);
        //     }
        // } else {
        //     printf("preLo=%d, preHi=%d\tinLo=%d, inHi=%d\n", preLo, preHi, inLo, inHi);
        // }

        if (size <= 0) {
            // printf("size is zero or negative, returning NULL\n");
            return NULL;
        } else if (size == 1) {
            return createNode(preorder[preLo]);
        } else {
            int rootVal = preorder[preLo];
            TreeNode* newNode = createNode(rootVal);

            int rootInInd = inIndMap[rootVal];
            // printf("rootVal = %d, rootInInd = %d\n", rootVal, rootInInd);

            int numNodesInLTree = rootInInd - inLo;
            int numNodesInRTree = inHi - rootInInd;

            newNode->left = buildTreeRec(preorder, preLo + 1, preLo + numNodesInLTree, inorder, inLo, rootInInd - 1, inIndMap);
            newNode->right = buildTreeRec(preorder, preLo + numNodesInLTree + 1, preHi, inorder, rootInInd + 1, inHi, inIndMap);

            return newNode;
        }
    }

   public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int len = preorder.size();
        map<int, int> inIndMap = buildIndMap(inorder);
        return buildTreeRec(preorder, 0, len - 1, inorder, 0, len - 1, inIndMap);
    }

    void lvlOrder(TreeNode* root) {
        printf("\nLvlOrder traversal is:-\n");

        if (root != NULL) {
            queue<TreeNode*> que;

            que.push(root);
            while (!que.empty()) {
                for (int i = 1; i <= que.size(); i++) {
                    TreeNode* node = que.front();
                    que.pop();

                    printf("%d ", node->val);
                    if (node->left != nullptr) {
                        que.push(node->left);
                    }
                    if (node->right != nullptr) {
                        que.push(node->right);
                    }
                }
                cout << endl;
            }
        }
    }

    void inOrder(TreeNode* root) {
        printf("\nInOrder traversal is:-\n");
        inOrderRec(root);
        cout << endl;
    }

    friend class SolutionTest;
};

class SolutionTest {
   public:
    void testBinSearch() {
        Solution soln = Solution();
        vector<int> vec;

        vec = {};
        assert(soln.binSearch(vec, 5, 0, ((int)vec.size() - 1)) == -1);

        vec = {1};
        assert(soln.binSearch(vec, 5, 0, ((int)vec.size() - 1)) == -1);

        vec = {5};
        assert(soln.binSearch(vec, 5, 0, ((int)vec.size() - 1)) == 0);

        vec = {3, 5};
        assert(soln.binSearch(vec, 5, 0, ((int)vec.size() - 1)) == 1);

        vec = {5, 6};
        assert(soln.binSearch(vec, 4, 0, ((int)vec.size() - 1)) == -1);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 4, 0, ((int)vec.size() - 1)) == -1);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 5, 0, ((int)vec.size() - 1)) == 0);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 8, 0, ((int)vec.size() - 1)) == -1);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 9, 0, ((int)vec.size() - 1)) == 1);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 10, 0, ((int)vec.size() - 1)) == -1);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 11, 0, ((int)vec.size() - 1)) == 2);

        vec = {5, 9, 11};
        assert(soln.binSearch(vec, 13, 0, ((int)vec.size() - 1)) == -1);

        // vec = {9, 3, 15, 20, 7};
        // assert(soln.binSearch(vec, 3, 0, ((int) vec.size() - 1)) == 1);
    }
};

int main() {
    vector<int> inOrder;
    vector<int> preOrder;
    TreeNode* root;
    Solution soln = Solution();
    SolutionTest solnTest = SolutionTest();

    solnTest.testBinSearch();

    preOrder = {3, 9, 20, 15, 7};
    inOrder = {9, 3, 15, 20, 7};
    root = soln.buildTree(preOrder, inOrder);
    soln.lvlOrder(root);
    soln.inOrder(root);

    return 0;
}
