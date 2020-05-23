#include <stdio.h>
#include <stdlib.h>


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

//    cout << head << " " << head->data << " " << head->next << endl;
	printf("0x%x\t0x%x\t%d\t%c\t%c\t0x%x\n", &head, head, head->data, head->a, head->b, head->next);

    head->next = first;
//    cout << head << " " << head->data << " " << head->next << endl;
	printf("0x%x\t0x%x\t%d\t%c\t%c\t0x%x\n", &head, head, head->data, head->a, head->b, head->next);

    free(head);
//    cout << head << " " << head->data << " " << head->next << endl;
	printf("0x%x\t0x%x\t%d\t%c\t%c\t0x%x\n", &head, head, head->data, head->a, head->b, head->next);
}


