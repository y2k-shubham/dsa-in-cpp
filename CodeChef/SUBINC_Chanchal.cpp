#include<bits/stdc++.h>

using namespace std;

long long countIncSub(long long a[],long long n) {
    long long ctr = 0;
    int index = 0;
    long long in;
    long long ctr1;

    ctr1 = 0;
    for(int i = index; i <n; i++)
    {
        ctr = 1;
        in = a[i];
        printf("outer loop starts at arr[%d] = %d, ctr = %d\n", i, a[i], ctr);
        for(int j = i + 1; j < n; j++)
        {
            if(in <= a[j])
            {
                in = a[j];
                ctr++;
            }

            else{
                    printf("inner loop breaks at arr[%d] = %d, ctr = %d\n\n", j, a[j], ctr);
                    i = j - 1;
                    break;
                    }
        }
        ctr1 += (ctr * (ctr + 1)) / 2;
    }
    return ctr1;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        long long n;
        cin>>n;
        long long a[n];
        for(long long i = 0; i < n; i++)
            scanf("%lld",&a[i]);

        long long res = countIncSub(a,n);
        cout<<res<<endl;
    }

    return 0;
}
