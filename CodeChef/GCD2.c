//source limit 1000 bytes
#include <stdio.h>
#include <string.h>
void iap(char[][260],int[],int);
int gfr(char[],int);
int GCD(int,int);
void out(char[][260],int[],int);
void iap(char B[][260],int rs[],int T) {
	int i,A,rm;
	for(i=0;i<T;i++){
		scanf("%d",&A);
		scanf("%s",&B[i]);
		if(A>1){
			rm=gfr(B[i],A);
			rs[i]=GCD(A,rm);
		}else if(A==1){
			rs[i]=1;
		}else{
			rs[i]=-999;
		}
	}
}
int gfr(char B[],int A) {
	int i,len,d;
	len=strlen(B);
	d=0;
	for(i=0;i<len;){
		while((i<len)&&(d<A)){
			d=(d*10)+(B[i++]-'0');
		}
		if(i<len){
			d%=A;
		}else{
			break;
		}
	}
	return d;
}
int GCD(int B,int A){
	if(A==0){
		return B;
	}else{
		return GCD(A,(B%A));
	}
}
void out(char B[][260],int rs[],int T) {
	int i;
	for(i=0;i<T;i++){
		if(rs[i]>0){
			printf("%d\n",rs[i]);
		}else{
			printf("%s\n",B[i]);
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	int rs[T];
	char B[T][260];
	iap(B,rs,T);
	out(B,rs,T);
	return 0;
}
