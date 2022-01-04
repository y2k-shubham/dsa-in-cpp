/**
 * diversions means no of times the branch changes from left (subtree) to right (subtree) or vice-versa
 * in this example
 *
 *      A
 *   B     E
 *  C D   F G
 *     H I
 *
 * in above example, no of diversions are
 * b/w H & I: 3
 * b/w C & H: 1
 * b/w E & I: 0
 * b/w D & G: 2
 * b/w B & G: 1
 *
 * while the problem can be easily solved by persisting paths from root to node,
 * the interviewer Prashant Sahdev specifically asked to improve the space complexity
 * (which would've been O(h) for the above soln; h=height of tree)
 *
 * so here we're trying to come up with clever and complex recursive fn that could
 * directly compute the answer in one shot
 */

#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   private:
    TreeNode *createNode(int val) {
        TreeNode *node = new TreeNode;

        node->left = nullptr;
        node->right = nullptr;
        node->val = val;

        return node;
    }

   public:
    friend class SolutionTest;

    pair<int, int> countDiversions(
        TreeNode *root,
        int val1,
        int val2,
        int move) {
        if (val1 == val2) {
            // both nodes are same
            return {0, 0};
        }
        if (root == nullptr) {
            // reached dead end
            return {-1, -1};
        }

        // determine result of left subtree
        int leftMoveCount = (move == -1) ? 0 : 1;
        pair<int, int> leftResult = countDiversions(root->left, val1, val2, -1);
        if (leftResult.second >= 0) {
            // if result already exists in left subtree, return it
            return leftResult;
        }
        // adjust result of left subtree to factor in diversion made at current node (root)
        leftResult.first += leftMoveCount;

        // determine result of left subtree
        int rightMoveCount = (move == 1) ? 1 : 0;
        pair<int, int> rightResult = countDiversions(root->right, val1, val2, 1);
        if (rightResult.second >= 0) {
            // if result already exists in left subtree, return it
            return rightResult;
        }
        // adjust result of right subtree to factor in diversion made at current node (root)
        rightResult.first += rightMoveCount;

        if ((root->val == val1) || (root->val == val2)) {
            // we are currently at one of the two nodes

            if (leftResult.first >= 0) {
                // other node exists in left subtree
                return {0, leftResult.first};
            }

            if (rightResult.first >= 0) {
                // other node exists in right subtree
                return {0, rightResult.first};
            }

            // both subtrees dont have the other node
            return {0, -1};
        }

        // at this point, we are certain that current node is not one of the two required vals
        // so we look at subtrees

        if ((leftResult.first >= 0) && (rightResult.first >= 0)) {
            // one node is in left subtree and the other is in right subtree
            return {0, leftResult.first + rightResult.first + 1};
        } else if (leftResult.first >= 0) {
            // only left subtree contains one of the two vals
            return leftResult;
        } else if (rightResult.first >= 0) {
            // only right subtree contains one of the two vals
            return rightResult;
        } else {
            // no subtree contains either of the two vals
            return {-1, -1};
        }
    }
};

class SolutionTest {
   public:
    void testCountDiversions() {
        Solution soln = Solution();
        int inVal1, inVal2;
        int outExpected;
        pair<int, int> outComputed;

        TreeNode *root = soln.createNode(0);           // A
        root->left = soln.createNode(1);               // B
        root->left->left = soln.createNode(2);         // C
        root->left->right = soln.createNode(3);        // D
        root->right = soln.createNode(4);              // E
        root->right->left = soln.createNode(5);        // F
        root->right->right = soln.createNode(6);       // G
        root->left->left->right = soln.createNode(7);  // H
        root->right->left->left = soln.createNode(8);  // I

        inVal1 = 7;  // H
        inVal2 = 8;  // I
        outExpected = 3;
        outComputed = soln.countDiversions(root, inVal1, inVal2, 0);
        printf("(%d, %d)\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed.second);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCountDiversions();

    return 0;
}
