// LeetCode-366: https://leetcode.com/problems/find-leaves-of-binary-tree/
// Premium
// Companies: [Google][LinkedIn][Oracle][Amazon][Salesforce][Flipkart]

#include <vector>
#include <unordered_map>

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
    void showMap(unordered_map<int, vector<int>>& distFromFurthestLeafMap, int maxDist) {
        for (int i = 0; i <= maxDist; i++) {
            printf("[%d] -> ", i);

            vector <int> nodes = distFromFurthestLeafMap[i];
            for (auto jVal : nodes) {
                printf("%d ", jVal);
            }

            printf("\n");
        }
    }

    int populateDistFromFurthestLeafMap(TreeNode* root, unordered_map<int, vector<int>>& distFromFurthestLeafMap) {
        if (root == nullptr) {
            return -1;
        }

        bool hasLChild = root->left != nullptr;
        bool hasRChild = root->right != nullptr;
        bool isLeaf = !hasLChild && !hasRChild;

        if (isLeaf) {
            distFromFurthestLeafMap[0].push_back(root->val);
            return 0;
        }

        int lRes = hasLChild ? populateDistFromFurthestLeafMap(root->left, distFromFurthestLeafMap) : 0;
        int rRes = hasRChild ? populateDistFromFurthestLeafMap(root->right, distFromFurthestLeafMap) : 0;

        int distFromFurthestLeaf = max(lRes, rRes) + 1;
        distFromFurthestLeafMap[distFromFurthestLeaf].push_back(root->val);

        return distFromFurthestLeaf + 1;
    }

    vector <vector<int>> convertToVec(unordered_map<int, vector<int>>& distFromFurthestLeafMap, int maxDist) {
        vector <vector <int> > distFromFurthestLeafVec;

        for (int i = 0, j = 0; i <= maxDist; i++) {
            if ((distFromFurthestLeafMap.find(i) != distFromFurthestLeafMap.end()) && !distFromFurthestLeafMap[i].empty()) {
                distFromFurthestLeafVec.push_back(distFromFurthestLeafMap[i]);
            }
        }

        return distFromFurthestLeafVec;
    }

public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        unordered_map <int, vector<int>> distFromFurthestLeafMap;
        int maxDist = populateDistFromFurthestLeafMap(root, distFromFurthestLeafMap);
        // showMap(distFromFurthestLeafMap, maxDist);

        return convertToVec(distFromFurthestLeafMap, maxDist);
    }
};
