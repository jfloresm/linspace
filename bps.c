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
	
	

}

int main(){

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
	
	n1 = 12;
	m1 = SETWORDSNEEDED(n1);
	
	long int *temp = (long int *)malloc(m1*n1*sizeof(long int));			//for constructed graph	

	EMPTYGRAPH(temp,m1,n1);
  
/////////////////////////////////////////////////////////////////////////////////////
//
//Start with a quadrangle and build configuration from this (4 path as of now)
//
/////////////////////////////////////////////////////////////////////////////////////

	psp = 6;						//number of points in cons graph
	
	psl = 6;						//number of lines in cons graph

	n3 = comb(psl+1,2);
	
	m3 = SETWORDSNEEDED(n3);

	n4 = comb(psp+1,2);

	m4 = SETWORDSNEEDED(n4);

	long int** tr = (long int **)malloc(2*sizeof(long int*));	//to keep track of pair of points/lines that dont add new lines/points to graph

	
	tr[0] = (long int *)malloc(m3*sizeof(long int));		//for lines

	tr[1] = (long int *)malloc(m4*sizeof(long int));		//for points
	

	EMPTYGRAPH(tr[0],m3,n3);

	EMPTYGRAPH(tr[1],m4,n4);

	int *cset = (int *)malloc(b*sizeof(int));		//adjacency holder
	
	int *dont1 = (int *)malloc(b*sizeof(int));		//adjacency holder
//	
	
	pset = (int *)malloc(psp*sizeof(int));			//contains points in graph
//
	lset = (int *)malloc(psl*sizeof(int));			// contains lines in graph
//
//	long int *gr = (long int *)malloc(sizeof(long int));	//graph

	l = 0;
	
	v1 = randint(1301,651);

	lset[0] = v1;

	i = v1*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}
/////////////////////////////////////////////////////////////////////////////
	v2 = cset[randint(25,0)];

	pset[0] = v2;

	i = v2*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}

	ADDONEEDGE(temp,0,6,m1);

////////////////////////////////////////////////////////////////////////////
	v3 = cset[randint(25,0)];

	while(in(lset, v3, psl)){
		v3 = cset[randint(25,0)];
	}

	lset[1] = v3;

	i = v3*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}

	ADDONEEDGE(temp,6,1,m1);
///////////////////////////////////////////////////////////////////////////
	
	v4 = cset[randint(25,0)];

	while(in(pset, v4, psp)){
		v4 = cset[randint(25,0)];
	}

	pset[1] = v4;

	i = v4*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}

	ADDONEEDGE(temp,1,7,m1);
///////////////////////////////////////////////////////////////////////////
	
	v5 = cset[randint(25,0)];

	while(in(lset, v5, psl)){
		v5 = cset[randint(25,0)];
	}

	lset[2] = v5;

	i = v5*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}

	ADDONEEDGE(temp,7,2,m1);
///////////////////////////////////////////////////////////////////////////

	v6 = cset[randint(25,0)];

	while(in(pset, v6, psp)){
		v6 = cset[randint(25,0)];
	}

	pset[2] = v6;

	i = v6*m;

	k = 0;
	
	for(j = -1; (j = nextelement(plane + i,m,j))>= 0;){			//vertices that v1 is adjacent to
		cset[k] = j;
		k+=1;
	}

	ADDONEEDGE(temp,2,8,m1);
///////////////////////////////////////////////////////////////////////////

//NEED TO FINISH FUNCTION SO THAT WE DON'T TEST COMBINATIONS THAT DONT GIVE NEW POINTS
//	printf(" %d %d %d %d \n", v1,v2,v3,v4);
	
	l1 = 0; 

	l2 = 0;

	c1 = 3;									//number of lines currently

	c2 = 3;									//number of points currently

	r = 6;

	while(r <= (psp+psl-1)){

		if((r % 2) == 0){										//meet operation
	



			b1 = randint((c1-1),0);
	
			d1 = lset[b1];

			b2 = randint((c1-1),0);
	
			while(b2 == b1){

				b2 = randint((c1-1),0);

			}		
	
			d2 = lset[b2];

			for(i = 0; i<21; i++){
				if((plane[d1*m+i] & plane[d2*m+i]) != 0){
					j = FIRSTBIT((plane[d1*m+i] & plane[d2*m+i]))+64*i;
					printf("j = %d, r = %d, d1 = %d, d2 = %d \n",j,r,d1 ,d2);
					if(!in(pset,j,(c2-1))){
						pset[c2] = j;
						c2+= 1;
						ADDONEEDGE(temp,b1,c2+psl,m1);
						ADDONEEDGE(temp,b2,c2+psl,m1);
					}

					else{
						printf("j = %d, r = %d, d1 = %d, d2 = %d \n",j,r,d1 ,d2);
						z1 = dic(psl,b1,b2);
						if(!ISELEMENT(tr[0],z1)){
							ADDELEMENT(tr[0],z1);
							l1+= 1;
						}
						l = posit(pset,j, psp);
						ADDONEEDGE(temp,b1,l+psl,m1);
						ADDONEEDGE(temp,b2,l+psl,m1);
					}
				
					break;
				}
			}

			while((in(pset,j,(c2-1))==1) && (l1<= (c2-1))){

				b1 = randint((c1-1),0);

				b2 = randint((c1-1),0);
	
				while(b2 == b1){

					b2 = randint((c1-1),0);

				}		
	
				d2 = lset[b2];

				for(i = 0; i<21; i++){
					if((plane[d1*m+i] & plane[d2*m+i]) != 0){
						j = FIRSTBIT((plane[d1*m+i] & plane[d2*m+i]))+64*i;
						printf("j = %d, r = %d, d1 = %d, d2 = %d \n",j,r,d1 ,d2);
						if(!in(pset,j,(c2-1))){
							printf("j = %d, hi \n", j);
							pset[c2] = j;
							printf("%d \n", pset[c2]);
							c2+= 1;
							ADDONEEDGE(temp,b1,c2+psl,m1);
							ADDONEEDGE(temp,b2,c2+psl,m1);
						}

						else{
							l = posit(pset,j, psp);
							ADDONEEDGE(temp,b1,l+psl,m1);
							ADDONEEDGE(temp,b2,l+psl,m1);
						
						}
				
						break;
					}
				}
			
			}
					
			r+=1;

		}

		else{									//join operation

			b1 = randint((c2-1),0);
	
			d1 = pset[b1];

			b2 = randint((c2-1),0);
	
			while(b2 == b1){

				b2 = randint((c2-1),0);

			}		
	
			d2 = pset[b2];

			for(i = 0; i<21; i++){
				if((plane[d1*m+i] & plane[d2*m+i]) != 0){
					j = FIRSTBIT((plane[d1*m+i] & plane[d2*m+i]))+64*i;
					if(!in(lset,j,(c1-1))){
						lset[c1] = j;
						c1+= 1;
						ADDONEEDGE(temp,b1+psl,c1 ,m1);
						ADDONEEDGE(temp,b2+psl,c1,m1);
					}

					else{
						l = posit(lset,j, psl);
						ADDONEEDGE(temp,b1+psl,l,m1);
						ADDONEEDGE(temp,b2+psl,l,m1);
						
					}
				
					break;
				}
			}

			while(in(lset,j,(c1-1))){

				b1 = randint((c2-1),0);
	
				d1 = pset[b1];

				b2 = randint((c2-1),0);
	
				while(b2 == b1){

					b2 = randint((c2-1),0);

				}		
	
				d2 = pset[b2];

				for(i = 0; i<21; i++){
					if((plane[d1*m+i] & plane[d2*m+i]) != 0){
						j = FIRSTBIT((plane[d1*m+i] & plane[d2*m+i]))+64*i;
						if(!in(lset,j,(c1-1))){
							lset[c1] = j;
							c1+= 1;
							ADDONEEDGE(temp,b1+psl,c1,m1);
							ADDONEEDGE(temp,b2+psl,c1,m1);
						}

						else{
							l = posit(lset,j, psl);
							ADDONEEDGE(temp,b1+psl,l,m1);
							ADDONEEDGE(temp,b2+psl,l,m1);
						
						}
				
						break;
					}
				}
			
			}
					
			r+=1;			
	
		}



	}

	for(i = 0; i<psl; i++){
		printf("%d ", lset[i]);
	}

	printf("\n");

	for(i = 0; i<psp; i++){
		printf("%d ", pset[i]);
	}

	printf("\n");	

		
		for(k = 0;k<n1*m1;k++){
			for(j = 63; j >= 63-(n1-1); j--){
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
	
	
	
	
/*			
	printf(" v1 = %d \n", v1);

	for( i = 0; i < b; i++){
		printf("%d \n", cset[i]);
	}			
*/
/////////////////////////////////////////////////////////////////////////////////////
//
//Start with a tree and build up configuration (NEED TO FINISH)
//
/////////////////////////////////////////////////////////////////////////////////////	
/*
	
	u1 = 4;//#of points
	u2 = 5;//#of lines

	n2 = u1+u2;
	
	m2 = SETWORDSNEEDED(n2);

	//level2 = ;									//number of lines/vertices in layer 2

	int **inc  = (int **)malloc(4*sizeof(int *));

	inc[0] = (int *)malloc(sizeof(int));

	inc[1] = (int *)malloc((u1-1)*sizeof(int));

	inc[2] = (int *)malloc((u1-1)*sizeof(int));

	if((u1 % 1) == 0){

		inc[3] = (int *)malloc(((u1-1)/2)*sizeof(int));

	}

	else{

		inc[3] = (int *)malloc((((u1-1)/2)-1)*sizeof(int));

	}

	for(i = 1; i <4; i++){

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
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////////

	
	long int *temp = (long int *)malloc(m2*n2*sizeof(long int));			//starting configuration

	EMPTYGRAPH(temp,m1,n1);
	
	for(i = u1; i<u1+level2; i++){
		ADDONEEDGE(temp, 0, i, m2);
	}

	for(i = 1; i<u1;i++){
		ADDONEEDGE(temp, i, i+level2,m2); 
	}

	for(i = 1; i<7; i++){
		ADDONEEDGE(temp,2*i-1, i+24,m2);
		ADDONEEDGE(temp, 2*i, i+24, m2);
	}




*/
	return(0);

}
