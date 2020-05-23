#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <cmath>

// 7532^*922^-/+64*+ (answer = 40)

using namespace std;
#define MAX 100

float evaluate(char [], int, stack <float>&);
float findResult(float, float, char);
int isDigit(char);
float popFromStack(stack <float>&);

int main() {
	char arrPost[MAX];
	stack <float> arrStack;
	int lenPost;
	float result;

	printf("Enter the PostFix expression:\t");
	scanf("%s", &arrPost);
	lenPost = strlen(arrPost);

	result = evaluate(arrPost, lenPost, arrStack);
	printf("\nThe result is:\t%f\n", result);

	return 0;
}

float evaluate(char arrPost[MAX], int lenPost, stack <float>& arrStack) {
    int indPost;
    char ch;
    float operand_1;
    float operand_2;
    float result;

    for (indPost = 0; indPost < lenPost; indPost++) {
        ch = arrPost[indPost];

        if (isdigit(ch)) {
            arrStack.push(ch - '0');
        } else {
            operand_1 = popFromStack(arrStack);
            operand_2 = popFromStack(arrStack);
            result = findResult(operand_2, operand_1, ch);
            printf("performed %f\t%c\t%f\t=\t%f\n", operand_1, ch, operand_2, result);
            arrStack.push(result);
        }
    }

    return popFromStack(arrStack);
}

float findResult(float operand_1, float operand_2, char op) {
    switch (op) {
        case '+':   return operand_1 + operand_2;
        case '-':   return operand_1 - operand_2;
        case '*':   return operand_1 * operand_2;
        case '/':   return operand_1 / operand_2;
        case '^':   return powf(operand_1, operand_2);
        default:    return -999;
    }
}

int isDigit(char ch) {
    if ('0' <= ch && ch <= '9') {
        return 1;
    } else {
        return 0;
    }
}

float popFromStack(stack <float>& arrStack) {
    float element;

    element = arrStack.top();
    arrStack.pop();

    return element;
}
