// https://practice.geeksforgeeks.org/problems/count-bst-nodes-that-lie-in-a-given-range/1
// De-Shaw

/*
50
25 75
10 37 100
30 87 150
34 81
78 84
-1

390 832 49 680 592 740 607 901 534 931 605 198 754 712 301 50 974 641 574 394 921 272 141 887 189 163 437 666 167 465 863 908 296 912 587 888 3 545 140 888 828 744 86 933 455 386 -1
19 982
*/

#include <cstdio>
#include <iostream>
// for ostringstream
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct node {
  int val;
  struct node * left;
  struct node * right;
};

node * input();
node * insertNode(node *, int);
node * createNode(int);
void printInOrder(node *);
vector <int> getPath(int);
void showVec(vector <int>, string);
int countNodesInRange(node *, int, int);

int main() {
  node * root = input();
  cout << "InOrder traversal of BST is:-" << endl; 
  printInOrder(root);
  cout << endl;

  int rLo, rHi;
  cout << "Enter range to get count of elements:-" << endl;
  cin >> rLo >> rHi;

  int count = countNodesInRange(root, rLo, rHi);
  cout << "There are " << count << " nodes in range (" << rLo << ", " << rHi << ")" << endl;

  return 0;
}

node * input() {
  int ele;
  node * root = NULL;

  cout << "Enter elements of BST (-1 to terminate):-" << endl;
  cin >> ele;
  do {
    root = insertNode(root, ele);
    cin >> ele;
  } while (ele != -1);

  return root;
}

node * insertNode(node * root, int ele) {
  if (root == NULL) {
    return createNode(ele);
  } else {
    if (ele < root -> val) {
      root -> left = insertNode(root -> left, ele);
    } else if (ele > root -> val) {
      root -> right = insertNode(root -> right, ele);
    } else {
      printf("BST can't have duplicate nodes\n");
      return root;
    }
    return root;
  }
}

void printInOrder(node * root) {
  if (root != NULL) {
    printInOrder(root -> left);
    cout << root -> val << "\t";
    printInOrder(root -> right);
  }
}

node * createNode(int ele) {
  node * newNode = new node;

  newNode -> val = ele;
  newNode -> left = NULL;
  newNode -> right = NULL;

  return newNode;
}

int countNodesInRange(node * root, int rLo, int rHi) {
  if (root == NULL) {
    return 0;
  } else {
    int leftResult, crrResult, rightResult;

    // printf("at node %d, (rLo=%d, rHi=%d)\n", root -> val, rLo, rHi);

    if (rLo < root -> val) {
      leftResult = countNodesInRange(root -> left, rLo, min(root -> val - 1, rHi));
    } else {
      leftResult = 0;
    }
    if (root -> val < rHi) {
      rightResult = countNodesInRange(root -> right, max(rLo, root -> val + 1), rHi);
    } else {
      rightResult = 0;
    }
    if (rLo <= root -> val && root -> val <= rHi) {
      // printf("node %d included\n", root -> val);
      crrResult = 1;
    } else {
      crrResult = 0;
    }
    return (leftResult + crrResult + rightResult);
  }
}

vector <int> getPath(int pos) {
  vector <int> vec;
  do {
    vec.push_back(pos);
    pos = pos / 2;
  } while (pos > 1);

  reverse(vec.begin(), vec.end());

  return vec;
}

void showVec(vector <int> vec, string name) {
  printf("%s vector is:-\n", name.c_str());
  for (vector <int>::iterator it = vec.begin(); it != vec.end(); it++) {
    printf("%d\t", (* it));
  }
  cout << endl;
}
