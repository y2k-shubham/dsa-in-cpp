// https://www.geeksforgeeks.org/finding-the-lexicographically-smallest-diameter-in-a-binary-tree/

/*
>> check the input format, it's given in comments on top of the program.
>> it says keep entering values to be inserted into tree along with their position in the tree, till -1 is entered for position.
>> here position is 1-indexed, so root has position 1, root -> left has position 2, root -> right has position 3, root -> left -> left has position 4 and so on.
>> the tree need not be complete binary tree but all successive insertion positions should be legal
>> in the input given below, all nodes (along-with their positions) written in a single line actually lie in same level, so each line of input denotes a level
*/

/*
    a
  b    c
 d e  f g

a 1
b 2 c 3
d 4 e 5 f 6 g 7
x -1

     k
   e   s
  g f

k 1
e 2 s 3
g 4 f 5
x -1
*/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct node {
    char val;
    struct node *left;
    struct node *right;
};

node *inputTree();
void showTree(node *, string, bool);
void inOrder(node *);
void levelOrder(node *);
node *createNode(char);
node *getPath(int);
node *insert(node *, node *, node *);
string reversed(string);
string lexSmallestDiameter(node *, int, string &);
int findDiameter(node *, int &);

int main() {
    node *root = inputTree();

    showTree(root, "inOrder", true);
    showTree(root, "levelOrder", true);

    int dia = 0;
    findDiameter(root, dia);
    cout << "length of diameter is " << dia << endl;

	string lsd = "zzzz";
	lexSmallestDiameter(root, dia, lsd);

		cout << "lexicographically smallest diameter is " << lsd << endl;

    return 0;
}

/**
 * 
 **/
string lexSmallestDiameter(node *root, int dia, string &lsd) {
    string lexSmall;
    if (root == NULL) {
        lexSmall = "";
    } else if (root -> left == NULL && root -> right == NULL) {
			lexSmall += root->val;
		} else {
			string lResult = lexSmallestDiameter(root->left, dia, lsd);
			string rResult = lexSmallestDiameter(root->right, dia, lsd);

			string small, big;
			if (rResult.empty() || lResult.compare(rResult) < 0) {
				small = lResult;
                big = rResult;
			} else {
				small = rResult;
                big = lResult;
			}
			lexSmall = small + root->val;

			string lsdCand = lexSmall + reversed(big);

			// cout << endl << "=======" << endl;
			// printf("at node=%c\n", root->val);
			// printf("lResult=%s\trResult=%s\n", lResult.c_str(), rResult.c_str());
			// cout << endl;
			// printf("lexSmall=%s\n", lexSmall.c_str());
			// printf("lsdCand=%s\n", lsdCand.c_str());
			
			if (lsdCand.size() >= dia && lsdCand.compare(lsd) < 0) {
				// cout << endl;
				// printf("Updated lsd=%s to lsdCand=%s\n", lsd.c_str(), lsdCand.c_str());
				lsd = lsdCand;
			}

			// cout << "=======" << endl;
    }
    return lexSmall;
}

node *inputTree() {
    node *root;
    char val;
    int pos;

    printf("\nEnter (val, pos) to insert into Tree:-\n(pos starts from 1)\n");
    scanf(" %c%d", &val, &pos);
    getchar();

    root = NULL;
    while (pos != -1) {
        node *path = getPath(pos);
        root = insert(root, path->right, createNode(val));

        scanf(" %c%d", &val, &pos);
        getchar();
    }

    return root;
}

node *getPath(int pos) {
    node *head;

    head = createNode(pos);
    pos /= 2;

    while (pos >= 1) {
        node *newNode = createNode(pos);
        newNode->right = head;
        head = newNode;

        pos /= 2;
    }

    return head;
}

node *insert(node *root, node *path, node *newNode) {
    if (path == NULL) {
        //		printf("at node %d\tpath = NULL\n", root -> val);
        return newNode;
    } else {
        //		printf("at node %d\tpath = %d\n", root -> val, path -> val);
        if (path->val % 2 == 1) {
            root->right = insert(root->right, path->right, newNode);
        } else {
            root->left = insert(root->left, path->right, newNode);
        }

        return root;
    }
}

node *createNode(char val) {
    node *newNode = new node;

    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void showTree(node *root, string travType, bool newLineBefore) {
    if (newLineBefore) {
        cout << endl;
    }
    cout << "The " << travType << " traversal is:-" << endl;
    if (travType.compare("inOrder") == 0) {
        inOrder(root);
    } else if (travType.compare("levelOrder") == 0) {
        levelOrder(root);
    } else {
        throw std::invalid_argument("invalid traversal type");
    }
    cout << endl;
}

void inOrder(node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%c ", root->val);
        inOrder(root->right);
    }
}

void levelOrder(node *root) {
    queue<node *> que;

    que.push(root);
    while (!que.empty()) {
        int nodeCount = que.size();

        while (nodeCount > 0) {
            node *crrNode = que.front();
            que.pop();

            printf("%c ", crrNode->val);

            if (crrNode->left != NULL) {
                que.push(crrNode->left);
            }
            if (crrNode->right != NULL) {
                que.push(crrNode->right);
            }

            nodeCount--;
        }
        cout << endl;
    }
    cout << endl;
}

string reversed(string str) {
    string revStr = str;
    reverse(revStr.begin(), revStr.end());
    return revStr;
}

int findDiameter(node * root, int &dia) {
    if (root == NULL) {
        return 0;
    } else {
        int lHeight = findDiameter(root -> left, dia);
        int rHeight = findDiameter(root -> right, dia);
        int crrDia = lHeight + rHeight + 1;
        dia = max(dia, crrDia);
        return max(lHeight, rHeight) + 1;
    }
}
