// LeetCode-894: https://leetcode.com/problems/all-possible-full-binary-trees/
// NeetCode: https://www.youtube.com/watch?v=nZtrZPTTCAo

#include <cstdio>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
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

class Solution {
   private:
    bool debug = false;

    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->val = val;
        return newNode;
    }

    void showTreeLvlOrder(TreeNode* root) {
        cout << endl;
        if (root == nullptr) {
            printf("null\n");
        }

        queue<pair<TreeNode*, int>> mQue;
        mQue.push({root, 1});

        int lvlNo = 1;
        while (!mQue.empty()) {
            int lvlSize = mQue.size();

            for (int i = 1; i <= lvlSize; i++) {
                pair<TreeNode*, int> item = mQue.front();
                mQue.pop();

                if (item.first == nullptr) {
                    printf("- ");
                } else {
                    printf("%d ", item.second);
                    
                    if (root->left != nullptr) {
                        mQue.push({root->left, item.second * 2});
                    }

                    if (root->right != nullptr) {
                        mQue.push({root->right, item.second * 2 + 1});
                    }
                }

                // printf("lvlNo=%d, lvlSize=%d, i=%d\n", lvlNo, lvlSize, i);
            }

            // printf("\nlvlNo=%d over\n", lvlNo);
            cout << endl;

            lvlNo++;
        }
    }

    list<TreeNode*> buildFBTsRec(
        int n,
        unordered_map<int, list<TreeNode*>>& memoMap) {
        if (memoMap.find(n) != memoMap.end()) {
            if (debug) {
                printf("returning memoized result of n=%d, which has %d trees\n", n, (int)memoMap[n].size());
            }
            return memoMap[n];
        }

        list<TreeNode*> mList;
        if ((n % 2) == 0) {
            // full binary tree having even no of nodes is not possible
            mList = {};
        } else if (n == 1) {
            mList = {createNode(0)};
        } else {
            // we'll ensure that each subtree (that we try to build) always has odd no nodes
            // odd + odd + 1 (root itself) = odd nodes overall
            for (int i = 1; i < n; i += 2) {
                if (debug) {
                    printf("invoking leftTrees = buildFBTRec(%d, memoMap)\n", i);
                    printf("invoking rightTrees = buildFBTRec(%d, memoMap)\n", n - i - 1);
                }
                list<TreeNode*> leftTrees = buildFBTsRec(i, memoMap);
                list<TreeNode*> rightTrees = buildFBTsRec(n - i - 1, memoMap);

                if (debug) {
                    printf("leftTrees are:-\n");
                    for (list<TreeNode*>::iterator it1 = leftTrees.begin(); it1 != leftTrees.end(); it1++) {
                        showTreeLvlOrder(*it1);
                    }
                    cout << endl;

                    printf("rightTrees are:-\n");
                    for (list<TreeNode*>::iterator it2 = rightTrees.begin(); it2 != rightTrees.end(); it2++) {
                        showTreeLvlOrder(*it2);
                    }
                    cout << endl;
                }

                for (list<TreeNode*>::iterator it1 = leftTrees.begin(); it1 != leftTrees.end(); it1++) {
                    TreeNode* leftNode = *it1;
                    for (list<TreeNode*>::iterator it2 = rightTrees.begin(); it2 != rightTrees.end(); it2++) {
                        TreeNode* rightNode = *it2;

                        TreeNode* root = createNode(0);
                        if (debug) {
                            // printf("\nnewly created root\n");
                            // showTreeLvlOrder(root);
                        }

                        root->left = leftNode;
                        root->right = rightNode;
                        if (debug) {
                            printf("linking setting root->left = following tree\n");
                            showTreeLvlOrder(leftNode);

                            printf("linking setting root->right = following tree\n");
                            showTreeLvlOrder(rightNode);
                        }

                        mList.push_back(root);
                        if (debug) {
                            printf("\npushing back following root with %d nodes\n", n);
                            showTreeLvlOrder(root);
                        }
                    }
                }
            }
        }

        memoMap[n] = mList;
        if (debug && !mList.empty()) {
            printf("\nthe %d complete binary trees having %d nodes are:-\n", (int)mList.size(), n);
            for (list<TreeNode*>::iterator it = mList.begin(); it != mList.end(); it++) {
                // showTreeLvlOrder(*it);
                printf("\n- - - - - - - \n");
            }
        }

        return mList;
    }

   public:
    vector<TreeNode*> allPossibleFBT(int N) {
        if (debug) {
            printf("\n------------\n------------\n\n");
        }
        unordered_map<int, list<TreeNode*>> memoMap;
        list<TreeNode*> mList = buildFBTsRec(N, memoMap);

        vector<TreeNode*> mVec(mList.begin(), mList.end());
        return mVec;
    }

    void setDebug(bool debug) {
        this->debug = debug;
    }
};

int main() {
    Solution soln = Solution();

    soln.setDebug(true);
    soln.allPossibleFBT(0);
    soln.allPossibleFBT(1);
    soln.allPossibleFBT(2);
    soln.allPossibleFBT(3);
    soln.setDebug(false);

    return 0;
}
