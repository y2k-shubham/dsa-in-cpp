/*
4
aaaass dddefggggh
sdpaaaassdddefggggh
qwertyuiopasdfghjklzxcvbnm
rrrrrrrrrrrrrrrrrrrrrrr
*/

#include <cstring>
#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;
#define MAX 200

void convC(char *);
void convCPP(string);

int main() {
	int t;

	printf("Enter no of test cases:\t");
	cin >> t;

	getc(stdin);
	while (t-- > 0) {
		char * strC;
		string strCPP;

		strC = (char *) calloc(MAX, sizeof(char));
//		strCPP.resize(MAX);

		printf("\nEnter string:\t");
		getline(cin, strCPP);

//		fgets(strC, MAX, stdin);
		strC = (char *) strCPP.c_str();
//		strC[strlen(strC) - 1] = '\0';

//		convC(strC);
		convCPP(strCPP);
	}

	return 0;
}

void convC(char * str) {
	int lIndF = MAX - 1;
	int lIndO = strlen(str);

	if (lIndO > ((lIndF - 1) / 2)) {
		lIndF = lIndO * 2;
		str = (char *) realloc(str, lIndO * 2 + 1);
	}

	str[lIndF--] = '\0';
	lIndO--;

	for ( ; lIndO >= 0; lIndO--) {
		int freq = 1;
		while (lIndO >= 1 && str[lIndO] == str[lIndO - 1]) {
			lIndO--;
			freq++;
		}
//		if (lIndO == 0 && str[lIndO] == str[lIndO + 1]) {
//			freq++;
//		}
		//		printf("at str[%d] = %c, freq = %d\n", lIndO + 1, str[lIndO + 1], freq);

		while (freq > 0) {
			char dig = freq % 10;
			freq /= 10;
			str[lIndF--] = dig + '0';
		}
		str[lIndF--] = str[lIndO];
	}

	lIndF++;
	printf("C   string:\t%s\n", (str + lIndF));
}

void convCPP(string str) {
	int lIndO = str.length();
	int lIndF = str.capacity();

	if (lIndO > ((lIndF - 1) / 2)) {
		lIndF = lIndO * 2;
		str.resize(lIndF * 2 + 1);
	}

	lIndO--;
	lIndF--;

	for (; lIndO >= 0; lIndO--) {
		int freq = 1;
		while (lIndO >= 1 && str[lIndO] == str.at(lIndO - 1)) {
			lIndO--;
			freq++;
		}

		while (freq > 0) {
			char dig = freq % 10;
			freq /= 10;
			str[lIndF--] = dig + '0';
		}
		str[lIndF--] = str[lIndO];
	}

//	cout << str << endl;
//	cout << "size = " << str.size() << "\tcap = " << str.capacity() << "\tlIndF = " << lIndF << endl;

	str = str.substr(lIndF + 1);
	printf("C++ string:\t%s\n", str.c_str());
}
