//http://www.geeksforgeeks.org/construct-a-special-tree-from-given-preorder-traversal/

/*
5
10 30 20 5 15
N  N  L  L L
*/

#include <cstdio>
#include <iostream>
#include <cctype>

using namespace std;
#define MAX 100

struct node {
	int val;
	struct node * left;
	struct node * right;
};

void input(int [MAX], int);
void input(char [MAX], int);
node * createNode(int);
node * createTree(int [MAX], char [MAX], int, int &);
void inOrder(node *);
void showArray(char [MAX], int);

int main() {
	int pre[MAX];
	char preLN[MAX];
	int len;

	cout << "Enter no of nodes in tree:\t";
	cin >> len;

	input(pre, len);
	input(preLN, len);

	showArray(preLN, len);

	int ind = 0;
	node * root = createTree(pre, preLN, len, ind);

	cout << "\nInOrder traversal of constructed tree is:-\n";
	inOrder(root);
	cout << endl;

	return 0;
}

void input(int pre[MAX], int len) {
	cout << "Enter pre[] array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> pre[i];
	}
}

void input(char preLN[MAX], int len) {
	char c;

	cout << "Enter pre[] array:-\n";
	for (int i = 0; i < len; i++) {
		while (isspace(c = getc(stdin))) {
		}
		preLN[i] = c;
	}
}

void showArray(char preLN[MAX], int len) {
	printf("\npreLN[] array is:-\n");
	for (int i = 0; i < len; i++) {
		putc(preLN[i], stdout);
		cout << " ";
	}
	cout << endl;
}

node * createTree(int pre[MAX], char preLN[MAX], int len, int &ind) {
	if (ind == len) {
		return NULL;
	} else {
		node * tmp = createNode(pre[ind]);
		ind++;

		if (preLN[ind - 1] == 'N') {
			tmp -> left = createTree(pre, preLN, len, ind);
			tmp -> right = createTree(pre, preLN, len, ind);
		}

		return tmp;
	}
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> left);
		printf("%d ", root -> val);
		inOrder(root -> right);
	}
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> left = NULL;
	newNode -> right = NULL;

	newNode -> val = val;

	return newNode;
}

