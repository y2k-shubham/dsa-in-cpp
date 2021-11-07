// LeetCode-2049: https://leetcode.com/problems/count-nodes-with-the-highest-score/

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
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

TreeNode* createNode(int val) {
    TreeNode* newNode = new TreeNode;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->val = val;
    return newNode;
}

class Solution {
   private:
    vector<TreeNode*> createNodes(int n) {
        vector<TreeNode*> nodes(n);
        for (int i = 0; i < n; i++) {
            nodes[i] = createNode(i);
        }

        return nodes;
    }

    // it builds tree of a (possibly, likely) different shape than expected
    // (yet we get correct answer as that is independent of that difference in shape of tree)
    TreeNode* buildTree(vector<int>& parents) {
        int len = parents.size();
        if (len == 0) {
            return nullptr;
        }

        vector<TreeNode*> nodes = createNodes(len);

        for (int i = 1; i < len; i++) {
            TreeNode* crrNode = nodes[i];
            TreeNode* parentNode = nodes[parents[i]];

            // connect child node with parent node
            // (depending on whether left child already present or not)
            if (parentNode->left == nullptr) {
                parentNode->left = crrNode;
            } else {
                parentNode->right = crrNode;
            }
        }

        return nodes[0];
    }

    long long biggestItem(vector<long long>& vec) {
        // https://en.cppreference.com/w/cpp/algorithm/max_element
        return *max_element(vec.begin(), vec.end());
    }

    int countItems(vector<long long>& vec, long long item) {
        // https://www.cplusplus.com/reference/algorithm/count/
        return count(vec.begin(), vec.end(), item);
    }

   public:
    friend class SolutionTest;

    int findScores(TreeNode* root, int numNodesTotal, vector<long long>& scores) {
        if (root == nullptr) {
            return 0;
        } else if (numNodesTotal <= 0) {
            return 0;
        } else if (numNodesTotal == 1) {
            scores[0] = 0;
            return 0;
        } else {
            int numNodesLeft = findScores(root->left, numNodesTotal, scores);
            int numNodesRight = findScores(root->right, numNodesTotal, scores);
            int numNodesCrrSubtree = numNodesLeft + numNodesRight + 1;

            long long crrNodeScore = ((long long)max(numNodesLeft, 1)) * max(numNodesRight, 1) * max(numNodesTotal - numNodesCrrSubtree, 1);
            scores[root->val] = crrNodeScore;

            return numNodesCrrSubtree;
        }
    }

    int countHighestScoreNodes(vector<int>& parents) {
        int numNodes = parents.size();
        if (numNodes == 0) {
            return 0;
        }
        if (numNodes == 1) {
            return 1;
        }

        TreeNode* root = buildTree(parents);

        vector<long long> scores(numNodes, 0);
        findScores(root, numNodes, scores);

        long long highestScore = biggestItem(scores);
        int highestScoreFreq = countItems(scores, highestScore);

        return highestScoreFreq;
    }
};

class SolutionTest {
   private:
    void buildInOrder(TreeNode* root, vector<int>& inOrder) {
        if (root != nullptr) {
            buildInOrder(root->left, inOrder);
            inOrder.push_back(root->val);
            buildInOrder(root->right, inOrder);
        }
    }

    void showVec(vector<int>& vec) {
        printf("vec is:-\n");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d ", vec[i]);
        }
        cout << endl;
    }

   public:
    void testBuildTree() {
        Solution soln = Solution();
        vector<int> inParents;
        TreeNode* outRootComputed;
        vector<int> outInOrderExpected;
        vector<int> outInOrderComputed;

        inParents = {};
        outInOrderExpected = {};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);

        inParents = {-1};
        outInOrderExpected = {0};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);

        inParents = {-1, 0, 0, 1, 1, 2, 4, 5, 5, 6, 7, 7, 10};
        outInOrderExpected = {3, 1, 9, 6, 4, 0, 12, 10, 7, 11, 5, 8, 2};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        // showVec(outInOrderExpected);
        // showVec(outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
    }

    void testFindScores() {
        Solution soln = Solution();
        vector<int> inParents;
        TreeNode* outRootComputed;
        vector<int> outInOrderExpected;
        vector<int> outInOrderComputed;
        vector<long long> outScoresExpected;
        vector<long long> outScoresComputed;

        inParents = {};
        outInOrderExpected = {};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
        outScoresExpected = {};
        outScoresComputed.clear();
        outScoresComputed.resize(inParents.size(), 0);
        soln.findScores(outRootComputed, inParents.size(), outScoresComputed);
        assert(outScoresExpected == outScoresComputed);

        inParents = {-1};
        outInOrderExpected = {0};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
        outScoresExpected = {0};
        outScoresComputed.clear();
        outScoresComputed.resize(inParents.size(), 0);
        soln.findScores(outRootComputed, inParents.size(), outScoresComputed);
        // showVec(outScoresComputed);
        assert(outScoresExpected == outScoresComputed);

        inParents = {-1, 0, 0, 1, 1, 2, 4, 5, 5, 6, 7, 7, 10};
        outInOrderExpected = {3, 1, 9, 6, 4, 0, 12, 10, 7, 11, 5, 8, 2};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        // showVec(outInOrderExpected);
        // showVec(outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
        outScoresExpected = {35, 24, 36, 12, 20, 28, 11, 18, 12, 12, 11, 12, 12};
        outScoresComputed.clear();
        outScoresComputed.resize(inParents.size(), 0);
        soln.findScores(outRootComputed, inParents.size(), outScoresComputed);
        // showVec(outScoresComputed);
        assert(outScoresExpected == outScoresComputed);

        inParents = {-1, 2, 0, 2, 0};
        outInOrderExpected = {1, 2, 3, 0, 4};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        // showVec(outInOrderExpected);
        // showVec(outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
        outScoresExpected = {3, 4, 2, 4, 4};
        outScoresComputed.clear();
        outScoresComputed.resize(inParents.size(), 0);
        soln.findScores(outRootComputed, inParents.size(), outScoresComputed);
        // showVec(outScoresComputed);
        assert(outScoresExpected == outScoresComputed);

        inParents = {-1, 2, 0};
        outInOrderExpected = {1, 2, 0};
        outRootComputed = soln.buildTree(inParents);
        outInOrderComputed.clear();
        buildInOrder(outRootComputed, outInOrderComputed);
        // showVec(outInOrderExpected);
        // showVec(outInOrderComputed);
        assert(outInOrderExpected == outInOrderComputed);
        outScoresExpected = {2, 2, 1};
        outScoresComputed.clear();
        outScoresComputed.resize(inParents.size(), 0);
        soln.findScores(outRootComputed, inParents.size(), outScoresComputed);
        // showVec(outScoresComputed);
        assert(outScoresExpected == outScoresComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildTree();
    solnTest.testFindScores();

    return 0;
}
