/*
2
sach
2
keh
2
rahaa
2
hai
2
deewana
2
dil
2
na
2
kisii
2
se
2
lagaana
2
jhoote
2
hain
2
pyaar
2
ke
2
vaade
2
saare
2
jhooti
2
hain
2
pyaar
2
ki
2
kasmein
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define LEN 26

struct node {
	node * child[LEN];
	bool ends[LEN];
};

node * createNode();
node * insertWord(node *, string);
bool searchWord(node *, string);
node * deleteWord(node *, string);
void showDict(node *, string);
int nodeCount(node *);

int main() {
	node * root = NULL;
	string word;
	int choice = -2;

	while (choice != 5) {
		printf("\nPick an option:-\n");
		printf("1. Search a word\n");
		printf("2. Insert a word\n");
		printf("3. Delete a word\n");
		printf("4. Show dictionary\n");
		printf("5. Exit\n");

		printf("\nEnter your choice:\t");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Enter the word:\t");
			cin >> word;
			if (searchWord(root, word)) {
				printf("Present in dictionary\n");
			} else {
				printf("Not present in dictionary\n");
			}
			break;

		case 2:
			printf("Enter the word:\t");
			cin >> word;
			root = insertWord(root, word);
			break;

		case 3:
			printf("Enter the word:\t");
			cin >> word;
			root = deleteWord(root, word);
			break;

		case 4:
			printf("Words in dictionary are:-\n");
			showDict(root, "");
			break;

		case 5:
			continue;

		default:
			printf("\nInvalid choice\n");
		}
	}

	return 0;
}

node * createNode() {
	node * newNode = new node;
	for (int i = 0; i < LEN; i++) {
		newNode -> child[i] = NULL;
	}
	memset(newNode -> ends, false, LEN * sizeof(bool));
	return newNode;
}

node * insertWord(node * root, string word) {
	if (word.size() == 0) {
		return root;
	}

	if (root == NULL) {
		root = createNode();
	}

	if (word.size() == 1) {
		root -> ends[word[0] - 'a'] = true;
	} else {
		root -> child[word[0] - 'a'] = insertWord(root -> child[word[0] - 'a'], word.substr(1));
	}

	return root;
}

bool searchWord(node * root, string word) {
	if (root == NULL) {
		return false;
	}

	if (word.size() == 1) {
		return root -> ends[word[0] - 'a'];
	} else {
		return searchWord(root -> child[word[0] - 'a'], word.substr(1));
	}
}

node * deleteWord(node * root, string word) {
	if (root == NULL) {
		printf("Word not present in dictionary\n");
		return NULL;
	} else if (word.size() == 1) {
		root -> ends[word[0] - 'a'] = false;

		int i;
		for (i = 0; i < LEN; i++) {
			if (root -> child[i] != NULL || root -> ends[i] == true) {
				break;
			}
		}

		if (i == LEN) {
			delete(root);
			return NULL;
		} else {
			return root;
		}
	} else {
		root -> child[word[0] - 'a'] = deleteWord(root -> child[word[0] - 'a'], word.substr(1));
		return root;
	}
}

void showDict(node * root, string prefix) {
	if (root != NULL) {
		for (int i = 0; i < LEN; i++) {
			if (root -> ends[i]) {
				cout << (prefix + ((char) ('a' + i))) << endl;
			}
			if (root -> child[i] != NULL) {
				showDict(root -> child[i], (prefix + ((char) ('a' + i))));
			}
		}
	}
}

int nodeCount(node * root) {
	if (root == NULL) {
		return 0;
	} else {
		int count = 0;
		for (int i = 0; i < LEN; i++) {
			if (root -> child[i] != NULL) {
				count += nodeCount(root -> child[i]);
			}
		}

		return (count + 1);
	}
}

void lvlOrder(node * root) {
	queue <node *> que;

	que.push(root);
	while (!que.empty()) {

	}
}

