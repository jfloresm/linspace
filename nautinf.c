#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>
#include "pls.h"

/*
Makes nauty output graphs into smo format printing info such as cardinality of aut group and self duality.
*/

/*INSTRUCTIONS:
argv[1] is the name of the file in g6 format as outputed by nauty. 
*/


void main(int argc, char* argv[]){
	
	int p,m,n,l,i,count,aut, dual,len11,e1,e2,e3;

	FILE *file1;
	FILE *file2;
	FILE *file3;
	char buffer[200];
	char num[200];
	char buffer2[200];
	char buffer3[200];
	char *line1 = NULL;		//Will contain graph in graph6 format
	size_t  len1 = 0; 		//Length of line to be read
	ssize_t read1;			//Value of Getline (should be >= 0).


	static DEFAULTOPTIONS_GRAPH(options);		//nauty variables
	statsblk stats;
	size_t k2;
	int* lab;
	int* ptn;
	int* orbits;

	
	options.getcanon = FALSE;

	snprintf(buffer, sizeof(buffer), "/run/media/jfloresm/766C41A15D195E71/nauty/%s", argv[1]);

	file1 = fopen(buffer,"r");

	if(file1==NULL){	
		printf("EXIT_FAILURE buffer\n");
	}
	
	count = 0;

	while ((read1 = getline(&line1, &len1, file1)) != -1){
	
		count+=1;
	}

	rewind(file1);

	strcpy(num,argv[1]);
	
	len11 = strlen(num);
	
	num[len11 - 4] = 0;

	n = atoi(num);

	m = SETWORDSNEEDED(n);

	//printf("%d \n", n);

	long int* g = (long int *)malloc(1*sizeof(long int));

	lab=(int *)malloc(n*sizeof(int));

	ptn=(int *)malloc(n*sizeof(int));

	orbits=(int *)malloc(n*sizeof(int));

	while ((read1 = getline(&line1, &len1, file1)) != -1){
	
		g =  (long int *)realloc(g,(m*n)*sizeof(long int));

		EMPTYGRAPH(g,m,n);

		stringtograph(line1,g,m);

		

		smo(g,m,n);
		
		p = findpoints(g,n);

		l = n-p;

		

		densenauty(g,lab,ptn,orbits,&options,&stats,m,n,NULL);

		//printf("%d %d \n",p,l);

	
		e3 = 0;

		if(n % 2 == 0){

		for(e1 = 0; e1<p; e1++){
			for(e2 = p; e2<n; e2++){ 	
		//		printf("%d, %d \n", orbits[l], orbits[h]);	
				if(orbits[e1] == orbits[e2]){
					//for(i = 0; i<n; i++){
				//		printf("%d ", orbits[i]);
				//	}

				//	printf("\n");
			
					//printf(" l = %d, h = %d, j = %d \n",l,h, j);
					e3 = 1;
					break;
				}
			}


			if(e3 ==1){
				break;
			}
		}
	
		}

		aut= autsize2(stats.grpsize1,stats.grpsize2);

		snprintf(buffer2, sizeof(buffer2), "/run/media/jfloresm/766C41A15D195E71/nauty2/g6/%d_%d_g6.txt", p,l);

		snprintf(buffer3, sizeof(buffer3), "/run/media/jfloresm/766C41A15D195E71/nauty2/inf/%d_%d_inf.txt", p,l);
		
		file2 = fopen(buffer2,"a");

		if(file2==NULL){	
			printf("EXIT_FAILURE buffer2\n");
		}

		writeg6(file2, g,m,n);

		fclose(file2);

		file3 = fopen(buffer3,"a");

		if(file3==NULL){	
			printf("EXIT_FAILURE buffer3\n");
		}
	
		fprintf(file3, "%d %d %d %d %d \n", p,l,1,aut, dual);

		fclose(file3);
	}
	
	fclose(file1);

}
