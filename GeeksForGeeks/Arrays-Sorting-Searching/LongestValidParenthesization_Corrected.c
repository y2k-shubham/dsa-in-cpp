// http://www.geeksforgeeks.org/length-of-the-longest-valid-substring/
// Time  Complexity: O(3n) = O(n)
// Space Complexity: O(n)

/*
Explaination:
Take an auxillary integer array initialized with zero.
Input:

Scan the input string and keep count of
no of opening and closing braces seen so far as cOpen and cClose. Do the following
String:		( ) ( ( ) ) ) ) )
aux-array:	0 0 0 0 0 0 0 0 0

1. if current character of string is (, then increment cOpen
2. if current character of string is ), then increment cClose
		now if cClose <= cOpen => means we are still seeing a valid sequence
				then store 2 in same position of auxillary array
				(this signifies that at this point, the longest valid sequence that ends here will be
				at least of length 2)

after above steps we get the following
String:		( ) ( ( ) ) ) ) )
aux-array:	0 2 0 0 2 2 0 0 0

By observation, we can see that we need to spread out the 2's backwards (right to left) as 1's to mark
all regions of valid parenthesization. for this, we scan auxilary array backwards and whenever we encounter
a 2, we add it to a limit variable and then mark limit places (including current place) as 1. in the
any more 2's encountered are also added to limit.

after above, we get following
String:		( ) ( ( ) ) ) ) )
aux-array:	1 1 1 1 1 1 0 0 0

now all we need to do is make a scan of auxilary array from left and find longest sequence of consecutive 1s

*/

#include <stdio.h>
#include <string.h>

#define MAX 100
#define max(a, b) ((a > b) ? a : b)

/*
Input:
(())()))((()(())(()()))))((())
Output: 16

Input:
((()
Output: 2

Input:
)()())
Output: 4

Input:
()(()))))
Output: 6
*/

int main() {
	char arr[MAX];
	int arrLen;
	int open;
	int close;
	int crrLen;
	int maxLen;
	int endInd;
	int maxStrtInd;
	int i;
	int j;
	int k;
	int arr2[MAX] = {0};
	int limit;

	printf("\nEnter parenthesization string:\t");
	scanf("%s", arr);

	arrLen = strlen(arr);
	maxLen = 0;
	crrLen = 0;
	open = 0;
	close = 0;

	for (i = 0; i < arrLen; i++) {
		if (arr[i] == '(') {
			open++;
		} else {
			close++;

			if (close <= open) {
				arr2[i] = 2;
			} else {
				open = 0;
				close = 0;
			}
		}
	}

	for (i = arrLen - 1; i >= 0; i--) {
		limit = arr2[i];
		//		printf("at i = %d, limit = %d\n", i, limit);
		if (limit > 0) {
			arr2[i--] = 1;
			limit--;
			for (k = 1; i >= 0 && k <= limit; k++, i--) {
				if (arr2[i] > 0) {
					limit += arr2[i];
//					printf("at i = %d\t2 added, k = %d and new limit = %d\n", i, k, limit);
				}
				arr2[i] = 1;
			}
			i++;
		}
	}


	maxLen = -1;
	for (i = 0; i < arrLen; i++) {
		crrLen = 0;
		if (arr2[i] == 1) {
			for (; arr2[i] == 1; i++) {
				crrLen++;
			}
			i--;
			if (crrLen > maxLen) {
				maxLen = crrLen;
				maxStrtInd = i - maxLen + 1;
			}
		}
	}

	//maxStrtInd = endInd - maxLen + 1;

	printf("The longest valid sequence is:\t");
	for (i = 0, j = 0; j < maxLen - 1; i++) {
		if (j > 0) {
			j++;
		}

		if (i != maxStrtInd) {
			printf(" ");
		} else {
			printf("^");
			j = 1;
		}
	}
	printf("^\n                              \t");
	for (i = 0; i < maxStrtInd; i++) {
		printf(" ");
	}
	for (i = maxStrtInd, j = 1; j <= maxLen; i++, j++) {
		printf("%c", arr[i]);
	}
	printf("\nLength of longest sequence is:\t%d\n", maxLen);

	return 0;
}
