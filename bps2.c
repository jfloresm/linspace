#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 

/*

1. Need fix so that if two points(lines) intersect in a line(point) already in the set, that combination is not used again
(as of now it just searches two new points(lines) at random.






*/

void meet(long int *g, int x, int y, int m){

		

}

void join(long int *g, int x, int y, int m){


}

int first(int *a, int n){

	int i,k,l,j;
	l = 0;
	k = 0;

	for(i = 0; i<n; i++){
		if(a[i] == -1){
			k = i;
			l = 1;
			break;
		}

	}

	if(l == 1){
		return(k);
	}

	else{

		return(n);
	}
}
		
		

/////////////////////////////////////////////////////////////////////////////////////
//
//Returns 1 if integer b is in array a. 0 otherwise.
//
/////////////////////////////////////////////////////////////////////////////////////

int in(int *a, int b, int n){
	int i;
	int k;

	k = 0;

	for(i = 0; i<n; i++){
		if(a[i] == b){
			k = 1;
			break;
		}
	}

	return(k);

}

/////////////////////////////////////////////////////////////////////////////////////
//
//Returns position of element in array.
//
/////////////////////////////////////////////////////////////////////////////////////

int posit(int *a, int b, int n){
	int i;

	for(i = 0; i<n; i++){
		if(a[i] == b){
			return(i);
			break;
		}
	}


}


/////////////////////////////////////////////////////////////////////////////////////
//
//Adds the first n entries of array a and returns this number
//
/////////////////////////////////////////////////////////////////////////////////////
		

int add(int *a, int n){
	
	int i,k;

	k = 0;


	for(i = 0; i <n+1; i++){
		k += a[i];
	}

	return(k);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//Copies 1d array b into 1d array a
//
/////////////////////////////////////////////////////////////////////////////////////
			
int equalo(long int * a, long int *b,int n,int m){
	int i;
	for(i = 0; i<n*m; i++){
		
		a[i] = b[i];
		
	}

	return(0);
}



/////////////////////////////////////////////////////////////////////////////////////
//
//Copies 2d array b into 2d array a
//
/////////////////////////////////////////////////////////////////////////////////////
			
int equalt(long int ** a, long int **b,int n,int m){
	int i,j;
	for(i = 0; i<n; i++){
		for(j = 0; j<n; j++){
			a[i][j] = b[i][j];
		}
	}

	return(0);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//Sets the first n entries of array a to 0
//
/////////////////////////////////////////////////////////////////////////////////////

int zero(int *a, int n){
	int i;

	for(i = 0; i<n; i++){
		a[i] = 0;
	}

	return(0);

}

/////////////////////////////////////////////////////////////////////////////////////
//
//Sets the first n entries of array a to -1
//
/////////////////////////////////////////////////////////////////////////////////////

int fill(int *a, int n){
	int i;

	for(i = 0; i<n; i++){
		a[i] = -1;
	}

	return(0);

}

/////////////////////////////////////////////////////////////////////////////////////
//
//Finds the remainder after dividing a by 64
//
/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////
//
//Returns 1 if any entry of a[i] is nonzero. 0 otherwise.
//
/////////////////////////////////////////////////////////////////////////////////////

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
				
/////////////////////////////////////////////////////////////////////////////////////
//
//Returns a random number in the interval [lower, upper]
//
/////////////////////////////////////////////////////////////////////////////////////

int randint(int upper, int lower){

	int l,k;

	l = (upper - lower + 1);

	k = (rand() % l) + lower;

	return(k);

}

/////////////////////////////////////////////////////////////////////////////////////
//
//Factorial(n)
//
/////////////////////////////////////////////////////////////////////////////////////

int fact(int n){

	int i,k;

	k = 1;

	for(i = n; i>=1; i--){
		k*= i;
	}

	return(k);

}

/////////////////////////////////////////////////////////////////////////////////////
//
//nCr
//
/////////////////////////////////////////////////////////////////////////////////////

int comb(int n, int r){

	int k;

	k = fact(n)/(fact(r)*(fact(n-r)));

	return k;

}

/////////////////////////////////////////////////////////////////////////////////////
//
//function from 2 subset to position in array, n is the number of lines/points
//
/////////////////////////////////////////////////////////////////////////////////////

int dic(int n, int a, int b){

	int i,j,k, temp;
	
	if(a >= b+1){

		a = temp;
		a = b;
		b = temp;
	}

	j = 0;

	for(i = 0; i<a; i++){
		j+= n-i;
	}

	k = j+((b-a)+1);
		
	return(k);
	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//goes from bit to (point,point);
//
/////////////////////////////////////////////////////////////////////////////////////


void invdic(int n, int c,int h1, int h2){

	int i,j,k,m2;

	for(i = 0; i<n; i++){
		j+= n-i;
		
		if(j >= c){
			h1 = i;
			m2 = j-c;
			break;
		}
	}
	
	h2 = h1+ (n-h1) - m2-1;
	h2 = n-(m2+1);

			
}
	
	

int inter(long int * a, int m, int v1, int v2){

	int k;
	int r;

	for(k = 0; k<m; k++){
		if((a[v1*m+k] & a[v2*m+k]) != 0){					//since intersection occurs on 1 point/line
			r = FIRSTBIT((a[v1*m+k] & a[v2*m+k]))+64*k;
		}
	}
		
	return(r);
}



void main(){

int i,j,k,l,m,n,a,b,m1,n1,c1,c2,d1,d2,r,b1,b2,m2,n2,n3,m3,l1,l2,z1,z2,g1,g2;
	int v1,v2,v3,v4,v5,v6;
	FILE *file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	long int tempb;
	int *lset;					//to hold lines in configuration
	int *pset;					//to hold points in configuration
	int psp;					//points in linear space being found
	int psl;					//lines in linear space being found
	int snp;					//starting number of points in configuration
	int snl;					//starting number of lines in configuration
	
	//int count;
	//int points, lines;
	//int sol[n1];
	//int stack[n1];
	//int ts,ch;
	
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

	int *array = (int *)malloc(l*sizeof(int));					//Read Moorhouse file row by row

	long int *plane = (long int *)malloc(m*n*sizeof(long int));			//holds projective plane

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
// Instaniate values for PLS that will be checked and for constructed graph
//
/////////////////////////////////////////////////////////////////////////////////////
/*	
	n1 = 12;
	m1 = SETWORDSNEEDED(n1);
	
	long int *temp = (long int *)malloc(m1*n1*sizeof(long int));			//for constructed graph	

	EMPTYGRAPH(temp,m1,n1);
*/
/////////////////////////////////////////////////////////////////////////////////////
//
//Start with a quadrangle (of points) and build configuration from this 
//-In this case, start with 4 lines (no three collinear) and end up with at most (6 choose 2)+4
//lines after join and (4 choose 2) points after meet
/////////////////////////////////////////////////////////////////////////////////////

	snl = 4;									//# of lines of quadrangle
	snp = comb(snl,2);								//# of points after meet
	psl = comb(snp,2)+snl;								//#of lines after meet-join
	psp = snp;

	n2 = psp+psl;
	m2 = SETWORDSNEEDED(n2);
	
	long int *temp = (long int *)malloc(m2*n2*sizeof(long int));			//starting configuration	
				
	EMPTYGRAPH(temp,m2,n2);

	pset = (int *)malloc(psp*sizeof(int));			//contains points in graph

	lset = (int *)malloc(psl*sizeof(int));			// contains lines in graph
	
	fill(pset,psp);
	
	fill(lset,psl);

	int * conc = (int *)malloc(4*sizeof(int));		//to check for concurrence when bulding quadrangle

//Make sure to choose 4 starting lines no 3 concurrent

	c1 = 0;

	for(i = 0; i<4; i++){

		v1 = randint(2*l-1,l);

		while(in(lset,v1,c1)){	
			v1 = randint(2*l-1,l);						//make sure not to repeat line
		}

		if(i <= 1){
		
			lset[c1] = v1;

			c1+= 1;								//first line
		}

		else if(i==2){		

			lset[c1] = v1;
							//make sure no 3 lines are concurrent							
			conc[0] = inter(plane,m,lset[0],lset[1]);

			k = 1;

			for(j = 0; j<2; j++){
				conc[k] = inter(plane,m, lset[j], lset[2]);
				k+=1;
			}
							
			while(conc[2] == conc[0] || in(lset,v1,c1)){
				
				v1 = randint(2*l-1,l);
				
				lset[c1] = v1;
				
				k = 1;

				for(j = 0; j<2; j++){
					conc[k] = inter(plane,m, lset[j], lset[2]);
					k+=1;
				}						
			}
			
			c1+=1;
		}

		else if(i == 3){

			lset[c1] = v1;
							//make sure no 3 lines are concurrent						

			for(j = 0; j<3; j++){
				l = inter(plane,m, lset[j], lset[3]);
					if(l == conc[0] || l == conc[1] || l == conc[2]){
						k = -1;
						break;
					}
			}

			while(k == -1){

				k = 0; 			

				lset[c1] = v1;
							//make sure no 3 lines are concurrent						

				for(j = 0; j<3; j++){
					l = inter(plane,m, lset[j], lset[3]);
						if(l == conc[0] || l == conc[1] || l == conc[2]){
							k = -1;
							break;
						}
				}			

			}	
		}
	
	}
	
///////////////////////Meet operation////////////////////////////////////////////////////
	
	l1 = first(lset,psl);								// #(lines in lset) - 1

	for(i = 0; i<l1-1;i++){
		for(j = i+1; j<snl; j++){
			l = inter(plane,m, lset[i], lset[j]);

			if(in(pset,l,psp)){
				z1 = posit(pset,l,psp);
				ADDONEEDGE(temp,i,psl+z1,m2);
				ADDONEEDGE(temp,j,psl+z1,m2);
				
			}

			else{
				k = first(pset, psp);
				pset[k] = l; 
				ADDONEEDGE(temp,i,psl+k,m2);
				ADDONEEDGE(temp,j,psl+k,m2);
			}
		}
	}

/////////////////////////////join operation//////////////////////////////////////////

	l2 = first(pset,psp);

	for(i = 0; i< l2 -1; i++){
		for(j = i+1; j<l2;j++){
			l = inter(plane,m,pset[i], pset[j]);
	
			if(in(lset,l,psl)){
				z1 = posit(lset,l,psl);
				ADDONEEDGE(temp,i+psl,z1,m2);
				ADDONEEDGE(temp,j+psl,z1,m2);
				
			}

			else{
				k = first(lset, psl);
				lset[k] = l; 
				ADDONEEDGE(temp,i+psl,k,m2);
				ADDONEEDGE(temp,j+psl,k,m2);
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////


/*
for(i = 0; i< psp; i++){
	printf("%d ", pset[i]);
}

printf("\n");

for(j = 0; j< psl; j++){
	printf("%d ", lset[j]);
}

printf("\n");
*/


	for(k = 0;k<n2*m2;k++){
			for(j = 63; j >= 63-(n2-1); j--){
               			tempb = temp[k] >> j;

                		if(tempb & 1){
                        		printf("1");
                		}

                		else{		
                        		printf("0");
                		}
       			 }

			printf("\n");		

		}

		printf("\n");

}


