#include <stdio.h>

int main(){

unsigned int a = 5;

int i,j,k;


for(i = 63; i >=0; i--){
	k= a >> i;

	if(k&1){
		printf("1");
	}

	else{
		printf("0");
	}
}

printf("\n");

return 0;

}
