#include <stdio.h>

int main(){


int n = 2;

int i,j,k,l;

char num[3];

//itoa(n,num,10);

FILE *file;

//printf("%s \n", num);
	

switch(n){
	case 2:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace2.txt","r");
		//printf("2\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;

	case 3:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace3.txt","r");
		//printf("2\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	
	case 4:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace4.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	case 5:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace5.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;

	case 6:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace6.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
}

for(i = 0; i < 5; i++){
	if(i == 2){
		continue;
	}	
	for(j = 0; j<7; j++){
		if(j == 3){
			continue;
		}
		else{
			printf("i = %d, j = %d \n", i,j);
		}
	}
}



return 0;

}
