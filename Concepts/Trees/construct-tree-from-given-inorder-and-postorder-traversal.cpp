// https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/

/*
2 1 3 -1
2 3 1 -1

  1
2   3

4 8 2 5 1 6 3 7 -1
8 4 5 2 6 7 3 1 -1

          1
       /     \
     2        3
   /    \   /   \
  4     5   6    7
    \
      8
*/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

vector<int> readVec(const char*);
map<int, int> makeIndMap(vector<int>);
Node* createNode(int);
Node* createTree(map<int, int>, vector<int>, int, int, vector<int>, int, int);
void showInOrder(Node*);
void showPreOrder(Node*);
void showPostOrder(Node*);
void showVec(vector<int>, const char*, bool);
void showMap(map<int, int>, const char*, bool);
void showVecState(vector<int>, const char*, int, int);
void showCrrState(vector<int>, int, int, vector<int>, int, int);

int main() {
    vector<int> inOrder = readVec("inOrder ");
    vector<int> postOrder = readVec("postOrder");

    showVec(inOrder, "inOrder", true);
    showVec(postOrder, "postOrder", true);

    map<int, int> inIndMap = makeIndMap(inOrder);
    showMap(inIndMap, "inIndMap", true);

    Node* root = createTree(inIndMap, inOrder, 0, inOrder.size() - 1, postOrder, 0, postOrder.size() - 1);

    cout << endl
         << "InOrder  of constructed tree is ";
    showInOrder(root);

    cout << endl
         << "PreOrder  of constructed tree is ";
    showPreOrder(root);

    cout << endl
         << "PostOrder  of constructed tree is ";
    showPostOrder(root);
    cout << endl;

    return 0;
}

Node* createTree(map<int, int> inIndMap, vector<int> inOrder, int inLo, int inHi, vector<int> postOrder, int postLo, int postHi) {
    // printf("inLo=%d, inHi=%d\tpostLo=%d, postHi=%d\n", inLo, inHi, postLo, postHi);
    // showCrrState(inOrder, inLo, inHi, postOrder, postLo, postHi);

    int inRangeSize = (inHi - inLo + 1);
    int postRangeSize = (postHi - postLo + 1);
    if (inRangeSize != postRangeSize) {
        throw std::invalid_argument("InOrder & postOrder range sizes don't match");
    } else if (inRangeSize < 0) {
        throw std::invalid_argument("InOrder range size is negative");
    } else if (postRangeSize < 0) {
        throw std::invalid_argument("PostOrder range size is negative");
    } else {
        // showCrrState(inOrder, inLo, inHi, postOrder, postLo, postHi);
        if (inRangeSize == 0) {
            return NULL;
        } else if (inRangeSize == 1) {
            // printf("created node with root=%d\n", inOrder[inLo]);
            // printf("\n===========\n\n");
            return createNode(inOrder[inLo]);
        } else {
            int rootVal = postOrder[postHi];
            Node* root = createNode(rootVal);

            int rootIndInOrder = inIndMap[rootVal];
            int leftSubtreeNodeCount = rootIndInOrder - inLo;
            int rightSubtreeNodeCount = inHi - rootIndInOrder;
            // printf("root=%d, rootIndInOrder=%d, leftSubtreeNodeCount=%d, rightSubtreeNodeCount=%d\n", rootVal, rootIndInOrder, leftSubtreeNodeCount, rightSubtreeNodeCount);
            // printf("\n===========\n\n");

            root->left = createTree(inIndMap, inOrder, inLo, rootIndInOrder - 1, postOrder, postLo, postLo + leftSubtreeNodeCount - 1);
            root->right = createTree(inIndMap, inOrder, rootIndInOrder + 1, inHi, postOrder, postLo + leftSubtreeNodeCount, postHi - 1);

            return root;
        }
    }
}

void showCrrState(vector<int> inOrder, int inLo, int inHi, vector<int> postOrder, int postLo, int postHi) {
    showVecState(inOrder, "inOrder", inLo, inHi);
    showVecState(postOrder, "postOrder", postLo, postHi);
    cout << endl;
}

void showVecState(vector<int> vec, const char* name, int lo, int hi) {
    showVec(vec, name, false);
    cout << "Range:\t";
    for (int i = 0; i < vec.size(); i++) {
        if (i == lo) {
            printf("lo");
        }
        if (i == hi) {
            printf("hi");
        }
        cout << "\t";
    }
    cout << endl;
}

map<int, int> makeIndMap(vector<int> vec) {
    map<int, int> indMap;
    for (int i = 0; i < vec.size(); i++) {
        indMap[vec[i]] = i;
    }
    return indMap;
}

void showVec(vector<int> vec, const char* name, bool extraNewLine) {
    printf("%s vector is:-\n", name);

    cout << "Ind:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "Val:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;

    if (extraNewLine) {
        cout << endl;
    }
}

void showMap(map<int, int> myMap, const char* name, bool extraNewLine) {
    printf("%s map is:-\n", name);
    for (map<int, int>::iterator it = myMap.begin(); it != myMap.end(); it++) {
        printf("[%d] = %d\n", it->first, it->second);
    }

    if (extraNewLine) {
        cout << endl;
    }
}

vector<int> readVec(const char* name) {
    int ele;
    vector<int> vec;

    printf("\nEnter elements of %s vec\n(-1 to terminate)\n", name);
    cin >> ele;
    while (ele >= 0) {
        vec.push_back(ele);
        cin >> ele;
    }

    return vec;
}

Node* createNode(int val) {
    Node* newNode = new Node;
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void showInOrder(Node* root) {
    if (root != NULL) {
        showInOrder(root->left);
        cout << root->val << " ";
        showInOrder(root->right);
    }
}

void showPreOrder(Node* root) {
    if (root != NULL) {
        cout << root->val << " ";
        showPreOrder(root->left);
        showPreOrder(root->right);
    }
}

void showPostOrder(Node* root) {
    if (root != NULL) {
        showPostOrder(root->left);
        showPostOrder(root->right);
        cout << root->val << " ";
    }
}
