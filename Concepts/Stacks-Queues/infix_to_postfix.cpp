#include <iostream>
#include <cstdio>
#include <stack>
#include <map>
#include <cstring>

// 7+5*3^2/(9-2^2)+6*4      7532^*922^-/+64*+
// 8*(5^4+2)-6^2/(9*3)      854^2+*62^93*/-

using namespace std;
#define MAX 100

int isValid(char [], int, stack <char>&);
int isOpeningBracket(char);
int isClosingBracket(char);
int isOperator(char);
int isOfSameType(char, char);
void clearStack(stack <char>&);
void createPriorityMap(map <char, int>&);
void popAndPushBracket(stack <char>&, char [], int *);
void popAndPushPrecedence(stack <char>&, map <char, int>, char [], int *, char);
int convertToPostfix(char [], int, stack <char>&, map <char, int>, char []);
void clearStack();

int main() {
    map <char, int> priority;
	stack <char> arrStack;
	char arrIn[MAX];
	char arrPost[MAX];
	int lenIn;
	int lenPost;

	printf("Enter the expression:\t");
	scanf("%s", &arrIn);
	lenIn = strlen(arrIn);

	printf("The expression is:\t%s\n", arrIn);
	printf("The length is:\t\t%d\n", lenIn);
	printf("isValid(expression):\t%d\n", isValid(arrIn, lenIn, arrStack));

    createPriorityMap(priority);
	clearStack(arrStack);
	printf("\n");

	lenPost = convertToPostfix(arrIn, lenIn, arrStack, priority, arrPost) + 1;
	arrPost[lenPost] = '\0';

    printf("PostFix length is:\t%d\n", lenPost);
	printf("PostFix expression:\t%s\n", arrPost);

	return 0;
}

void createPriorityMap(map <char, int>& priority) {
    priority['^'] = 3;
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['%'] = 2;

    /*
    printf("\nPriority Map is:-\n");
    printf("%c\t%d\n", '^', priority['^']);
    printf("%c\t%d\n", '+', priority['+']);
    printf("%c\t%d\n", '-', priority['-']);
    printf("%c\t%d\n", '*', priority['*']);
    printf("%c\t%d\n", '/', priority['/']);
    */
}

int convertToPostfix(char arrIn[MAX], int lenIn, stack <char>& arrStack, map <char, int> priority, char arrPost[MAX]) {
	int indIn;
	int indPost;
	char ch;

	indPost = -1;
	for (indIn = 0; indIn < lenIn; indIn++) {
		ch = arrIn[indIn];
		//printf("At index %d, ch = %c\t", indIn, ch);

		if (isOpeningBracket(ch)) {
            //printf("pushed to stack");
			arrStack.push(ch);
		} else if (isClosingBracket(ch)) {
		    //printf("\n");
			popAndPushBracket(arrStack, arrPost, &indPost);
		} else if (isOperator(ch)) {
			popAndPushPrecedence(arrStack, priority, arrPost, &indPost, ch);
		} else {
		    //printf("added to postfix array");
			arrPost[++indPost] = ch;
		}
		//printf("\n");
	}

    while (!arrStack.empty()) {
        ch = arrStack.top();
        arrStack.pop();
        arrPost[++indPost] = ch;
    }

	return indPost;
}

void popAndPushBracket(stack <char>& arrStack, char arrPost[MAX], int * indPost) {
	char chStack;

	chStack = arrStack.top();
	arrStack.pop();

	while (!arrStack.empty() && !isOpeningBracket(chStack)) {
        //printf("%c added to postfix array\n", chStack);
		arrPost[++(*indPost)] = chStack;

		chStack = arrStack.top();
		arrStack.pop();
	}
}

void popAndPushPrecedence(stack <char>& arrStack, map <char, int> priority, char arrPost[MAX], int * indPost, char chIn) {
    char chStack;

    if (arrStack.empty()) {
        arrStack.push(chIn);
        //printf("pushed to stack", chIn);
        return;
    }

    chStack = arrStack.top();
    //printf("\n");

    while (priority[chStack] >= priority[chIn]) {
        //printf("%c added to postfix array\n", chStack);
        arrStack.pop();
        arrPost[++(*indPost)] = chStack;

        if (!arrStack.empty()) {
            chStack = arrStack.top();
        } else {
            break;
        }
    }

    arrStack.push(chIn);
    //printf("%c pushed to stack\n", chIn);
}

void clearStack(stack <char>& arrStack) {
	while (!arrStack.empty()) {
		arrStack.pop();
	}
}

int isValid(char arrIn[MAX], int lenIn, stack <char>& arrStack) {
	int i;
	char ch;

	for (i = 0; i < lenIn; i++) {
		ch = arrIn[i];

		//printf("At index %d ch = %c\t", i, ch);
		if (isOpeningBracket(ch)) {
			//printf("%c pushed to stack", ch);
			arrStack.push(ch);
		} else if (isClosingBracket(ch)) {
			if (arrStack.empty() || !isOfSameType(arrStack.top(), ch)) {
				//printf("invalidated\n");
				return 0;
			} else {
				//printf("%c popped from stack", arrStack.top());
				arrStack.pop();
			}
		}
		//printf("\n");
	}

	if (arrStack.empty()) {
		return 1;
	} else {
		return 0;
	}
}

int isOfSameType(char chOpening, char chClosing) {
	int result;

	result = 1;
	switch (chClosing) {
	case ')':
		if (chOpening != '(') {
			result = 0;
		}
		break;

	case '}':
		if (chOpening != '{') {
			result = 0;
		}
		break;

	case ']':
		if (chOpening != '[') {
			result = 0;
		}
		break;

	default:
		result = 0;
	}

	return result;
}

int isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
		return 1;
	} else {
		return 0;
	}
}

int isOpeningBracket(char ch) {
	if (ch == '(' || ch == '{' || ch == '[') {
		return 1;
	} else {
		return 0;
	}
}

int isClosingBracket(char ch) {
	if (ch == ')' || ch == '}' || ch == ']') {
		return 1;
	} else {
		return 0;
	}
}
