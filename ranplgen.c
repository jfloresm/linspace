#include "nauty.h"
#include "pls.h"
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>

/*

PREFACE: Generates random  linear spaces, converts them into bi-partite graph,
compares up to isomorphism and duality and puts them in a matrix.

*/

void main(){

	int p,l,m,i,i1,j,k,put, countd, th, row, flag, flag2, num,s,counter,n1,m1,k1,k3, lo,prop;

	FILE *file;
	FILE *file2;

	long int temp;

	clock_t time;						//for timing code
	double time_taken;

	static DEFAULTOPTIONS_GRAPH(options);			//nauty variables
	statsblk stats;
	size_t k2;
	int* lab;
	int* ptn;
	int* orbits;

	options.getcanon = TRUE;				//get canonical labeling of graph

	int *total;
	
	int *aut;
	int write;
	int write2;
	int write3;


	char buffer[200];

	char buffer2[200];

	printf("Enter number of points \n");
	scanf("%d", &p);

	printf("Enter number of lines \n");
	scanf("%d", &l);

	snprintf(buffer, sizeof(buffer), "/home/jfloresm/Documents/Research/linspace/planes/p%dl%dg6.txt", p,l);
	
	snprintf(buffer2, sizeof(buffer), "/home/jfloresm/Documents/Research/linspace/planes/p%dl%dinf.txt", p,l);
	
	printf("Enter number of times to run code \n");
	scanf("%d", &counter);

	
	total = (int *)malloc(counter*sizeof(int));

	zero(total, counter);

	aut = (int *)malloc(counter*sizeof(int));

	n1 = p+l;								//vertices in bipartite graph

	m1 = SETWORDSNEEDED(n1);						

	lab = (int *)malloc(n1*sizeof(int));

	ptn = (int *)malloc(n1*sizeof(int));

	orbits = (int *)malloc(n1*sizeof(int));

	long int ** graphs = (long int **)malloc(counter*sizeof(long int *));	//Save LS up to isomorphism and Duality

	long int * holder = (long int *)malloc(n1*m1*sizeof(long int));	

	long int * temp1 = (long int *)malloc(n1*m1*sizeof(long int));	

	long int * temp2 = (long int *)malloc(n1*m1*sizeof(long int));	
	
	m = SETWORDSNEEDED(l);

	long int *tracker;							//To keep track of positions in incidence matrix that have been tried 

	long int *ls;								//Holds the random LS

	tracker = (long int *)malloc(p*m*sizeof(long int));			//Holds positions to be tested to add a 1 in the incidence matrix

	ls = (long int *)malloc(p*m*sizeof(long int));
	
	time = clock();

	k1 = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("Enter 1 to write graphs in g6 format to disk (0 otherwise) \n");
	scanf("%d", &write);

	printf("Enter 1 to write graph info to disk (0 otherwise) \n");
	scanf("%d", &write2);
	
	printf("Enter 1 to print out graphs (0 otherwise) \n");
	scanf("%d", &write3);	
	

	if(write==1){
		file = fopen(buffer, "a");	
		if(file == NULL){
			printf("EXIT_FAILURE \n");
	
		}
	}

for(i1 = 0; i1 < counter; i1++){

	EMPTYSET(ls, p*m);

	EMPTYSET(tracker, p*m);

	for(i = 0; i<p; i++){
		togbits(tracker, l, i*m, m);
	}
	
	countd = p*l-1;

	//while(!linsp(ls,p,m) && checkzer(tracker,p,m)){					//FOR LS ONLY (NOT SATURATED)

	while(checkzer(tracker,p,m)){								//While there are locations in incidence matrix to test
		
		put = randint(countd, 0);							//position to test to put a 1
	
		k = 0;										//counter to try each of the countd positions

		flag = 0;

		for(i = 0; i<p; i++){

			for(j = -1; (j = nextelement(tracker + i*m,m,j)) >= 0;){
			
				if(k == put){

					th = j;

					row = i;

					DELELEMENT(tracker+i*m,th);

					ADDELEMENT(ls + row*m, th);
	
					countd -= 1;

					flag = 1;

					break;
				}
	
				k+=1;
			}

			if(flag == 1){
				break;
			}

		}	

		flag2 = 0;		

		for(i = 0; i<p; i++){

			num = 0;

			if(i == row){
				continue;
			}		

			if(ISELEMENT(ls + i, th)){
			
				for(j = 0; j<m; j++){ 					
									 
					temp = (ls[i*m+j] & ls[row*m+j]);
		
					num += POPCOUNT(temp);

					if(num >= 2){

						DELELEMENT(ls + row*m, th);

						flag2 = 1;
			
						break;
					}
				}

				if(flag2 == 1){
		
					break;
	
				}
	
			}									

		}

		while(flag2 == 1 && (countd >= 0)){

			put = randint(countd, 0);

			k = 0;

			flag = 0;

			for(i = 0; i<p; i++){

				for(j = -1; (j = nextelement(tracker + i*m,m,j)) >= 0;){
			
					if(k == put){

						th = j;

						row = i;

						DELELEMENT(tracker+i*m,th);

						ADDELEMENT(ls + row*m, th);

						countd -= 1;

						flag = 1;

						break;
					}
		
					k+=1;
				}

				if(flag == 1){
					break;
				}

			}	

			flag2 = 0;		

			for(i = 0; i<p; i++){

				num = 0;

				if(i == row){
					continue;
				}		
	
				if(ISELEMENT(ls + i, th)){
			
					for(j = 0; j<m; j++){ 					
									 
						temp = (ls[i*m+j] & ls[row*m+j]);
		
						num += POPCOUNT(temp);

						if(num >= 2){

							DELELEMENT(ls + row*m, th);

							flag2 = 1;
			
							break;
						}
					}
	
					if(flag2 == 1){
			
						break;
	
					}
	
				}
				
			}
	
		}									
			
	}

	if(linsp(ls,p,m)){							//COMMENT OUT IF WANT PLS INSTEAD OF JUST LS or STARTED WITH PL

		EMPTYGRAPH(holder, m1,n1);

		for(i = 0; i< p; i++){
			for(j = -1; (j = nextelement(ls + i*m,m,j)) >= 0;){
				ADDONEEDGE(holder, i, p+j,m1);
			}
		}
	
		if(k1 == 0){
				
			graphs[k1] = (long int *)malloc(m1*n1*sizeof(long int));
		
			EMPTYGRAPH(graphs[k1], m1,n1);

			for(i = 0; i<m1*n1;i++){
				graphs[k1][i] = holder[i];
			}

			EMPTYGRAPH(temp1, m1,n1);

			densenauty(graphs[k1],lab,ptn,orbits,&options,&stats,m1,n1,temp1);

			if(write==1){

				writeg6(file, graphs[k1],m1,n1);
		
			}

			aut[k1]= autsize2(stats.grpsize1,stats.grpsize2);
		
			total[k1]+=1;
		
			k1+=1;

			continue;
		}

		EMPTYGRAPH(temp1,m1,n1);

		EMPTYGRAPH(temp2,m1,n1);
	
		for(i = 0; i<k1; i++){

			k3 = 0;

			densenauty(graphs[i],lab,ptn,orbits,&options,&stats,m1,n1,temp1);		

			densenauty(holder,lab,ptn,orbits,&options,&stats,m1,n1,temp2);
			
			for(j = 0; j<m1*(size_t)n1; j++){

				if(temp1[j] == temp2[j]){
					k3+=1;
				}
			}

			if(k3 == m1*(size_t)n1){
				total[i] +=1;
				break;
			}

		}

		
		if(i == k1 && k3 != m1*(size_t)n1){
		
			graphs[k1] = (long int *)malloc(m1*n1*sizeof(long int));
				
			EMPTYGRAPH(graphs[k1], m1,n1);
				
			for(k = 0; k< n1*m1; k++){
				graphs[k1][k] = holder[k];
			}

			EMPTYGRAPH(temp2, m1,n1);

			densenauty(holder,lab,ptn,orbits,&options,&stats,m1,n1,temp2);

			if(write==1){

				writeg6(file, holder,m1,n1);

			}

			aut[k1]= autsize2(stats.grpsize1,stats.grpsize2);

			total[k1]+=1;
			
			k1+=1;

		}	
	

	}
}

	if(write==1){

		fclose(file);
	
	}

/////////////////////////////////////////////////////////////////////////////////////
//
//Write relevant information to disk.
//
/////////////////////////////////////////////////////////////////////////////////////

	if(write2==1){

		file2 = fopen(buffer2, "w");	
	
		if(file2 == NULL){
			printf("EXIT_FAILURE \n");
		}

		for(i = 0; i<k1; i++){
			fprintf(file2, "%d %d %d %d\n", p,l,total[i],aut[i]);
		}

		fclose(file2);

	}
/////////////////////////////////////////////////////////////////////////////////////
//
//For printing relevant information
//
/////////////////////////////////////////////////////////////////////////////////////

	if(write3==1){

		for(i = 0; i<k1; i++){
			incprint(graphs[i],m1, n1);
		}

	}

	time = clock() - time;

	time_taken = ((double)time)/CLOCKS_PER_SEC;	

	printf("ran %d times, found %d LS \n", counter, k1);

	printf("time = %f \n", time_taken);

	printf("\n");


}	
