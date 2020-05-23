// A simple and tail recursive C++ program to reverse
// a linked list
#include<bits/stdc++.h>
using namespace std;

struct node {
	int data;
	struct node *next;
};

void mergeSort(node *, int, int);
void merge(node *, node *, int, int, int);

// A utility function to create a new node
node *newNode(int key) {
	node *temp = new node;
	temp->data = key;
	temp->next = NULL;
	return temp;
}

// A utility function to print a linked list
void printlist(node *head) {
	while(head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

// Driver program to test above functions
int main() {
//	node *head1 = newNode(8);
//	head1->next = newNode(1);
//	head1->next->next = newNode(3);
//	head1->next->next->next = newNode(7);
//	head1->next->next->next->next = newNode(4);
//	head1->next->next->next->next->next = newNode(2);
//	head1->next->next->next->next->next->next = newNode(9);
//	head1->next->next->next->next->next->next->next = newNode(10);
//	head1->next->next->next->next->next->next->next->next = newNode(-1);

	node *head1 = newNode(4);
	head1 -> next = newNode(1);

	cout << "Given linked list\n";
	printlist(head1);

	mergeSort(head1, 0, 1);

	cout << "\nSorted linked list\n";
	printlist(head1);

	return 0;
}

void mergeSort(node * head, int lo, int hi) {
//	printf("head = %d\tlo = %d\thi = %d\n", head -> data, lo, hi);
	if (lo < hi) {
		int mid = (lo + hi) / 2;
		node * tmp = head;

		for (int i = lo; i <= mid; i++) {
			tmp = tmp -> next;
		}

		mergeSort(head, lo, mid);
		mergeSort(tmp, mid + 1, hi);
		merge(head, tmp, lo, mid, hi);
	}
}

void merge(node * h1, node * h2, int lo, int mid, int hi) {
	int arr[hi - lo + 1];
	node * list1, * list2;
	int i, j, k;

	list1 = h1;
	list2 = h2;
	for (i = lo, j = mid + 1, k = 0; i <= mid && j <= hi; k++) {
//		printf("list1 -> data = %d\tlist2 -> data = %d\n", list1 -> data, list2 -> data);
		if (list1 -> data <= list2 -> data) {
			arr[k] = list1 -> data;
			list1 = list1 -> next;
			i++;
		} else {
			arr[k] = list2 -> data;
			list2 = list2 -> next;
			j++;
		}
	}

	while (i <= mid) {
		arr[k++] = list1 -> data;
		list1 = list1 -> next;
		i++;
	}

	while (j <= hi) {
		arr[k++] = list2 -> data;
		list2 = list2 -> next;
		j++;
	}

	for (i = lo, k = 0, list1 = h1; i <= hi; i++) {
		list1 -> data = arr[k++];
		list1 = list1 -> next;
	}

//	printf("\nafter merging, list is:-\n");
//	printlist(h1);
//	printf("\n");
}
