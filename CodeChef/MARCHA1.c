#include <stdio.h>
#include <string.h>

void inputAndProcess(int [], int);
int hasSubset(int [], int, int, int, int, int);
void output(int [], char * [], int);

FILE * myFile;

int main() {
    int t;
    char * result[] = {"No", "Yes"};

    scanf("%d", &t);
    int answer[t];

    //myFile = fopen("myFile.txt", "w");
    inputAndProcess(answer, t);
    output(answer, result, t);
    //fclose(myFile);

    return 0;
}

void inputAndProcess(int answer[], int t) {
    int i;
    int j;
    int n;
    int m;
    int max;
    int sum;
    int freq[1001];
    int value;

    for (i = 0; i < t; i++) {
        scanf("%d %d", &n, &m);

        sum = 0;
        max = 0;
        memset(freq, 0, (1001   * sizeof(int)));

        for (j = 1; j <= n; j++) {
            scanf("%d", &value);

            freq[value]++;
            sum += value;
            max = (value > max) ? value : max;
        }

        if (m < sum) {
            answer[i] = hasSubset(freq, 1, max, 0, sum, m);
        } else if (m == sum) {
            answer[i] = 1;
        } else {
            answer[i] = 0;
        }
    }
}

int hasSubset(int freq[], int crrIndex, int maxIndex, int crrSum, int possblSum, int reqSum) {
    //fprintf(myFile, "\n\n===\nInside hasSubset(freq[], %d, %d, %d, %d)\n", crrIndex, maxIndex, crrSum, reqSum);
    //if (crrSum > 1000) {
    //    fprintf(myFile, "Sum too large, terminated\n===\n\n");
    //    return 1;
    //}
    if (crrSum == reqSum) {
        //fprintf(myFile, "required sum achieved, returned true\n===\n\n");
        return 1;
    } else if ((crrIndex > maxIndex) || (possblSum < reqSum) || (crrSum > reqSum)) {
        //fprintf(myFile, "no match found, returned false\n===\n\n");
        return 0;
    } else {
        int i;

        for (i = 0; i <= freq[crrIndex]; i++) {
            //fprintf(myFile, "    In hasSubset(freq[], %d, %d, %d, %d)\n", crrIndex, maxIndex, crrSum, reqSum);
            //fprintf(myFile, "For i = %d\nfreq[%d] = %d\nTrying hasSubset(freq[], %d, %d, %d, %d)\n", i, crrIndex, freq[crrIndex], (crrIndex + 1), maxIndex, (crrSum + (i * crrIndex)), reqSum);
            if (hasSubset(freq, (crrIndex + 1), maxIndex, (crrSum + (i * crrIndex)), (possblSum - ((freq[i] - i) * crrIndex)), reqSum)) {
                //fprintf(myFile, "Match found, returned true\n===\n\n");
                return 1;
            } else {
                //fprintf(myFile, "Match not found for hasSubset(freq[], %d, %d, %d, %d)\n", (crrIndex + 1), maxIndex, (crrSum + (i * crrIndex)), reqSum);
            }
        }

        //fprintf(myFile, "no match found, returned false\n===\n\n");
        return 0;
    }
}

void output(int answer[], char * result[], int t) {
    int i;

    for (i = 0; i < t; i++) {
        printf("%s\n", result[answer[i]]);
    }
}
