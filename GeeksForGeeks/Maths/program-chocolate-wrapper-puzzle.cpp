/*
16 2 2
Ans: 15

15 1 3
Ans: 22

20 3 5
Ans: 7
*/

#include <cstdio>

using namespace std;

int main() {
	int money, price, wrapReq;
	int chocCount, wrapAvail;

	printf("Enter money, price and wrappers needed for exchange:\t");
	scanf("%d%d%d", &money, &price, &wrapReq);

	chocCount = wrapAvail = money / price;
	money = money % price;

	while (wrapAvail >= wrapReq) {
		int chocGot = wrapAvail / wrapReq;
		chocCount += chocGot;
		wrapAvail = (wrapAvail % wrapReq) + chocGot;
	}

	printf("\nChocolates bought = %d\n", chocCount);
	printf("Money left        = %d\n", money);
	printf("Wrappers left     = %d\n", wrapAvail);

	return 0;
}

