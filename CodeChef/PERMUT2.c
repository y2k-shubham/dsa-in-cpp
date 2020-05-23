#include <stdio.h>
#include <stdlib.h>

#define len 100001

struct node {
    char * answer;
    struct node * next;
};

typedef struct node link;

link * inputAndProcess(int [], char * []);
link * createNode(char *);
void output(link *);

int main() {
    int numbers[len];
    link * head;
    char * result[2];

    result[0] = "not ambiguous";
    result[1] = "ambiguous";

    head = inputAndProcess(numbers, result);
    output(head);

    return 0;
}

link * inputAndProcess(int numbers[], char * result[]) {
    int i;
    int n;
    link * head;
    link * newNode;
    link * list;

    head = NULL;
    scanf("%d", &n);

    while (n > 0) {
        for (i = 1; i <= n; i++) {
            scanf("%d", &numbers[i]);
        }

        for (i = 1; (i <= n) && (numbers[numbers[i]] == i); i++) {
        }

        if (i > n) {
            newNode = createNode(result[1]);
        } else {
            newNode = createNode(result[0]);
        }

        if (head == NULL) {
            head = newNode;
            list = head;
        } else {
            list -> next = newNode;
            list = newNode;
        }

        scanf("%d", &n);
    }

    return head;
}

link * createNode(char * str) {
    link * newNode;

    newNode = (link *) malloc(sizeof(link));
    newNode -> answer = str;
    newNode -> next = NULL;

    return newNode;
}

void output(link * head) {
    link * list;

    for (list = head; list != NULL; list = list -> next) {
        printf("%s\n", list -> answer);
    }
}
