#include<stdio.h>
#include<string.h>
int main(){
int t,x,y,k;
char string[27],reverse[27];
strcpy(string,"abcdefghijklmnopqrstuvwxyz");
strcpy(reverse,"zyxwvutsrqponmlkjihgfedcba");
scanf("%d",&t);
while(t--){
scanf("%d",&k);
x=k/25, y=k%25;
if(y){while(y>=0) printf("%c",string[y--]);}
while(x--) printf("%s",reverse);
printf("\n");
}
return 0;
}
