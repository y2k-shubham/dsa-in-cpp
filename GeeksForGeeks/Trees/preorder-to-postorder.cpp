// http://www.practice.geeksforgeeks.org/problem-page.php?pid=559
// http://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/
// http://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversa/
// Stack O(n) method : http://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversal-set-2/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

using namespace std;
typedef struct node link;

#define MAX 100

link * createNode(int);
void input(int [MAX], int&);
node * createTreeStack(int [MAX], int);

int main() {
	int n;
	int in[MAX];
	int pre[MAX];
	node * root;

	input(pre, n);

	memcpy(pre, in, n * sizeof(int));
	sort(in, in + n);

	root = createTreeStack(pre, n);

	printf("\nThe inOrder traversal is:-\n");
	//inOrder(root);

	printf("\nThe preOrder traversal is:-\n");
	//preOrder(root);

	printf("\nThe postOrder traversal is:-\n");
	//postOrder(root);

	return 0;
}

link * createNode(int val) {
	link * newNode;
	newNode = (link *) malloc(sizeof(link));

	newNode -> lC = NULL;
	newNode -> rC = NULL;
	newNode -> val = val;

	return newNode;
}

void input(int pre[MAX], int& n) {
	printf("Enter no of nodes:\t");
	scanf("%d", &n);

	printf("Enter the preOrder traversal:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &pre[i]);
	}
}

node * createTreeStack(int pre[MAX], int n) {
	stack <node *> stk;
	node * tmp;

	stk.push(createNode(pre[0]));
	for (int i = 1; i < n; i++) {
		node * newNode = createNode(pre[i]);

		if (stk.top() -> val < pre[i]) {
			while (!stk.empty() && pre[i] > stk.top() -> val) {
				tmp = stk.top();
				stk.pop();
			}
			tmp -> rC = newNode;
		} else {
			stk.top() -> lC = newNode;
		}
	}
}
