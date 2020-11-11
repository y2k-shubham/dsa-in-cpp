// LeetCode-662: https://leetcode.com/problems/maximum-width-of-binary-tree/
// Nick-White: https://www.youtube.com/watch?reload=9&v=sm4UdCO2868

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
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

void showLvlWidthMap(map<int, pair<unsigned long long, unsigned long long> > lvlWidthMap) {
    printf("\nlvlWidthMap is:-\n");
    for (map<int, pair<unsigned long long, unsigned long long> >::iterator i = lvlWidthMap.begin(); i != lvlWidthMap.end(); i++) {
        printf("[%d] -> (%d, %d)\n", (*i).first, (*i).second.first, (*i).second.second);
    }
}

void prepareLvlWidthMap(TreeNode* root, map<int, pair<unsigned long long, unsigned long long> >& lvlWidthMap, int lvl, unsigned long long idx) {
    if (root != nullptr) {
        prepareLvlWidthMap(root->left, lvlWidthMap, lvl + 1, idx * 2);
        if (lvlWidthMap.find(lvl) == lvlWidthMap.end()) {
            lvlWidthMap[lvl] = {idx, idx};
        } else {
            lvlWidthMap[lvl].second = idx;
        }
        prepareLvlWidthMap(root->right, lvlWidthMap, lvl + 1, idx * 2 + 1);
    }
}

// unsigned long long with pre-return cast suggested at https://leetcode.com/problems/maximum-width-of-binary-tree/discuss/921744/C%2B%2B-(Use-unsigned-long-long-for-large-inputs)
int calcWidth(map<int, pair<unsigned long long, unsigned long long> > lvlWidthMap) {
    unsigned long long maxWidth = 0;
    for (map<int, pair<unsigned long long, unsigned long long> >::iterator i = lvlWidthMap.begin(); i != lvlWidthMap.end(); i++) {
        // int crrLvl = (*i).first;
        pair<unsigned long long, unsigned long long> crrBounds = (*i).second;

        // unsigned long long crrLvlFirstIdx = (unsigned long long)pow(2, crrLvl - 1);
        // unsigned long long crrOffsetFirst = (crrBounds.first - crrLvlFirstIdx);
        // unsigned long long crrOffsetSecond = (crrBounds.second - crrLvlFirstIdx);

        // int crrWidth = ((int)(crrOffsetSecond - crrOffsetFirst + 1));
        unsigned long long crrWidth = crrBounds.second - crrBounds.first + 1;

        maxWidth = max(maxWidth, crrWidth);
    }

    return (int)maxWidth;
}

///

int widthOfBinaryTree(TreeNode* root) {
    map<int, pair<unsigned long long, unsigned long long> > lvlWidthMap;
    prepareLvlWidthMap(root, lvlWidthMap, 1, 1);

    showLvlWidthMap(lvlWidthMap);

    int maxWidth = calcWidth(lvlWidthMap);
    return maxWidth;
}

int main() {
    return 0;
}
