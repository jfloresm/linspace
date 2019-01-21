#include <stdio.h>

int notin(int *a,int b,int n){

	int i,k;

	k = 1;

	for(i = 0; i<n; i++){
		if(b == a[i]){
			k=0;
			break;
		}

	}

	return(k);

}

int main(){

int i,j,k,n;

int b[3];
int c[3];

b[0] = 0;
c[0] = 1;

b[0] = 2;
c[0] = 2;

b[0] = 3;
c[0] = 3;


n = 3;

k=0;

for(i = 0; i<n; i++){
	if(notin(c,b[i],n) == 1){
		k+=1;
	}
}

printf("%d \n", k);

return 0;

}
