#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 

/*

1. Need fix so that if two points(lines) intersect in a line(point) already in the set, that combination is not used again
(as of now it just searches two new points(lines) at random.






*/

/////////////////////////////////////////////////////////////////////////////////////
//
//Returns the number of points/lines in set
//
/////////////////////////////////////////////////////////////////////////////////////


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
	
/////////////////////////////////////////////////////////////////////////////////////
//
//Returns the point/line at which two lines/points meet/lie
//
/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////
//
//Prints out adjacency matrix of graph
//
/////////////////////////////////////////////////////////////////////////////////////

void incprint(long int * a, int m, int n){

	int k,j;
	long int tempb;

	for(k = 0;k<n*m;k++){
			for(j = 63; j >= 63-(n-1); j--){
               			tempb = a[k] >> j;

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

////////////////////
//
//-l1 is the number of lines currently
//-lset is set of points
//-psl is the max number of lines
//
////////////////////


void meet(int l1, long int * plane, int m,long int * temp,int m2, int * lset, int psl, int * pset, int psp){

	int i,j,k,l,z1;

	for(i = 0; i<l1-1;i++){
		for(j = i+1; j<l1; j++){
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

}

void join(int l2, long int * plane, int m,long int * temp,int m2, int * lset, int psl, int * pset, int psp){

	int i,j,k,l,z1;

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

}


void main(){

int i,j,k,l,m,n,a,b,m1,n1,c1,c2,r,r1,m2,n2,n3,m3,l1,l2,z1,z2;
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
	int holder;					//Number of graphs we want to save 	
	int i1,j1,k1; 					// For looping over algorithm
	int points;					//number of points in proj plane
	int num;					//number of meets/joins wanted

	static DEFAULTOPTIONS_GRAPH(options);
	statsblk stats;
	size_t k2;
	int* lab;
	int* ptn;
	int* orbits; 
	options.getcanon = TRUE;
	//int i1,i2,i3;
	//unsigned int x;			//Used to test how to read graphs

	
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

	points = a*a+a+1;		//number of points/lines

	b = a+1;		//number of points on each line (and lines through each point)

	n = 2*points;

	m = SETWORDSNEEDED(n);

	int *array = (int *)malloc(points*sizeof(int));					//Read Moorhouse file row by row

	long int *plane = (long int *)malloc(m*n*sizeof(long int));			//holds projective plane

	EMPTYGRAPH(plane,m,n);

	for(j = 0; j< points; j++){
		for(i = 0; i < b; i++){
                        if(fscanf(file, "%d",&array[i])){
				//printf("%d %d %d \n", i, array[i],j);
                                ADDONEEDGE(plane, j, array[i] + points,m);
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
//Make space to store the number of graphs we will save
//
/////////////////////////////////////////////////////////////////////////////////////
	
	
	holder = 100000; 

	num = 4;

	long int **graphs = (long int **)malloc(holder*sizeof(long int *));			//for constructed graph	

	int par[holder];									//to store m,n parameters of saved graphs

	long int* test1;									//to test graphs for isomorphism
	
	long int* test2;									//to test graphs for isomorphism
	 									

/////////////////////////////////////////////////////////////////////////////////////
//
//Start with a quadrangle (of points) and build configuration from this 
//-In this case, start with 4 lines (no three collinear) and end up with at most (6 choose 2)+4
//lines after join and (4 choose 2) points after meet
/////////////////////////////////////////////////////////////////////////////////////
/*
	snl = 4;									//# of lines of quadrangle
	snp = comb(snl,2);								//# of points after meet
	psl = comb(snp,2)+snl;								//#of lines after meet-join
	psp = snp;

	n2 = psp+psl;
	m2 = SETWORDSNEEDED(n2);
	
*/	
/////////////////////////////////////////////////////////////////////////////////////
//
//2 meets and 2 joins memory allocation (NOT IDEAL)
//
/////////////////////////////////////////////////////////////////////////////////////

	snl = 4;									//# of lines of quadrangle
	snp = comb(snl,2);								//# of points after meet
	psp = l;
	psl = l;

	n2 = psp+psl;
	m2 = SETWORDSNEEDED(n2);



/////////////////////////////////////////////////////////////////////////////////////
//
//Initialize sets
//
/////////////////////////////////////////////////////////////////////////////////////


	long int *temp = (long int *)malloc(m2*n2*sizeof(long int));			//starting configuration	
				
	EMPTYGRAPH(temp,m2,n2);

	pset = (int *)malloc(psp*sizeof(int));			//contains points in graph

	lset = (int *)malloc(psl*sizeof(int));			// contains lines in graph
	
	int * conc = (int *)malloc(4*sizeof(int));		//to check for concurrence when bulding quadrangle




/////////////////////////////////////////////////////////////////////////////////////
//
//Loop over algorithm holder number of times
//
/////////////////////////////////////////////////////////////////////////////////////

k1 = 0;

for(i1 = 0; i1<holder; i1++){

	fill(pset,psp);
	
	fill(lset,psl);

	//Make sure to choose 4 starting lines no 3 concurrent

	c1 = 0;

	for(i = 0; i<4; i++){

		v1 = randint(2*points-1,points);

		while(in(lset,v1,c1)){	
			v1 = randint(2*points-1,points);						//make sure not to repeat line
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
				
				v1 = randint(2*points-1,points);
				
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

			for(j = 0; j<3; j++){
				l = inter(plane,m, lset[j], lset[3]);
					if(l == conc[0] || l == conc[1] || l == conc[2]){
						k = -1;
						break;
					}
			}

			while(k == -1){

				k = 0; 			
			
				v1 = randint(2*points-1,points);

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

	//printf(" %d %d %d %d \n", lset[0], lset[1], lset[2], lset[3]);

/////////////////////////////////////////////////////////////////////////////////////
//
//Do meet followed by join operation num times.
//
/////////////////////////////////////////////////////////////////////////////////////

	for(i = 0; i<num;i++){
		l1 = first(lset,psl);

		meet(l1, plane, m,temp,m2, lset, psl, pset, psp);								

		l2 = first(pset,psp);

		join(l2, plane, m,temp,m2, lset, psl, pset, psp);	
	}

/////////////////////////////////////////////////////////////////////////////////////
//
//Create a new graph with correct number of vertices
//
/////////////////////////////////////////////////////////////////////////////////////

	r = first(lset,psl);

	r1 = first(pset,psp);

	n3 = r+r1;

	m3 = SETWORDSNEEDED(n3);

	long int *temp2 = (long int *)malloc(m3*n3*sizeof(long int));

	EMPTYGRAPH(temp2,m3,n3);

	k = 0;

	for(j = 0 ; j<m2*r; j+= m2){
		for(i = -1;(i = nextelement(temp+j,m2,i)) >=0;){	
			l = i - psl;
			ADDONEEDGE(temp2, k, l+r,m3);					
		}		

		k+=1;
	}

	//printf("%d %d \n", r1,r);

/////////////////////////////////////////////////////////////////////////////////////
//
//Allocate memory for nauty
//
/////////////////////////////////////////////////////////////////////////////////////

	lab = (int *)malloc(n3*sizeof(int));

	ptn = (int *)malloc(n3*sizeof(int));

	orbits = (int *)malloc(n3*sizeof(int));			

/////////////////////////////////////////////////////////////////////////////////////
//
//Create a new graph with correct number of vertices
//
/////////////////////////////////////////////////////////////////////////////////////



	if(k1 == 0){
		graphs[k1] = (long int *)malloc(m3*n3*sizeof(long int));
		
		for(i = 0; i<m3*n3;i++){
			graphs[k1][i] = temp2[i];
		}
		
		par[k1] = n3;
		
		k1+=1;
	}

	test1 = (long int *)malloc(n3*m3*sizeof(long int));					//for canonical labels of graphs
	
	test2 = (long int *)malloc(n3*m3*sizeof(long int));					//for canonical labels of graphs
	
	for(i = 0; i<k1; i++){

		if(par[i] == n3){	

		//	printf("i = %d \n", i);

			densenauty(graphs[i],lab,ptn,orbits,&options,&stats,m3,n3,test1);

			densenauty(temp2,lab,ptn,orbits,&options,&stats,m3,n3,test2);

		//	incprint(temp2, m3,n3);

		//	incprint(graphs[i], m3,n3);
			
			for(j = 0; j<m3*(size_t)n3; j++){

				if(test1[j] != test2[j]){
					break;
				}
			}

			if(j != m3*(size_t)n3){
								
				for(k = 0; k< n3*m3; k++){
					graphs[k1][k] = temp2[k];
				}
			
				par[k1] = n3;

				k1+=1;

				break;
			}

		}


		else{
			continue;
		}

	}

	free(lab);
	free(orbits);
	free(ptn);
	free(test1);
	free(test2);
	free(temp2);			
		
}	

	printf("%d = k1 \n", k1);		

	free(temp);

}

