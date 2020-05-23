#include <cstdio>
#include <iostream>

using namespace std;

struct node {
	int val;
};

node * createNode(int);
void makeNull1(node *);
void makeNull2(node * &);
void makeNull3(node **);

int main() {
	node * tmp = createNode(-1);

	printf("tmp = %d\n", tmp -> val);
	makeNull1(tmp);
	printf("tmp = %d\n", tmp -> val);

	printf("tmp = %d\n", tmp -> val);
	makeNull2(tmp);
	printf("tmp = %d\n", tmp -> val);

	printf("tmp = %d\n", tmp -> val);
	makeNull3(&tmp);
	printf("tmp = %d\n", tmp -> val);

	return 0;
}

node * createNode(int val) {
	node * tmp = new node;
	tmp -> val = val;

	return tmp;
}

void makeNull1(node * tmp) {
	tmp = NULL;
}

void makeNull2(node * &tmp) {
	tmp = NULL;
}

void makeNull3(node ** tmp) {
	*tmp = NULL;
}
