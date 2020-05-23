#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <strings.h>

int sigmaN(int);
int countIncSub(int [], int);

int countIncSub(int a[], int n)
{
    int curr;
    int prev;
    int crrLen;
    int count;
    int i;

    prev = -1;
    crrLen = 0;
    count = 0;

    for(i = 0; i <n; i++)
    {
        curr = a[i];
        //printf("prev = %d\tcurr = %d\tcrrLen = %d\t", prev, curr, crrLen);

        if (curr >= prev) {
            //printf("if\t");
            crrLen++;
            prev = curr;
        } else {
            //printf("else\t");
            count += sigmaN(crrLen);
            //printf("added %d\t", sigmaN(crrLen));
            prev = -1;
            crrLen = 0;
            i--;
        }
        //printf("prev = %d\tcrrLen = %d\n", prev, crrLen);
    }
    count += sigmaN(crrLen);

    return count;
}

int sigmaN(int n) {
    int i;
    int sum;

    sum = 0;
    for (i = 1; i <= n; i++) {
        sum += i;
    }

    return sum;
}

int main()
{
    int t;
    int i;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        int a[n];
        for(i = 0; i < n; i++)
            scanf("%d",&a[i]);

        int res = countIncSub(a,n);
        printf("%d\n", res);
    }

    return 0;
}
