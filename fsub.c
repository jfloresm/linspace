#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 

int in(int *a, int b, int n){
	int i;
	int k;

	k = 0;

	for(i = 0; i<n; i++){
		if(a[i] == b){
			k = 1;
		}
	}

	return(k);

}
		

int add(int *a, int n){
	
	int i,k;

	k = 0;


	for(i = 0; i <n+1; i++){
		k += a[i];
	}

	return(k);
}
			
int equal(long int ** a, long int **b,int n,int m){
	int i,j;
	for(i = 0; i<n; i++){
		for(j = 0; j<n; j++){
			a[i][j] = b[i][j];
		}
	}

	return(0);
}


int zero(int *a, int n){
	int i;

	for(i = 0; i<n; i++){
		a[i] = 0;
	}

	return(0);

}

int fill(int *a, int n){
	int i;

	for(i = 0; i<n; i++){
		a[i] = -1;
	}

	return(0);

}


int rem(int a){

	int k,y;

	if(a %64 == 0){
		k = 65;
	}

	else{
		y = (a/64) - 1;
		k = a - y*64;
	}
		
	return(k);

}

int empty(long int ** a, int n,int m){
	int i, j,l,k;
	
	l = -1;
	k = 0;	

	for(i = 0; i < n; i++){
		if(l == 1){
			break;
		}

		for(j = 0; j<m; j++){
			if(a[i][j] != 0){
				k = 1;
				l = 1;
				break;
			}
		}
	}

	return(k);
}
				


int main(){

int i,m3,j,k,l,m,n,m1,n1,m2,n2,a,b,u1,u2,u3,u4,u5,sum, test, ver,flag,z;
	double r;
	FILE *file;
	int *v1;
	int *v2;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	long int b1,b2;
	int count;
	int points, lines;
	int sol[n1];
	int stack[n1];
	int ts,ch;
	
/////////////////////////////////////////////////////////////////////////////////////
//
//Read projective planes in Moorhouse format and store it in nauty format in plane
//
/////////////////////////////////////////////////////////////////////////////////////	

	file = fopen("/home/jfloresm/Documents/Research/linspace/25s1.txt", "r");	
	if(file == NULL){
		printf("EXIT_FAILURE \n");
	}

	a = 25;			//order of plane

	l = a*a+a+1;		//number of points/lines

	b = a+1;		//number of points on each line (and lines through each point)

	n = 2*l;

	m = SETWORDSNEEDED(n);

	//printf("m = %d, n = %d, l = %d,a = %d, b = %d \n", m,n,l,a,b);

	int *array = (int *)malloc(l*sizeof(int));

	long int *plane = (long int *)malloc(m*n*sizeof(long int));

	EMPTYGRAPH(plane,m,n);


	for(j = 0; j<l; j++){
		for(i = 0; i < b; i++){
                        if(fscanf(file, "%d",&array[i])){
				//printf("%d %d %d \n", i, array[i],j);
                                ADDONEEDGE(plane, j, array[i] + l,m);
				//ADDONEEDGE(plane, l+array[i], j,m);
                        }

			else{
				break;
			}
               }
	}

	fclose(file);
       
	free(array);



/////////////////////////////////////////////////////////////////////////////////////
//
//Algorithm to find if graph is isomorphic to a subgraph
//
/////////////////////////////////////////////////////////////////////////////////////

n1 = 12;							//Number of vertices in BPG

m1 = SETWORDSNEEDED(n1);			

long int** ng = (long int **)malloc(29*sizeof(long int*));	// Holds PLS

for(i = 0; i < 29; i++){
	ng[i] = (long int *)malloc(m1*n1*sizeof(long int));
	}

long int* ng2 = (long int *)malloc(m1*n1*sizeof(long int));	// Copy of PLS

int * point = (int *)malloc(m1*n1*sizeof(int));			// Holds row of plane

//////////////////////////////
//Construct temporary graph
/////////////////////////////


n2 = 31;

m2 = SETWORDSNEEDED(n2);

long int *temp = (long int *)malloc(m2*n2*sizeof(long int));

	EMPTYGRAPH(temp,m2,n2);
	
	for(i = 13; i<25; i++){
		ADDONEEDGE(temp, 0, i, m2);
	}

	for(i = 1; i<13;i++){
		ADDONEEDGE(temp, i, i+12,m2); 
	}

	for(i = 1; i<7; i++){
		ADDONEEDGE(temp,2*i-1, i+24,m2);
		ADDONEEDGE(temp, 2*i, i+24, m2);
	}
	
///////////////////////////////////////////////////////////////////////////////////
//For each PLS, find number of points and lines (PLS in SMO), then apply algorithm
///////////////////////////////////////////////////////////////////////////////////


/*file = fopen("/run/media/jfloresm/TOSHIBA EXT/p12.txt", "r");	
	if(file == NULL){
		printf("EXIT_FAILURE \n");
	}
*/



	long int ** tset = (long int **)malloc(n1*sizeof(long int *));		// hold domain of each variable

	for(i = 0; i < n1; i++){						 //Move this inside the for loop if I need more memory
		tset[i] = (long int *)malloc(m2*sizeof(long int));
	}
		
	long int ** tsetcop = (long int **)malloc(n1*sizeof(long int *));	// hold domain of each variable

	for(i = 0; i < n1; i++){ 						//Move this inside the for loop if I need more memory
		tsetcop[i] = (long int *)malloc(m2*sizeof(long int));
	}

	long int ** untried = (long int **)malloc(n1*sizeof(long int *));	// hold domain of each variable

	for(i = 0; i < n1; i++){ 						//Move this inside the for loop if I need more memory
		untried[i] = (long int *)malloc(m2*sizeof(long int));
	}


file = fopen("/home/jfloresm/Documents/Research/linspace/p12.txt", "r");	
	if(file == NULL){
		printf("EXIT_FAILURE \n");
	}

//Loop through all PLS with n1 vertices

ts = 0;

while ((read = getline(&line, &len, file)) != -1){
	stringtograph(line, ng[ts],m1);
	ts+= 1;
}

 fclose(file);
//Find number of points and lines in PLS	

	ch = 1;				//PLS to check

	for(i = 0; i < m1*n1; i++){
		ng2[i] = ng[ch][i];
	}

	zero(point, m1*n1);


	for(j = 0; j <m1*n1; j++){
		TAKEBIT(point[j], ng2[j]);
		}
	
	k = 0;

	for(i = 0; i < n1; i++){
	
		for( j =0; j < i+1; j++){	
		
			if(point[j] <= i){

				points = i;
				lines  = n1 - i;
				k = 1;
				break;

			}
		}

		if(k == 1){
			break;
		}

	}

	
// Maybe tests for bipartitness (not needed as of now)

//	if(twocolouring(ng,test,m1,n1)){
//		printf("Bipartite \n");
//	}

/////////////////////////////
//Subgraph Isomorphism Test
/////////////////////////////

//First, choose domains for variables (for now, simply point set to point set and same for lines)

	for(j = 0; j<n1; j++){
		EMPTYSET(tset[j], m2);
	}

	for(j = 0; j< points; j++){
		for(i = 0; i<13; i++){
			ADDELEMENT(tset[j], i);
		}
	}

	for(j = points; j<n1; j++){
		for(i = 13; i <n2; i++){
			ADDELEMENT(tset[j],i);
		}
	}

	k = 0;
	
	equal(untried, tset, n1, m2);

	fill(stack, n1);

while(k <= n1-1 && empty(untried,n1,m2) == 1){ 
	if(untried != 0){											//uninitiated values in domain k
		equal(tsetcop, tset, n1,m2);									//copy of domains						
		ver = FIRSTBIT(untried[k][0]);									//find uninitiated value						
		DELELEMENT(untried[k], ver);									//delete value as to not revisit
		stack[k] = ver;											// set variable to uninitated value
														
			for(i = k+1; i <n1; i++){								// check next domains for reduction
				for(j = -1; (j = nextelement(tset[i],m2,j))>= 0;){				// check values in domain i
					if(ISELEMENT(ng[ch], k*64 + i) && !ISELEMENT(temp, ver*64 +j)){		//binary constraint (adjacency)
						DELELEMENT(tset[i], j);
					}
	
	
					if(in(stack, j, n1)==1){
						DELELEMENT(tset[i],j);
					}
				}

				

				if(tset[i] == 0){
					stack[k] = -1;
					equal(tset,tsetcop,n1,m2);									//by connectedness
					flag = -1;
					break;						
				}
			}
			
		if(flag!= -1 && k == (n1-1)){
			printf("embedable \n");
			break;
		}
	
		else if(flag != -1 && k<(n1-1)){
			k+=1;
		}
		
	//	DELELEMENT(tset[k], ver);
	}

	else{
		k -= 1;
	}


}

//}	

//fclose(file);

/////////////////////////////////////////////////////////////////////////////////////
//
//For testing purposes, specifically, usage of nauty sets
//
/////////////////////////////////////////////////////////////////////////////////////
/*
	set padd[2];

	EMPTYSET(padd,1);

	ADDELEMENT(padd,0);
	ADDELEMENT(padd,1);
	ADDELEMENT(padd,68);


	for(i = 0; i<63; i++){
		if(ISELEMENT(padd,i)){
			printf("is \n");
		}
	}



	if(ISELEMENT(padd,68)){
		printf("yes\n");
	}

	if(!ISELEMENT(padd,22)){
		printf("no\n");
	}
*/



/////////////////////////////////////////////////////////////////////////////////////
//
//Construct a subgraph... HAVE TO FINISH
//
/////////////////////////////////////////////////////////////////////////////////////	
/*
	u1 = 4;//#of points
	u2 = 5;//#of lines

	n1 = u1+u2;
	
	m1 = SETWORDSNEEDED(n1); 
	
	int **inc  = (int **)malloc(4*sizeof(int *));

	for(i = 0; i <4; i++){

		inc[i] = (int *)malloc(n1*sizeof(int));
	}

	for(i = 0; i<4; i++){
		zero(inc[i], n1);
	}

	u3 = (rand() % l);

	u4 = rem(u3);
	
	k = 0;


	for(i = 0; i<n1; i++){
		if(u4 == 0){
			b1 = (plane[i*m1]>>63);
			if(b1 & 1){
				inc[k][i] = 1;
			}
		}

		else{
			u5 = (a/64)-1;
		
			b1 = (plane[i*m1 + u5]>> (63-u4));

			if(b1 & 1){
				inc[k][i] = 1;
			}
		}
	}

	k = 1; 	 
	
//do same now that we have info from previous ones 


	for(j = 1; j<4; j++){
		
		
	
	

		k+=1;

	}
	


}

*/




return 0;

}
