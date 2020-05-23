#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FREQ 123

void findPalind(char *);

void findPalind(char *arr)
{
    int freq[MAX_FREQ];
    int flag;
    int i;
    int len;
    int oddCtr;

    memset(freq, 0, MAX_FREQ * sizeof(int));
    flag = 0;
    oddCtr = 0;
    len = strlen(arr);

    for (i = 0; i < len; i++) {
        //printf("char %c\t", arr[i]);
        if (++freq[arr[i]] & 1) {
            oddCtr++;
        } else {
            oddCtr--;
        }
        //printf("freq[%c] = %d\toddCtr = %d\n", arr[i], freq[arr[i]], oddCtr);
    }

    if (oddCtr > 1) {
        flag = 1;
    }

    // Find the required answer here. Print Yes or No at the end of this function depending on your inspection of the string
    if (flag==0)
        printf("YES\n");
    else
        printf("NO\n");
}
int main() {

    char arr[100001];
    scanf("%s",arr);
    findPalind(arr);
    return 0;
}
