/*
Program is correct but output function, which is supposed to display complete
solution is wrong and almost always ends up in infinite loop

Input:
8
2 5 7 1 4 3 1 3
3

Output:
maxProfit = 10
Day     [0]     [1]     [2]     [3]     [4]     [5]     [6]     [7]
Price   2       5       7       1       4       3       1       3
--------------------------------------------------------------------
        B---------------S[5]    B-------S[3]            B-------S[2]

Input:
7
100 180 260 310 40 535 695
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <stack>

using namespace std;

#define MAX 100
#define max(a, b) ((a > b) ? a : b)

void input(int [MAX], int &, int &);
void init(int [MAX][MAX], int, int, int, int);
void calc(int [MAX], int, int, int [MAX][MAX]);
void showTable(int [MAX][MAX], int [MAX], int, int);
void output(int [MAX][MAX], int [MAX], int, int);
int pop(stack <int> &);

int main() {
	int days;
	int k;
	int price[MAX];
	int table[MAX][MAX];

	input(price, days, k);
	init(table, 0, k - 1, 0, 0);
	init(table, 0, 0, 0, days - 1);

	calc(price, days, k, table);
	showTable(table, price, days, k);
	printf("maxProfit = %d\n", table[k][days - 1]);
	//output(table, price, days, k);

	return 0;
}

void input(int price[MAX], int &days, int &k) {
	printf("Enter the number of days:\t");
	scanf("%d", &days);

	printf("Enter the prices of stocks for %d days:-\n", days);
	for (int i = 0; i < days; i++) {
		scanf("%d", &price[i]);
	}

	printf("Enter the max no of txns:\t");
	scanf("%d", &k);
}

void init(int table[MAX][MAX], int rowLo, int rowHi, int colLo, int colHi) {
	for (int i = rowLo; i <= rowHi; i++) {
		for (int j = colLo; j <= colHi; j++) {
			table[i][j] = 0;
		}
	}
}

void calc(int price[MAX], int maxDays, int k, int table[MAX][MAX]) {
//	printf("\t");
//	for (int i =0; i < maxDays; i++) {
//		printf("day %d\t", i);
//	}

	for (int txn = 1; txn <= k; txn++) {
		int maxDiff = INT_MIN;
//		printf("\n\t%d\t", maxDiff);

		for (int day = 1; day < maxDays; day++) {
//			printf("%d\t", maxDiff);
			maxDiff = max(maxDiff, table[txn - 1][day - 1] - price[day - 1]);
			table[txn][day] = max(table[txn][day - 1], price[day] + maxDiff);
		}
	}
//	printf("\n");
}

void showTable(int table[MAX][MAX], int price[MAX], int days, int k) {
	printf("\nThe table is:-");

	printf("\nDay\t");
	for (int i = 0; i < days; i++) {
		printf("[%d]\t", i);
	}

	printf("\nPrice\t");
	for (int i = 0; i < days; i++) {
		printf("%d\t", price[i]);
	}

	printf("\n");
	for (int i = 0; i <= days; i++) {
		printf("--------");
	}

	for (int txn = 0; txn <= k; txn++) {
		printf("\nTxn_%d\t", txn);
		for (int day = 0; day < days; day++) {
			printf("%d\t", table[txn][day]);
		}
	}

	printf("\n");
}

void output(int table[MAX][MAX], int price[MAX], int maxDays, int k) {
	// Display the max profit
	printf("\nThe max possible profit is %d\n", table[k][maxDays - 1]);

	// compute the days of transactions and store them in a stack
	stack <int> dayNo, dayNo_copy;
	int txn, day;
	int crr;
	bool isBuy;

	for (txn = k, day = maxDays - 1; txn > 0; ) {
		if (table[txn][day] != table[txn][day - 1]) {
			isBuy = !isBuy;
			dayNo.push(day);

			int remProf = table[txn][day] - price[day];
			txn--;

			while (table[txn][day] - price[day] != remProf) {
				day--;
			}

			dayNo.push(day);
		} else {
			day--;
		}
	}

	// display headings
	printf("The txns to obtain this profit were:-");

	printf("\nDay\t");
	for (int i = 0; i < maxDays; i++) {
		printf("[%d]\t", i);
	}

	printf("\nPrice\t");
	for (int i = 0; i < maxDays; i++) {
		printf("%d\t", price[i]);
	}

	printf("\n");
	for (int i = 0; i <= maxDays; i++) {
		printf("--------");
	}

	// from the stack created above, extract days one-by-one and display transactions
	// (whether buy or sell and profit in case of sell)
	day = 0;
	dayNo_copy = dayNo;

	crr = pop(dayNo);
	isBuy = true;
	int costPrice, sellPrice;

	printf("\n\t");
	while (!dayNo.empty()) {
		if (day == crr) {
			if (isBuy) {
				costPrice = price[day];
				printf("B-------");
			} else {
				sellPrice = price[day];
				printf("S[%d]\t", (sellPrice - costPrice));
			}

			isBuy = !isBuy;
			crr = pop(dayNo);
		} else if (!isBuy) {
			printf("--------");
		} else {
			printf("\t");
		}

		day++;
	}
	while (day < crr) {
		day++;
	}
	sellPrice = price[day];
	printf("S[%d]\n", (sellPrice - costPrice));
}

int pop(stack <int> &stk) {
	int tmp = stk.top();
	stk.pop();

	return tmp;
}

