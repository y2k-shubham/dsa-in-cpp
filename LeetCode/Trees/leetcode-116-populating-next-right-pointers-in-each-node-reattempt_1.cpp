#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
   private:
    // LC-submission: speed: 75 %tile
    void inOrderConnect(Node* root, map<int, Node*>& lvlNodeMap, int lvl) {
        if (root != nullptr) {
            inOrderConnect(root->left, lvlNodeMap, lvl + 1);

            root->next = NULL;
            if (lvlNodeMap.find(lvl) != lvlNodeMap.end()) {
                Node* prevLvlNode = lvlNodeMap[lvl];
                prevLvlNode->next = root;
            }
            lvlNodeMap[lvl] = root;

            inOrderConnect(root->right, lvlNodeMap, lvl + 1);
        }
    }

   public:
    Node* connect(Node* root) {
        map<int, Node*> lvlNodeMap;
        inOrderConnect(root, lvlNodeMap, 0);
        return root;
    }
};
