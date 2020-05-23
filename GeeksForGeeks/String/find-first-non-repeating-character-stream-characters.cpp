// http://www.geeksforgeeks.org/find-first-non-repeating-character-stream-characters/
// geeksforgeeksandgeeksquizfor

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

struct node {
	char c;
	struct node * next;
	struct node * prev;
};

using namespace std;
#define MAX 256

node * createNode(char);
node * insert(node *, node *);

int main() {
	string str;
	node * head, * tail;
	bool occured[MAX];
	node * ptr[MAX] = {NULL};

//	memset(ptr, NULL, sizeof(ptr));
	memset(occured, false, sizeof(occured));
	head = tail = NULL;

	cout << "Enter string:\t";
	getline(cin, str);

	for (int i = 0; i < str.length(); i++) {
		char c = str[i];
		node * tmp = ptr[c];

		if (occured[c] == false) {
			// insert into linked list
			occured[c] = true;

			tail = insert(tail, createNode(c));
			head = (head == NULL) ? tail : head;

			ptr[c] = tail;
		} else {
			if (tmp == NULL) {
				// do nothing
				if (head != NULL) {
					printf("till str[%d] = %c, first non-repeating char = %c\n", i, str[i], head -> c);
				} else {
					printf("till str[%d] = %c, no non-repeating chars\n", i, str[i]);
				}
				continue;
			} else {
				if (tmp == head) {
					// delete head
					head = head -> next;

					if (head == NULL) {
						tail = NULL;
					}
				} else if (tmp == tail) {
					// delete tail
					tail = tail -> prev;

					if (tail == NULL) {
						head = NULL;
					}
				} else {
					// delete node from list
					tmp -> prev -> next = tmp -> next;
					tmp -> next -> prev = tmp -> prev;

				}

				delete(tmp);
				ptr[c] = NULL;
			}
		}

		if (head != NULL) {
			printf("till str[%d] = %c, first non-repeating char = %c\n", i, str[i], head -> c);
		} else {
			printf("till str[%d] = %c, no non-repeating chars\n", i, str[i]);
		}
	}

	return 0;
}

node * createNode(char c) {
	node * newNode = new node;
	newNode -> c = c;
	newNode -> next = NULL;
	newNode -> prev = NULL;
}

node * insert(node * tail, node * newNode) {
	if (tail != NULL) {
		newNode -> prev = tail;
		tail -> next = newNode;
	}
	return newNode;
}

