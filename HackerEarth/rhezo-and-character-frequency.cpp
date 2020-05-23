// https://www.hackerearth.com/practice/basic-programming/implementation/basics-of-implementation/practice-problems/algorithm/rhezo-and-character-frequency-3/

/*
fpgpappgp
p
4

fppapppgp
p
4

asdnajsdnasj
d
3
Ans: 9

hmhxfp
r
4
Ans: 6

mrzhyfyfvjveovfaiuukuvklambgbgypaywydwdbgafwvmxegrobmboonrxqyvfyvdwzzbchbjexvbbcsrfgstvhluxjpcjlhhmhioo
j
54
Ans: 103

lynapkutkbuftxjqgocvqfqegddtewgswvslhohrpbykaiagyeboktusyzndvvvsqpfxdmqunp
e
67
Ans: 74

xlvthuqvsvbgzoymnlqlhimmobwclkrivodeitaarbjsrjeewvsdfgruhnyv
x
44
Ans: 43

isqjqsnmfqvkpdesgbiwhffesurstpwdjomzhzlmrjyimcbuglrnswtntlhocfrlugmbhxpbiojvsmpyainshjfawmqyujlorxr
z
22
Ans: 56

aquwwdjirihovsvcirxegxyaqrsqwpjwfdudidlbmvqhpnlygkcmjbpzsjrpyanffijnlurzphjfwwdchhrqigsdrjuqmhvrpehdbycqhnxfkchtkajuidxanrqbzlsqsbttbylkljpxnzqxbaukdrkslatmnocfrwavumfhxxfkyvkzxejdvvxivtulhxsattvpfdwecdoazybycnbaibieudrdajdvcbmjgknkoempcnnharhjsrpougrwrwtwzfhfqxrgbdvfrkmtbvcvnrljzcgrbbnahuiztzfudcawmopqms
n
30
Ans: -1
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void findZ(string, int, int, char, vector <int>&, int&);
void showVec(string, int, char, vector <int>);
void findInd(string, int, int, char, vector <int>, int);

int main() {
	string S;
	int len;
	int P;
	char C;
	int Z;

	cout << "Enter string:\t";
	cin >> S;

	len = S.length();
	S = '\0' + S;
	vector <int> CFreqCum(len + 1);

	cout << "Enter char:\t";
	getchar();
	C = getc(stdin);

	cout << "Enter window size:\t";
	cin >> P;

	findZ(S, len, P, C, CFreqCum, Z);
	showVec(S, len, C, CFreqCum);
	printf("Max freq of %c in window size of %d is %d\n", C, P, Z);

	findInd(S, len, P, C, CFreqCum, Z);

	return 0;
}

void findZ(string S, int len, int P, char C, vector <int>& CFreqCum, int& Z) {
	CFreqCum[0] = 0;
	Z = -1;

	for (int i = 1; i <= len; i++) {
		CFreqCum[i] = CFreqCum[i - 1];
		if (S[i] == C) {
			CFreqCum[i]++;
		}
		if (i >= P && CFreqCum[i] - CFreqCum[i - P] > Z) {
			Z = CFreqCum[i] - CFreqCum[i - P];
		}
	}
}

void showVec(string S, int len, char C, vector <int> CFreqCum) {
	printf("\nCumulative Frequency Vector is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Str:\t";
	for (int i = 0; i <= len; i++) {
		printf("%c\t", S[i]);
	}
	cout << endl;

	cout << "CFreq:\t";
	for (int i = 0; i <= len; i++) {
		printf("%d\t", CFreqCum[i]);
	}
	cout << endl;
}

void findInd(string S, int len, int P, char C, vector <int> CFreqCum, int Z) {
//	printf("len = %d\n", len);
	if (Z == -1) {
		cout << len << endl;
		return;
	}
	for (int i = len; i >= P; i--) {
		if ((CFreqCum[i] - CFreqCum[i - P]) == Z) {
			if (S[i] != C) {
				if (S[i - P + 1] != C) {
					printf("\nCharacter %c should be inserted in place of S[%d] = %c\n", C, i, S[i]);
//					printf("here1\n");
					return;
				} else {
					printf("\nCharacter %c should be inserted in place of S[%d] = %c\n", C, (i - 1), S[i]);
//					printf("here2\n");
					return;
				}
			}
		}
	}
	printf("\nThere isn't an index with given constraints\n");
}

