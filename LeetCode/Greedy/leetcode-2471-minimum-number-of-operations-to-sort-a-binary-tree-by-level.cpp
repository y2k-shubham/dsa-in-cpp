// LeetCode-2471: https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level
// minimum-swaps required to sort an array approach referenced from GeeksForGeeks: https://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/

#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class SortNumSwapsDeterminer {
private:
    inline void swapValues(vector <int>& vec, int idx1, int idx2, unordered_map <int, int>& valueToIndexMap) {
        int temp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = temp;

        valueToIndexMap[vec[idx1]] = idx1;
        valueToIndexMap[vec[idx2]] = idx2;
    }

    inline unordered_map <int, int> buildValueIndexMap(vector <int>& vec) {
        unordered_map <int, int> valueToIndexMap;
        for (int i = 0; i < vec.size(); i++) {
            valueToIndexMap[vec[i]] = i;
        }

        return valueToIndexMap;
    }

public:
    inline int calculateNumSwapsToSort(vector <int>& vecUnSorted) {
        if (vecUnSorted.size() <= 1) {
            return 0;
        }

        vector <int> vecSorted = vecUnSorted;
        sort(vecSorted.begin(), vecSorted.end());

        unordered_map <int, int> valueToIndexMap = buildValueIndexMap(vecUnSorted);

        int numSwaps = 0;
        for (int i = 0; i < vecUnSorted.size(); i++) {
            if (vecUnSorted[i] == vecSorted[i]) {
                continue;
            }

            numSwaps++;

            int idxToSwapWith = valueToIndexMap[vecSorted[i]];
            swapValues(vecUnSorted, i, idxToSwapWith, valueToIndexMap);
        }

        return numSwaps;
    }
};

class Solution {
private:
    inline bool isEmpty(TreeNode* root) {
        return (root == nullptr);
    }

    inline bool isLeaf(TreeNode* root) {
        return (root->left == nullptr && root->right == nullptr);
    }

    list <vector <int>> buildLvlOrder(TreeNode* root) {
        if (isEmpty(root)) {
            return {};
        }
        if (isLeaf(root)) {
            return {{root->val}};
        }

        list <vector <int>> lvlOrder;
        queue <TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            int numNodesInCrrLvl = que.size();
            vector <int> nodesInCrrLvl(numNodesInCrrLvl);

            for (int i = 0; i < numNodesInCrrLvl; i++) {
                TreeNode* node = que.front();
                que.pop();

                nodesInCrrLvl[i] = node->val;

                if (!isEmpty(node->left)) {
                    que.push(node->left);
                }
                if (!isEmpty(node->right)) {
                    que.push(node->right);
                }
            }

            lvlOrder.push_back(nodesInCrrLvl);
        }

        return lvlOrder;
    }

public:
    friend class SolutionTest;

    int minimumOperations(TreeNode* root) {
        SortNumSwapsDeterminer swapsDeterminer = SortNumSwapsDeterminer();
        list <vector <int>> lvlOrder = buildLvlOrder(root);
        if (lvlOrder.size() <= 1) {
            return 0;
        }

        int numSwaps = 0;
        for (auto& vec : lvlOrder) {
            numSwaps += swapsDeterminer.calculateNumSwapsToSort(vec);
        }

        return numSwaps;
    }
};

class SortNumSwapsDeterminerTest {
public:
    void testCalculateNumSwapsToSort() {
        SortNumSwapsDeterminer swapsDeterminer = SortNumSwapsDeterminer();
        vector <int> vecIn;
        int outExpected, outComputed;

        vecIn = {};
        outExpected = 0;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);

        vecIn = {715};
        outExpected = 0;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);

        vecIn = {19, 2, 41, 6};
        outExpected = 3;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 8, 5, 4};
        outExpected = 1;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);

        vecIn = {10, 19, 6, 3, 5};
        outExpected = 2;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 3, 4, 5, 6};
        outExpected = 0;
        outComputed = swapsDeterminer.calculateNumSwapsToSort(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SortNumSwapsDeterminerTest swapsDeterminerTest = SortNumSwapsDeterminerTest();

    swapsDeterminerTest.testCalculateNumSwapsToSort();

    return 0;
}
