#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int data;
    char a;
    char b;
    struct node *next;
};

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->data = 2;
    struct node *first;

    cout << &head << "\t" << head << "\t" << head->data << "\t" << head->a << "\t" << head->b << "\t" << head->next << endl;

    head->next = first;
    cout << &head << "\t" << head << "\t" << head->data << "\t" << head->a << "\t" << head->b << "\t" << head->next << endl;

    free(head);
    cout << &head << "\t" << head << "\t" << head->data << "\t" << head->a << "\t" << head->b << "\t" << head->next << endl;

    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    cout << &tmp << "\t" << tmp << "\t" << tmp->data << "\t" << tmp->a << "\t" << tmp->b << "\t" << tmp->next << endl;

    head->data = 5;
    cout << &head << "\t" << head << "\t" << head->data << "\t" << head->a << "\t" << head->b << "\t" << head->next << endl;
    cout << &tmp << "\t" << tmp << "\t" << tmp->data << "\t" << tmp->a << "\t" << tmp->b << "\t" << tmp->next << endl;

    char * c = (char *) malloc(sizeof(char));
	short * s = (short *) malloc(sizeof(short));
	int * l = (int *) malloc(sizeof(int));

	printf("sizeof(c) = %d\nsizeof(s) = %d\nsizeof(l) = %d\n", sizeof(*c), sizeof(*s), sizeof(*l));
}
