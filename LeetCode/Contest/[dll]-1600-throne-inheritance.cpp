// weekly contest 208: https://leetcode.com/contest/weekly-contest-208/problems/crawler-log-folder/
// incomplete: test cases failing

// passing test-cases
/*
["ThroneInheritance"]
[["king"]]

["ThroneInheritance","getInheritanceOrder"]
[["king"],[null]]

["ThroneInheritance","birth"]
[["king"],["king","andy"]]

["ThroneInheritance","birth","getInheritanceOrder"]
[["king"],["king","andy"],[null]]

["ThroneInheritance","birth","birth","birth","birth","birth","birth","getInheritanceOrder","death","getInheritanceOrder"]
[["king"],["king","andy"],["king","bob"],["king","catherine"],["andy","matthew"],["bob","alex"],["bob","asha"],[null],["bob"],[null]]

["ThroneInheritance","birth","birth","birth","birth","birth","birth","getInheritanceOrder","death","getInheritanceOrder"]
[["king"],["king","andy"],["king","bob"],["king","catherine"],["andy","matthew"],["bob","alex"],["bob","asha"],[null],["bob"],[null]]
*/

// failing test case
/*
["ThroneInheritance","birth","getInheritanceOrder","death","birth","getInheritanceOrder","birth","birth","getInheritanceOrder"]
[["king"],["king","clyde"],[null],["clyde"],["king","shannon"],[null],["king","scott"],["scott","keith"],[null]]

expected answer
[null,null,["king","clyde"],null,null,["king","shannon"],null,null,["king","shannon","scott","keith"]]
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

class DLLNode {
   public:
    string name;
    DLLNode* left;
    DLLNode* right;

    DLLNode(string name) {
        this->name = name;
        this->left = NULL;
        this->right = NULL;
    }
};

class ThroneInheritance {
   private:
    map<string, vector<string> > parentChildrenMap;
    map<string, string> childParentMap;
    map<string, DLLNode*> personNodeMap;
    DLLNode* dll;

    void insertNode(DLLNode* predecessorNode, DLLNode* node) {
        DLLNode* successorNode = predecessorNode->right;

        predecessorNode->right = node;
        node->left = predecessorNode;

        if (successorNode != NULL) {
            node->right = successorNode;
            successorNode->left = node;
        }
    }

    void deleteNode(DLLNode* node) {
        if (this->dll == NULL) {
            return;
        }

        DLLNode* predecessorNode = node->left;
        DLLNode* successorNode = node->right;

        if (predecessorNode == NULL && successorNode == NULL) {
            this->dll = NULL;
        } else if (predecessorNode == NULL) {
            this->dll = successorNode;
            successorNode->left = NULL;
        } else if (successorNode == NULL) {
            predecessorNode->right = NULL;
        } else {
            predecessorNode->right = successorNode;
            successorNode->left = predecessorNode;
        }
    }

   public:
    ThroneInheritance(string kingName) {
        // ref: https://stackoverflow.com/q/11247387/3679900
        DLLNode* kingNode = new DLLNode(kingName);
        this->personNodeMap[kingName] = kingNode;
        this->dll = kingNode;
    }

    void birth(string parentName, string childName) {
        string predecessorName;
        if (this->parentChildrenMap[parentName].empty()) {
            predecessorName = parentName;
        } else {
            predecessorName = *this->parentChildrenMap[parentName].rbegin();
        }

        DLLNode* predecessorNode = this->personNodeMap[predecessorName];

        this->parentChildrenMap[parentName].push_back(childName);
        this->childParentMap[childName] = parentName;

        DLLNode* childNode = new DLLNode(childName);
        this->personNodeMap[childName] = childNode;

        insertNode(predecessorNode, childNode);
    }

    void death(string name) {
        DLLNode* node = this->personNodeMap[name];
        deleteNode(node);
    }

    vector<string> getInheritanceOrder() {
        vector<string> inheritOrder;
        for (DLLNode* node = this->dll; node != NULL; node = node->right) {
            inheritOrder.push_back((*node).name);
        }

        return inheritOrder;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */