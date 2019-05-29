#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>
#include "pls.h"
/*

PREFACE: Enumerates number of non-isomorphic (up to duality) linear spaces embedded in a projective plane starting from a random construction
followed by operations of meet and join always ending in join.

1. Need fix so that if two points(lines) intersect in a line(point) already in the set, that combination is not used again
(as of now it just searches two new points(lines) at random.

*/


void main(){

int i,j,k,l,m,n,a,b,m1,n1,c1,r,r1,m2,n2,n3,m3,l1,l2,z1,pl1,pl2,pl11,pl22,k3;
	int v1;
	FILE *file;
	FILE *file2;
	FILE *file3;

	char buffer[200];
	char buffer2[200];
	char buffer3[200];
	
	char loc[20];					//Name of file with projective plane

	printf("Enter the name of the file \n");
	gets(loc);

	snprintf(buffer, sizeof(buffer), "/home/jfloresm/Documents/Research/linspace/planes/%s.txt", loc);
	snprintf(buffer2, sizeof(buffer2), "/home/jfloresm/Documents/Research/linspace/planes/%sg6.txt", loc);
	snprintf(buffer3, sizeof(buffer3), "/home/jfloresm/Documents/Research/linspace/planes/%sinf.txt", loc);

	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	long int tempb;					//for bit computations
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
	int dif;					//to check if a graph has distinct number of vertices compared to list

	int write2;					//Make 1 to write graphs in g6 format to disk
	int write3;					//Make 1 to write graph info to disk
	int write4;					//Make 1 to write print out graphs

	static DEFAULTOPTIONS_GRAPH(options);		//nauty variables
	statsblk stats;
	size_t k2;
	int* lab;
	int* ptn;
	int* orbits;

	lab = (int *)malloc(1*sizeof(int)); 
	ptn = (int *)malloc(1*sizeof(int));
	orbits = (int *)malloc(1*sizeof(int));  
	
	clock_t time;					//for timing code
	double time_taken;
	
	options.getcanon = TRUE;			//get canonical labeling of graph

	
/////////////////////////////////////////////////////////////////////////////////////
//
//Read projective planes in Moorhouse format and store it in nauty format in plane
//
/////////////////////////////////////////////////////////////////////////////////////	
	
	printf("Enter 1 to write files to disk (0 otherwise) \n");
	scanf("%d", &write2);

	printf("Enter 1 to write graph info to disk (0 otherwise) \n");
	scanf("%d", &write3);

	printf("Enter 1 to print out graphs (0 otherwise) \n");
	scanf("%d", &write4);

	file = fopen(buffer, "r");	
	if(file == NULL){
		printf("EXIT_FAILURE \n");
	}

	if(write2 == 1){
		file2 = fopen(buffer2, "a");	
		if(file2 == NULL){
			printf("EXIT_FAILURE \n");
		}
	}	

	a = 49;			//order of plane

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
                                ADDONEEDGE(plane, j, array[i] + points,m);
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
	
	printf("Enter number of times to run code \n");
	scanf("%d", &holder);

	printf("Enter number of times to do meet/join operation \n");
	scanf("%d", &num);
	

	int sol= holder;										//max number of nonisomorphic PS

	long int **graphs = (long int **)malloc(sol*sizeof(long int *));			//for constructed graph	

//	int *counter = (int *)malloc(1*sizeof(int));						//to hold number of times a graph occurs

//	int *aut = (int *)malloc(1*sizeof(int));						//to hold cardinality of automorphism group

	

	int counter[sol];
	
	zero(counter,sol);

	int aut[sol];

	int par[sol];										//to store m,n parameters of saved graphs

	long int* test1;									//to test graphs for isomorphism
	
	long int* test2;									//to test graphs for isomorphism
	
	test1 = (long int *)malloc(1*sizeof(long int));
	
	test2 = (long int *)malloc(1*sizeof(long int));
 									

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

	//snl = 4;									//# of lines starting of quadrangle
	//snp = comb(snl,2);								//# of points after meet
	//Don't need these since I'm starting with max number of poitns and lines for space

	psp = points;									//max number of points
	psl = points;									//max number of lines

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

	long int *temp2 =(long int *)malloc(1*sizeof(long int));//to store graph of correct size

	long int*dummy;						//for first loop usage of autsize



/////////////////////////////////////////////////////////////////////////////////////
//
//Loop over algorithm holder number of times
//
/////////////////////////////////////////////////////////////////////////////////////

k1 = 0;

time = clock();

for(i1 = 0; i1<holder; i1++){	

//	printf("i1 = %d \n", i1);

	fill(pset,psp);
	
	fill(lset,psl);

	//Make sure to choose 4 starting lines no 3 concurrent

	c1 = 0;

/////////////////////////////////////////////////////////////////////////////////////
//
//To start with quadrangle of points
//
/////////////////////////////////////////////////////////////////////////////////////
/*

	for(i = 0; i<4; i++){

		v1 = randint(points-1,0);

		while(in(pset,v1,c1)){	
			v1 = randint(points-1,0);						//make sure not to repeat line
		}

		if(i <= 1){
		
			pset[c1] = v1;

			c1+= 1;								//first line
		}

		else if(i==2){		

			pset[c1] = v1;
							//make sure no 3 lines are concurrent							
			conc[0] = inter(plane,m,pset[0],pset[1]);

			k = 1;

			for(j = 0; j<2; j++){
				conc[k] = inter(plane,m, pset[j], pset[2]);
				k+=1;
			}
							
			while(conc[2] == conc[0] || in(pset,v1,c1)){
				
				v1 = randint(points-1,0);
				
				pset[c1] = v1;
				
				k = 1;

				for(j = 0; j<2; j++){
					conc[k] = inter(plane,m, pset[j], pset[2]);
					k+=1;
				}						
			}
			
			c1+=1;
		}

		else if(i == 3){

			pset[c1] = v1;				

			for(j = 0; j<3; j++){
				l = inter(plane,m, pset[j], pset[3]);
					if(l == conc[0] || l == conc[1] || l == conc[2]){
						k = -1;
						break;
					}
			}

			while(k == -1){

				k = 0; 			
			
				v1 = randint(points-1,0);

				pset[c1] = v1;
							//make sure no 3 lines are concurrent						

				for(j = 0; j<3; j++){
					l = inter(plane,m, pset[j], pset[3]);
						if(l == conc[0] || l == conc[1] || l == conc[2]){
							k = -1;
							break;
						}
				}			

			}	
		}
	
	}
	


*/
/////////////////////////////////////////////////////////////////////////////////////
//
//To start with a triangle of points
//
/////////////////////////////////////////////////////////////////////////////////////
/*
	for(i = 0; i<3; i++){

		v1 = randint(points-1,0);

		while(in(pset,v1,c1)){	
			v1 = randint(points-1,0);						//make sure not to repeat line
		}

		if(i <= 1){
		
			pset[c1] = v1;

			c1+= 1;								//first line
		}

		else if(i==2){		

			pset[c1] = v1;
							//make sure no 3 lines are concurrent							
			conc[0] = inter(plane,m,pset[0],pset[1]);

			k = 1;

			for(j = 0; j<2; j++){
				conc[k] = inter(plane,m, pset[j], pset[2]);
				k+=1;
			}
							
			while(conc[2] == conc[0] || in(pset,v1,c1)){
				
				v1 = randint(points-1,0);
				
				pset[c1] = v1;
				
				k = 1;

				for(j = 0; j<2; j++){
					conc[k] = inter(plane,m, pset[j], pset[2]);
					k+=1;
				}						
			}
			
			c1+=1;
		}

	}

*/
///////////////////////////////////////4 RANDOM LINES/////////////////////////////////////////////
/*
	v1 = randint(2*points-1,points);

	lset[c1] = v1;
	
	c1+=1;

	for(i = 1; i<4; i++){

		v1 = randint(2*points-1,points);

		while(in(lset,v1,c1)){	
			v1 = randint(2*points-1,points);						//make sure not to repeat line
		}

		lset[c1] = v1;

		c1+=1;
	}
	
	//printf("%d %d %d %d \n", lset[0],lset[1],lset[2],lset[3]);
*/
///////////////////////////////////////4 RANDOM POINTS/////////////////////////////////////////////

	v1 = randint(points-1,0);

	pset[c1] = v1;
	
	c1+=1;

	for(i = 1; i<4; i++){

		v1 = randint(points-1,0);

		while(in(pset,v1,c1)){	
			v1 = randint(points-1,0);						//make sure not to repeat line
		}

		pset[c1] = v1;

		c1+=1;
	}
	
	//printf("%d %d %d %d \n", lset[0],lset[1],lset[2],lset[3]);



/////////////////////////////////////////////////////////////////////////////////////
//
//Do meet followed by join operation num times. (FOR LINES)
//
/////////////////////////////////////////////////////////////////////////////////////
/*
	EMPTYGRAPH(temp,m2,n2);

	for(i = 0; i<num;i++){
		l1 = first(lset,psl);

		lmeet(l1, plane, m,temp,m2, lset, psl, pset, psp);								

		l2 = first(pset,psp);

		ljoin(l2, plane, m,temp,m2, lset, psl, pset, psp);	
	}
*/
/////////////////////////////////////////////////////////////////////////////////////
//
//Do meet followed by join operation num times. (for points)
//
/////////////////////////////////////////////////////////////////////////////////////

	EMPTYGRAPH(temp,m2,n2);

	l2 = first(pset,psp);

	pjoin(l2, plane, m,temp,m2, lset, psl, pset, psp);

	for(i = 0; i<num;i++){
	
		l1 = first(lset,psl);
	
		pmeet(l1, plane, m,temp,m2, lset, psl, pset, psp);								

		l2 = first(pset,psp);

		pjoin(l2, plane, m,temp,m2, lset, psl, pset, psp);	
		
	}


/////////////////////////////////////////////////////////////////////////////////////
//
//Create a new graph with correct number of vertices
//
/////////////////////////////////////////////////////////////////////////////////////

	/*r = first(lset,psl);

	r1 = first(pset,psp);*/ //FOR LINES

	r = first(pset,psp);

	r1 = first(lset,psl);	//FOR POINTS	

	n3 = r+r1;

	m3 = SETWORDSNEEDED(n3);

	
	temp2= (long int *)realloc(temp2,m3*n3*sizeof(long int));

	if(temp2 == NULL){
		printf("failed to allocate memory for temp2, i1 = %d \n", i1);
	}
	

	EMPTYGRAPH(temp2,m3,n3);

	k = 0;

	for(j = 0 ; j<m2*r; j+= m2){							//m2 is how many set words per vertex, r is the number of vertices
		for(i = -1;(i = nextelement(temp+j,m2,i)) >=0;){	
			l = i - psl;
			ADDONEEDGE(temp2, k, l+r,m3);					
		}		

		k+=1;
	}



/////////////////////////////////////////////////////////////////////////////////////
//
//Allocate memory for nauty
//
/////////////////////////////////////////////////////////////////////////////////////
	
//	printf("before nauty \n");

	lab = (int *)realloc(lab,n3*sizeof(int));

	if(lab == NULL){
		printf("failed to allocate memory for lab, i1 = %d \n", i1);
	}

	ptn = (int *)realloc(ptn,n3*sizeof(int));

	if(ptn == NULL){
		printf("failed to allocate memory for ptn, i1 = %d \n", i1);
	}

	orbits = (int *)realloc(orbits,n3*sizeof(int));			
	
	if(orbits == NULL){
		printf("failed to allocate memory for orbits, i1 = %d \n", i1);
	}
	
//	printf("after nauty \n");

/////////////////////////////////////////////////////////////////////////////////////
//
//Create a new graph with correct number of vertices
//
/////////////////////////////////////////////////////////////////////////////////////

	if(k1 == 0){

		graphs[k1] = (long int *)malloc(m3*n3*sizeof(long int));

		dummy = (long int *)malloc(m3*n3*sizeof(long int));
	
		for(i = 0; i<m3*n3;i++){
			graphs[k1][i] = temp2[i];
		}

		densenauty(graphs[k1],lab,ptn,orbits,&options,&stats,m3,n3,dummy);

		if(write2 == 1){
			writeg6(file2, graphs[k1],m3,n3);
		}

		aut[k1]= autsize2(stats.grpsize1,stats.grpsize2);
		
		par[k1] = n3;
		
		counter[k1]+=1;
		
		k1+=1;

		continue;
	}


	test1 = (long int *)realloc(test1,(m3*n3)*sizeof(long int));					//for canonical labels of graphs

	if(!test1){
		printf("failed to allocate memory for test1, i1 = %d \n", i1);
	}
 	
	test2 = (long int *)realloc(test2,(m3*n3)*sizeof(long int));					//for canonical labels of graphs
		
	if(!test2){
		printf("failed to allocate memory for test2, i1 = %d \n", i1);
	}


	EMPTYGRAPH(test1,m3,n3);

	EMPTYGRAPH(test2,m3,n3);

	dif = 0;
	
	for(i = 0; i<k1; i++){
		
		k3 = 0;
	
		if(par[i] == n3){								//if same number of vertices, check for isomorphism
				
			dif += 1;

			densenauty(graphs[i],lab,ptn,orbits,&options,&stats,m3,n3,test1);		

			densenauty(temp2,lab,ptn,orbits,&options,&stats,m3,n3,test2);
			
			for(j = 0; j<m3*(size_t)n3; j++){

				if(test1[j] == test2[j]){
					k3+=1;
				}
			}
		
			if(k3 == m3*(size_t)n3){

				counter[i]+=1;
				break;

			}

			if(i == k1 && k3 != m3*(size_t)n3){

				graphs[k1] = (long int *)malloc(m3*n3*sizeof(long int));
								
				for(k = 0; k< n3*m3; k++){
					graphs[k1][k] = temp2[k];
				}

				densenauty(temp2,lab,ptn,orbits,&options,&stats,m3,n3,test2);

				if(write2 == 1){
					writeg6(file2, temp2,m3,n3);
				}
	
				aut[k1]= autsize2(stats.grpsize1,stats.grpsize2);

				counter[k1]+=1;
			
				par[k1] = n3;

				k1+=1;
			}


		}

	}


		if((i == k1) && (dif == 0)){						//if new number of vertices, add graph
					
			graphs[k1] = (long int *)malloc(m3*n3*sizeof(long int));
								
			for(k = 0; k< n3*m3; k++){
				graphs[k1][k] = temp2[k];
			}

			densenauty(temp2,lab,ptn,orbits,&options,&stats,m3,n3,test2);

			if(write2 == 1){
				writeg6(file2, temp2,m3,n3);
			}

			aut[k1]= autsize2(stats.grpsize1,stats.grpsize2);

			counter[k1]+=1;
		
			par[k1] = n3;

			k1+=1;
		}
	

	
}	

	if(write2 == 1){
		fclose(file2);
	}	
	
/////////////////////////////////////////////////////////////////////////////////////
//
//For finding number of points, lines
//
/////////////////////////////////////////////////////////////////////////////////////

	int numpoints[k1];

	int numlines[k1];

	for(i = 0; i<k1; i++){
		numpoints[i] = findpoints(graphs[i], par[i]);
		numlines[i] = par[i] - numpoints[i];
	}
	
/////////////////////////////////////////////////////////////////////////////////////
//
//Write relevant information to disk.
//
/////////////////////////////////////////////////////////////////////////////////////
if(write3==1){

	file3 = fopen(buffer3, "w");	
	if(file3 == NULL){
		printf("EXIT_FAILURE \n");
	}

	for(i = 0; i<k1; i++){
		fprintf(file3, "%d %d %d %d\n", numpoints[i],numlines[i],counter[i],aut[i]);
	}

	fclose(file3);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//For printing relevant information
//
/////////////////////////////////////////////////////////////////////////////////////

	printf("\n");

	for(i = 0; i<k1;i++){

		printf("#p = %d, #l = %d, counter[%d] = %d, aut[%d] = %d \n",numpoints[i],numlines[i],i,counter[i],i, aut[i]);
	
		if(write4==1){

			incprint(graphs[i],1, par[i]);
	
			printf("\n");
		}
	}

	time = clock() - time;

	time_taken = ((double)time)/CLOCKS_PER_SEC;	

	printf("ran %d times, found %d LS \n", holder, k1);

	printf("time = %f \n", time_taken);
//////////////////////////////////////////////////////////////////////////////////////// 		
/*
	free(temp);
	free(lab);
	free(ptn);
	free(test1);
	free(test2);
	free(temp);
	free(temp2);
*/
}

