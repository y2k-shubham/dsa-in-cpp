#include <stdio.h>
#include <string.h>
#define max 400

void input(char [][max], int);
void convert(char [][max], char [][max], int);
void output(char [][max], int);

int main() {
    int t;

    scanf("%d", &t);

    char infix[t][max];
    char postfix[t][max];

    input(infix, t);
    convert(infix, postfix, t);
    output(postfix, t);

    return 0;
}

void input(char infix[][max], int t) {
    int i;

    for (i = 0; i < t; i++) {
        scanf("%s", &infix[i]);
    }
}

void convert(char infix[][max], char postfix[][max], int t) {
    int i;
    int j;
    int k;
    int count;
    int top;
    char ch;
    char stack[max];

    for (i = 0; i < t; i++) {
        memset(stack, 0, (max * sizeof(char)));
        memset(postfix[i], 0, (max * sizeof(char)));

        count = 1;
        k = -1;
        top = -1;

        for (j = 1; count > 0; j++) {
            ch = infix[i][j];

            if (ch == '(') {
                count++;
            } else if (((ch >= 97) && (ch <= 122)) || ((ch >= 65) && (ch <= 90)) || ((ch >= 48) && (ch <= 57))) {
                postfix[i][++k] = ch;
            } else if (ch == ')') {
                postfix[i][++k] = stack[top--];
                count--;
            } else {
                stack[++top] = ch;
            }
        }
    }
}

void output(char postfix[][max], int t) {
    int i;

    for (i = 0; i < t; i++) {
        printf("%s\n", postfix[i]);
    }
}
