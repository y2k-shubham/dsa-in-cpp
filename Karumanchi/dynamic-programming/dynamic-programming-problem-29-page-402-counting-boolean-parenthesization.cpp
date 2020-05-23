// http://www.geeksforgeeks.org/dynamic-programming-set-37-boolean-parenthesization-problem/

/*
0^1&0^1
1^0&1
1^0|0
1|1&0^1
*/

#include <cstdio>
#include <iostream>
#include <utility>
#include <map>

using namespace std;
#define MAX 100

// input and initialize
void input(int [MAX], map <pair <int, int>, char> &, int &);
void init(int [MAX], pair <int, int> [MAX][MAX], int);
// output
void showArr(int [MAX], int);
void showMap(map <pair <int, int>, char>);
void showTab(int [MAX], map <pair <int, int>, char>, int, pair <int, int> [MAX][MAX], const char *);
// find no of ways of parenthesization via dynamic programming
void findWays(int [MAX], map <pair <int, int>, char>, int, pair <int, int> [MAX][MAX]);

int main() {
	int opRand[MAX], expLen;
	map <pair <int, int>, char> opRator;
	pair <int, int> count[MAX][MAX];

	input(opRand, opRator, expLen);
	showArr(opRand, expLen);
	showMap(opRator);

	init(opRand, count, expLen);
	showTab(opRand, opRator, expLen, count, "before filling");

	findWays(opRand, opRator, expLen, count);
	showTab(opRand, opRator, expLen, count, "after filling");

	return 0;
}

// input and initialize
void input(int opRand[MAX], map <pair <int, int>, char> &opRator, int &expLen) {
	string exp;

	cout << "Enter the expression:\t";
	cin >> exp;

	expLen = 0;
	for (int i = 0; i < exp.length(); i++) {
		if (i % 2 == 0) {
			// operand
			opRand[expLen++] = (exp[i] - '0');
		} else {
			// operator
			opRator.insert(make_pair(make_pair(expLen - 1, expLen), exp[i]));
		}
	}
}

void init(int opRand[MAX], pair <int, int> count[MAX][MAX], int expLen) {
	for (int i = 0; i < expLen; i++) {
		if (opRand[i] == 1) {
			count[i][i].first = 1;
			count[i][i].second = 0;
		} else {
			count[i][i].first = 0;
			count[i][i].second = 1;
		}

		for (int j = i + 1; j < expLen; j++) {
			count[i][j].first = count[i][j].second = 0;
		}
	}
}

// find no of ways of parenthesization via dynamic programming
void findWays(int opRand[MAX], map <pair <int, int>, char> opRator, int expLen, pair <int, int> count[MAX][MAX]) {
	for (int len = 2; len <= expLen; len++) {
//		printf("\n==================\n");
		int rLo = 0;
		int cLo = len - 1;

		int rHi = expLen - len;
		int cHi = expLen - 1;

		int i, j;
		for (i = rLo, j = cLo; j <= cHi; i++, j++) {
//			printf("\nfilling (%d, %d)\n", i, j);
			for (int k = i; k < j; k++) {
				switch (opRator[make_pair(k, k + 1)]) {
					case '|':
						count[i][j].first	+=	(count[i][k].first  * count[k + 1][j].first)	+
												(count[i][k].first  * count[k + 1][j].second)	+
												(count[i][k].second * count[k + 1][j].first)	;
						count[i][j].second	+=	(count[i][k].second * count[k + 1][j].second)	;
						break;

					case '&':
						count[i][j].first	+=	(count[i][k].first  * count[k + 1][j].first)	;
						count[i][j].second	+=	(count[i][k].second * count[k + 1][j].second)	+
												(count[i][k].first  * count[k + 1][j].second)	+
												(count[i][k].second * count[k + 1][j].first)	;
						break;

					case '^':
						count[i][j].first	+=	(count[i][k].first  * count[k + 1][j].second)	+
												(count[i][k].second * count[k + 1][j].first)	;
						count[i][j].second	+=	(count[i][k].first  * count[k + 1][j].first)	+
												(count[i][k].second * count[k + 1][j].second)	;
						break;

					default:
						printf("Unknown operator between %d and %d:\t%c\n", k, (k + 1), opRator[make_pair(k, k + 1)]);
				}
//				printf("at k = %d\top = %c\tc[%d][%d] = (%d, %d)\n", k, opRator[make_pair(k, k + 1)], i, j, count[i][j].first, count[i][j].second);
			}
		}
	}
}

// output
void showArr(int opRand[MAX], int expLen) {
	cout << "\nSequence of operands is:-\n";

	cout << "Ind:\t";
	for (int i = 0; i < expLen; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Oper:\t";
	for (int i = 0; i < expLen; i++) {
		printf("%d\t", opRand[i]);
	}
	cout << endl;
}

void showMap(map <pair <int, int>, char> opRator) {
	cout << "\nSequence of operators is:-\n";

	for (map <pair <int, int>, char>::iterator i = opRator.begin(); i != opRator.end(); i++) {
		pair <int, int> ind = (*i).first;
		char op = (*i).second;

		printf("[%d][%d]\t%c\n", ind.first, ind.second, op);
	}
}

void showTab(int opRand[MAX], map <pair <int, int>, char> opRator, int expLen, pair <int, int> count[MAX][MAX], const char * msg) {
	printf("\nTable %s is:-\n", msg);

	for (int i = 0; i < expLen - 1; i++) {
		printf("   %d   %c", opRand[i], opRator[make_pair(i, i + 1)]);
	}
	printf("  %d\n", opRand[expLen - 1]);

	for (int i = 0; i < expLen; i++) {
		int j;

		cout << opRand[i];
		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < expLen; j++) {
			printf("(%d, %d)\t", count[i][j].first, count[i][j].second);
		}
		cout << endl;
	}
}

