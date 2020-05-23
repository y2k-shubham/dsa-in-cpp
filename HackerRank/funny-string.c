#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LEN 10001

int main() {
    int T;
    int i;
    char ch;
    char S[MAX_LEN];
    int len;

    scanf("%d", &T);
    scanf("%c", &ch);
    while (T-- > 0) {
        scanf ("%[^\n]%*c", S);
        len = strlen(S);

        if (len == 2) {
            printf("Funny\n");
            continue;
        }

        for (i = 1; i <= (len / 2 + 1); i++) {
            //printf("orig string |%c - %c| = %d\n", S[i], S[i - 1], abs(S[i] - S[i - 1]));
            //printf("rev  string |%c - %c| = %d\n\n", S[len - i], S[len - i - 1], abs(S[len - i] - S[len - i - 1]));

            if (abs(S[i] - S[i - 1]) != abs(S[len - i] - S[len - i - 1])) {
                break;
            }
        }

        if (i > (len / 2 + 1)) {
            printf("Funny\n");
        } else {
            printf("Not Funny\n");
        }
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
