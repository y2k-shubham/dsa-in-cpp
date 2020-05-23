// http://www.geeksforgeeks.org/longest-consecutive-sequence-binary-tree/

/*
			1
	   2          3
	4     5   6      7
   8 9  10 11  13  14
       20 22    27
				 55


1 1
2 2		3 3
4 4		5 5		6 6		7 7
8 8		9 9		10 10	11 11	13 13	14 14
20 20	22 22	27 27
55 55
-1 -1
Ans = 2

6 1
9 3
7 6		10 7
11 15
-1 -1
Ans = 3

1 1
2 2		4 3
3 4		5 6		6 7
7 14
-1 -1
Ans = 3

90 1
1 2		66 3
2 4		67 7
5 8 	4 9		68 14
99 18		100	29
-1 -1
Ans = 3

90 1
1 2		67 3
2 4		67 7
5 8 	4 9		68 14
99 18		100	29
-1 -1
Ans = 2

90 1
1 2		67 3
3 4		67 7
5 8 	6 9		67 14
99 18		100	29
-1 -1
Ans = 1

1 1
2 2		2 3
3 4		3 5		4 7
4 11	5 15
6 31
-1 -1
Ans = 4

1 1
3 2		2 3
3 4		3 5		4 7
4 11	5 15
6 31
-1 -1
Ans = 3

1 1
2 2		2 3
3 4		3 5		4 7
4 11	5 15
6 31
7 62
8 124
-1 -1
Ans = 5

1 1
2 2		2 3
3 4		3 5		4 7
4 11	5 15
7 31
7 62
8 124
-1 -1
Ans = 4

1 1
3 2		3 3
5 4		3 5		3 7
4 11	5 15
7 31
7 62
9 124
-1 -1
Ans = 2

1 1
3 2		3 3
5 4		3 5		3 7
5 11	5 15
7 31
7 62
9 124
-1 -1
Ans = 1

1 1
3 2		2 3
3 4		3 5		4 7
4 11	5 15
6 31
-1 -1
Ans = 3

1 1
3 2		2 3
3 4		3 5		3 7
4 11	3 15
5 31
6 62
-1 -1
Ans = 3

1 1
3 2		2 3
3 4		3 5		3 7
4 11	4 15
5 31
6 62
-1 -1
Ans = 6

1 1
3 2		2 3
3 7
5 15
6 31
-1 -1
Ans = 3
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>
#include <climits>

using namespace std;

struct node {
	int val;
	struct node * lC;
	struct node * rC;
};

void inOrder(node *);
node * createNode(int);
node * getPath(int);
void showList(node *, const char *);
node * insert(node *, node *, node *);
int lcp(node *, int);
int lcp(node *, node *, int&, node **, map <node *, char>&);
void showLCP(map <node *, char>, node *, int);
int lcp(node *, node *, int);

int main() {
	node * root;
	int val, pos;
	map <node *, char> path;

	printf("\nEnter (val, pos) to insert into BST:-\n(pos starts from 1)\n");
	scanf("%d%d", &val, &pos);

	root = NULL;
	while (val != -1 && pos != -1) {
		node * path = getPath(pos);
//		showList(path);
		root = insert(root, path -> rC, createNode(val));

//		printf("\n");
		scanf("%d%d", &val, &pos);
	}

	printf("\nThe inOrder traversal is:-\n");
	inOrder(root);
	printf("\n");

	int lcpLen = 0;
	if (root != NULL) {
//		node * tmp = createNode(INT_MIN);
//
//		lcp(root, createNode(INT_MIN), lcpLen, &tmp, path);
//		lcpLen++;
//
//		printf("\nLength of LCP is %d\n", lcpLen);

//		if (lcpLen > 1) {
//			printf("LCP is:-\n");
//			showLCP(path, tmp -> lC, lcpLen);
//		}

		lcpLen = lcp(root, NULL, 1);
		printf("\nLength of LCP is %d\n", lcpLen);
	}

	return 0;
}

void inOrder(node * root) {
	if (root != NULL) {
		inOrder(root -> lC);
		printf("%d ", root -> val);
		inOrder(root -> rC);
	}
}

node * createNode(int val) {
	node * newNode = new node;

	newNode -> val = val;
	newNode -> lC = NULL;
	newNode -> rC = NULL;

	return newNode;
}

node * getPath(int val) {
	node * head;

	head = createNode(val);
	val /= 2;

	while (val >= 1) {
		node * newNode = createNode(val);
		newNode -> rC = head;
		head = newNode;

		val /= 2;
	}

	return head;
}

void showList(node * head, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (node * list = head; list != NULL; list = list -> rC) {
		printf("%d -> ", list -> val);
	}
	printf("NULL\n");
}

node * insert(node * root, node * path, node * newNode) {
	if (path == NULL) {
		return newNode;
	} else {
		if (path -> val % 2 == 1) {
			root -> rC = insert(root -> rC, path -> rC, newNode);
		} else {
			root -> lC = insert(root -> lC, path -> rC, newNode);
		}

		return root;
	}
}

// wrong methods
int lcp(node * root, int preVal) {
	if (root == NULL) {
		return 0;
	} else {
		int crrAns = max(lcp(root -> lC, root -> val), lcp(root -> rC, root -> val));

		if (root -> val == preVal + 1) {
			return 1 + crrAns;
		} else {
			return crrAns;
		}
	}
}

int lcp(node * root, node * preNode, int& maxLen, node ** maxLenRoot, map <node *, char>& path) {
	if (root == NULL) {
		return 0;
	} else {
		int lSeqLen = lcp(root -> lC, root, maxLen, maxLenRoot, path);
		int rSeqLen = lcp(root -> rC, root, maxLen, maxLenRoot, path);

		path[root] = (lSeqLen > rSeqLen) ? 'l' : 'r';
		int crrAns = max(lSeqLen, rSeqLen) + ((root -> val == preNode -> val + 1) ? 1 : 0);

		if (crrAns > maxLen) {
			maxLen = crrAns;
			(* maxLenRoot) -> lC = preNode;
		}

		return crrAns;
	}
}

void showLCP(map <node *, char> path, node * root, int remLen) {
	if (remLen > 0) {
		printf("%d\t", root -> val);

		if (path[root] == 'l') {
			showLCP(path, root -> lC, remLen - 1);
		} else {
			showLCP(path, root -> rC, remLen - 1);
		}
	} else {
		cout << endl;
	}
}

// correct method
int lcp(node * root, node * parent, int crrSeqLen) {
	if (root == NULL) {
		return 0;
	} else {
		if (parent != NULL && root -> val == parent -> val + 1) {
			crrSeqLen++;
		}

		int lSeqLen = 0;
		int rSeqLen = 0;
		if (root -> lC != NULL && root -> lC -> val == root -> val + 1) {
			lSeqLen = lcp(root -> lC, root, crrSeqLen);
		} else {
			lSeqLen = lcp(root -> lC, root, 1);
		}
		if (root -> rC != NULL && root -> rC -> val == root -> val + 1) {
			rSeqLen = lcp(root -> rC, root, crrSeqLen);
		} else {
			rSeqLen = lcp(root -> rC, root, 1);
		}

		int mSeqLen = max(lSeqLen, rSeqLen);
		return max(crrSeqLen, mSeqLen);
	}
}

