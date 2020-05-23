// STL String class URL: http://www.cprogramming.com/tutorial/string.html
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

// URL: http://www.geeksforgeeks.org/print-concatenation-of-zig-zag-string-form-in-n-rows/

using namespace std;

void genZigZagPattern(string, int, char *, int *, int);
void showZigZagPattern(char *, int *, int, int);

int main() {
	int n;
	string str;
	int len;

	printf("Enter a string:\t");
	cin >> str;
	len = str.length();
    cout << "Length of string is " << len << endl;

	cout << "Enter the no of rows for zig-zag pattern:\t";
	cin >> n;

	char zig_zag[n][len];
	int top[n];

	genZigZagPattern(str, len, &zig_zag[0][0], &top[0], n);
	showZigZagPattern(&zig_zag[0][0], &top[0], len, n);

	//cout << "The entered string is:\t" << str << endl;

	return 0;
}

void genZigZagPattern(string str, int len, char * zig_zag, int * top, int n) {
	int i;
	int row;
	int colCount;

	memset(top, 0, n * sizeof(int));
	colCount = len;

	for (i = 0, row = -2; i < len;) {
		for (row += 2; (i < len) && (row < n); row++, i++) {
            //printf("down : char %c added to row %d\n", str[i], row);
			* (zig_zag + (row * colCount) + top[row]) = str[i];
			top[row]++;
		}

		for (row -= 2; (i < len) && (row >= 0); row--, i++) {
            //printf("up   : char %c added to row %d\n", str[i], row);
			* (zig_zag + (row * colCount) + top[row]) = str[i];
			top[row]++;
		}
		//printf("\n");
	}
}

void showZigZagPattern(char * zig_zag, int * top, int len, int n) {
	int i;
	int j;
	int colCount;

	colCount = len;

	printf("\nThe string in zig-zag pattern would be:-\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < top[i]; j++) {
			putchar(* (zig_zag + (i * colCount) + j));
		}
		putchar(' ');
	}
	printf("\n");
}
