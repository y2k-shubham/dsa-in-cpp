#include <stdio.h>
#include <string.h>

#define MAX 10000
#define LEN 123

void findFreqMap(char [MAX], int, int, int [LEN]);
int compareFreqMaps(int [LEN], int [LEN]);
void showFreqMap(int [LEN]);

int main() {
    char str[MAX];
    int len;
    int freq_1[LEN] = {0};
    int freq_2[LEN] = {0};

    scanf("%s", str);
    len = strlen(str);

    if (len % 2) {
        findFreqMap(str, 0, len / 2, freq_1);
        findFreqMap(str, len / 2, len - 1, freq_2);
    } else {
        findFreqMap(str, 0, len / 2 - 1, freq_1);
        findFreqMap(str, len / 2 + 1, len - 1, freq_2);
    }

    showFreqMap(freq_1);
    showFreqMap(freq_2);

    if (compareFreqMaps(freq_1, freq_2)) {
        printf("First half is not anagram of 2nd half\n");
    } else {
        printf("First half is anagram of 2nd half\n");
    }

    return 0;
}

void findFreqMap(char str[MAX], int lo, int hi, int freq[LEN]) {
    int i;

    for (i = lo; i <= hi; i++) {
        freq[str[i]]++;
    }
}

int compareFreqMaps(int freq_1[LEN], int freq_2[LEN]) {
    int i;

    for (i = 0; i < LEN; i++) {
        if (freq_1[i] != freq_2[i]) {
            return 1;
        }
    }

    return 0;
}

void showFreqMap(int arr[LEN]) {
    int i;

    printf("\nThe freq map is:-\n");
    for (i = 0; i < LEN; i++) {
        if (arr[i]) {
            printf("f[%c] = %d\n", ((char) i), arr[i]);
        }
    }
}
