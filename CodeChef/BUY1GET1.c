#include <stdio.h>
#include <math.h>
#include <string.h>

void inputAndProcess(int [], int);
void output(int [], int);

int main() {
    int T;

    scanf("%d", &T);
    int result[T];

    inputAndProcess(result, T);
    output(result, T);

    return 0;
}

void inputAndProcess(int result[], int T) {
    int freq[125];
    char S[210];
    int i;
    int j;

    int len;

    for (i = 0; i < T; i++) {
        // accept the input string
        scanf("%s", S);

        // initialize variables
        memset(freq, 0, (123 * sizeof(int)));
        len = strlen(S);
        result[i] = 0;

        // counting frequency of each character A - Z and a - z in the string
        for (j = 0; j < len; j++) {
            freq[S[j]]++;
        }

        // adding items for characters A - Z
        for (j = 65; j <= 90; j++) {
            result[i] += (int) ceil(freq[j] / 2.0f);
        }

        // adding items for characters a - z
        for (j = 97; j <= 122; j++) {
            result[i] += (int) ceil(freq[j] / 2.0f);
        }
    }
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
