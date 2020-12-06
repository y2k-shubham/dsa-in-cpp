// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

/*
			     1
        2                 3
	4       5         6       7
   8 9   10  11        13   14
	    20  22          27
				         55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1


        1
    2       3
  4   5       7
    10      14
             29  

1 1
2 2 3 3
4 4 5 5 7 7
10 10 14 14
29 29
-1 -1
*/

#include <cstdio>
#include <iostream>
// for ostringstream
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

struct node {
    int val;
    struct node *left;
    struct node *right;
    struct node *next;
};

vector<int> getPath(int);
void showVec(vector<int>, string);
node *input();
node *insertNodeByPath(node *, vector<int>, vector<int>::iterator, node *);
node *createNode(int);
void printInOrder(node *);
void printPreOrder(node *);
void printPostOrder(node *);
void printLevelOrder(node *);
void linkNextNodesQue(node *);
void linkNextNodesRec(node *);
void printLevelOrderNextPtr(node *);
node *getNextNodeForChild(node *);
void buildLevelLeftMostNodeMap(node *, int, map<int, node *> &);

int main() {
    node *root = input();

    cout << endl
         << "InOrder    traversal of tree is:-" << endl;
    printInOrder(root);

    cout << endl
         << "PreOrder   traversal of tree is:-" << endl;
    printPreOrder(root);

    cout << endl
         << "PostOrder  traversal of tree is:-" << endl;
    printPostOrder(root);

    cout << endl
         << "LevelOrder traversal of tree is:-" << endl;
    printLevelOrder(root);

    // linkNextNodesQue(root);
    linkNextNodesRec(root);
    cout << endl
         << "LevelOrder traversal of tree using next pointers is:-" << endl;
    printLevelOrderNextPtr(root);

    return 0;
}

void linkNextNodesQue(node *root) {
    queue<node *> que;
    que.push(root);
    while (!que.empty()) {
        int lvlLen = (int)que.size();
        for (int i = 1; i <= lvlLen; i++) {
            node *myNode = que.front();
            que.pop();
            // only i < lvlLen check is needed
            // because que won't be empty as long as outer loop runs
            if (i < lvlLen) {
                myNode->next = que.front();
            }

            if (myNode->left != NULL) {
                que.push(myNode->left);
            }
            if (myNode->right != NULL) {
                que.push(myNode->right);
            }
        }
    }
}

void linkNextNodesRec(node *root) {
    if (root != NULL) {
        if (root->right != NULL) {
            node *nextNode = getNextNodeForChild(root);
            root->right->next = nextNode;
            linkNextNodesRec(root->right);
        }
        if (root->left != NULL) {
            node *nextNode = (root->right != NULL) ? root->right : getNextNodeForChild(root);
            root->left->next = nextNode;
            linkNextNodesRec(root->left);
        }
    }
}

node *getNextNodeForChild(node *root) {
    node *nextNode = NULL;
    for (node *tmp = root->next; tmp != NULL; tmp = tmp->next) {
        if (tmp->left != NULL) {
            nextNode = tmp->left;
            break;
        } else if (tmp->right != NULL) {
            nextNode = tmp->right;
            break;
        }
    }
    return nextNode;
}

// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3556/
node *connect(node *root) {
    if ((root != nullptr) && ((root->left != nullptr) || (root->right != nullptr))) {
        node *tmpNode;
        for (tmpNode = root->next; ((tmpNode != nullptr) && (tmpNode->left == nullptr) && (tmpNode->right == nullptr)); tmpNode = tmpNode->next)
            ;

        node *childNext = NULL;
        if (tmpNode != nullptr) {
            if (tmpNode->left != nullptr) {
                childNext = tmpNode->left;
            } else {
                childNext = tmpNode->right;
            }
            // childNext = (node->left != nullptr) ? node->left : node->right;
        }

        if (root->right != nullptr) {
            root->right->next = childNext;
        }

        if (root->left != nullptr) {
            if (root->right != nullptr) {
                root->left->next = root->right;
            } else {
                root->left->next = childNext;
            }
        }

        connect(root->right);
        connect(root->left);
    }

    return root;
}

node *input() {
    int ele, pos;
    node *root = NULL;
    ostringstream oss;

    cout << "Enter elements of binary-tree with positions:-\n(-1 pos to terminate)" << endl;
    cin >> ele >> pos;
    do {
        if (root == NULL) {
            root = createNode(ele);
        } else {
            node *newNode = createNode(ele);
            vector<int> path = getPath(pos);
            // oss << "path(" << pos << ")";
            // showVec(path, oss.str());
            // oss.str("");
            root = insertNodeByPath(root, path, path.begin(), newNode);
        }

        cin >> ele >> pos;
    } while (pos != -1);

    return root;
}

node *insertNodeByPath(node *root, vector<int> path, vector<int>::iterator it, node *newNode) {
    // redundant: both conditions will always become true simultaneously
    // so checking either of them suffices
    if (root == NULL || it == path.end()) {
        // printf("returning newNode\n");
        return newNode;
    } else if ((*it) % 2 == 0) {
        // printf("it = %d, going left\n", *it);
        root->left = insertNodeByPath(root->left, path, ++it, newNode);
        return root;
    } else {
        // printf("it = %d, going right\n", *it);
        root->right = insertNodeByPath(root->right, path, ++it, newNode);
        return root;
    }
}

node *createNode(int ele) {
    node *newNode = new node;

    newNode->val = ele;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;

    return newNode;
}

vector<int> getPath(int pos) {
    vector<int> vec;
    do {
        vec.push_back(pos);
        pos = pos / 2;
    } while (pos > 1);

    reverse(vec.begin(), vec.end());
    if (vec[0] == 1) {
        vec.erase(vec.begin());
    }

    return vec;
}

void showVec(vector<int> vec, string name) {
    printf("%s vector is:-\n", name.c_str());
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        printf("%d\t", (*it));
    }
    cout << endl;
}

void printInOrder(node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        cout << root->val << "\t";
        printInOrder(root->right);
    }
}

void printPreOrder(node *root) {
    if (root != NULL) {
        cout << root->val << "\t";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPostOrder(node *root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        cout << root->val << "\t";
    }
}

void printLevelOrder(node *root) {
    queue<node *> que;
    que.push(root);
    while (!que.empty()) {
        int lvlLen = (int)que.size();
        for (int i = 1; i <= lvlLen; i++) {
            node *myNode = que.front();
            que.pop();
            printf("%d\t", myNode->val);

            if (myNode->left != NULL) {
                que.push(myNode->left);
            }

            if (myNode->right != NULL) {
                que.push(myNode->right);
            }
        }
        cout << endl;
    }
}

void printLevelOrderNextPtr(node *root) {
    map<int, node *> levelLeftMostNodeMap;
    buildLevelLeftMostNodeMap(root, 1, levelLeftMostNodeMap);

    for (map<int, node *>::iterator it = levelLeftMostNodeMap.begin(); it != levelLeftMostNodeMap.end(); it++) {
        node *myNode = (*it).second;
        for (node *ptr = myNode; ptr != NULL; ptr = ptr->next) {
            printf("%d\t", ptr->val);
        }
        cout << endl;
    }
}

void buildLevelLeftMostNodeMap(node *root, int level, map<int, node *> &levelLeftMostNodeMap) {
    if (root != NULL) {
        if (levelLeftMostNodeMap.find(level) == levelLeftMostNodeMap.end()) {
            levelLeftMostNodeMap[level] = root;
        }
        buildLevelLeftMostNodeMap(root->left, level + 1, levelLeftMostNodeMap);
        buildLevelLeftMostNodeMap(root->right, level + 1, levelLeftMostNodeMap);
    }
}
