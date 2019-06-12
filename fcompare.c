#include "nauty.h"
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>
#include "pls.h"
/*

PREFACE: To compare LS (and eventually PLS) that we construct out of projective planes to PL (evenetually PLS) that we simply contruct randomly.
*/

/*

INTRODUCTION: argv[1] is the name of ranpl file, argv[2] is the name of planepl file, argv[3] is the number of meet/joins, argv[4] is the number of points (25 or 49)   
*/

void main(int argc, char* argv[]){

	int i,j,k,k3,zz;
	int n;
	int m;
	int n1;
	int m1;
	int order[2];
	int count1;
	int count2;
	int count3;
	char *line1 = NULL;		//Will contain graph in graph6 format
	size_t  len1 = 0; 		//Length of line to be read
	ssize_t read1;			//Value of Getline (should be >= 0).
	char *line2 = NULL;		//Will contain graph in graph6 format
	size_t  len2 = 0; 		//Length of line to be read
	ssize_t read2;			//Value of Getline (should be >= 0).
	char *line3 = NULL;		//Will contain graph in graph6 format
	size_t  len3 = 0; 		//Length of line to be read
	ssize_t read3;			//Value of Getline (should be >= 0).	
	char *line4 = NULL;		//Will contain graph in graph6 format
	size_t  len4 = 0; 		//Length of line to be read
	ssize_t read4;			//Value of Getline (should be >= 0).
	FILE* file1;
	FILE* file2;
	FILE* file3;
	FILE* file4;
	FILE* file5;
	FILE* file6;
	int p;
	int l;
	char buffer1[300];
	char buffer2[200];
	char buffer3[300];
	char buffer4[300];
	char buffer5[400];
	char buffer6[400];
	char* loc;
	char* loc2;
	int** infpl;
	int** infran;
	long int **ranpl;
	long int **ranpl2;
	long int *planepl;
	long int *temp1;
	long int *temp2;
	int len11;
	int len33;
	int len22;
	int len44;
	


	static DEFAULTOPTIONS_GRAPH(options);		//nauty variables
	statsblk stats;
	size_t k2;
	int lab[n];
	int ptn[n];
	int orbits[n];

	
	options.getcanon = TRUE;

	planepl = (long int *)malloc(1*sizeof(long int));
	temp2 = (long int *)malloc(1*sizeof(long int));

//FIX ADDRESS

	for(i = 0; i<2; i++){
		if(sscanf(argv[i+3], "%d", &order[i]) != 1){
			printf("error, not an integer");
		}
	}

	snprintf(buffer1, sizeof(buffer1), "/run/media/jfloresm/766C41A15D195E71/ranpl/g6/%s", argv[1]);
	snprintf(buffer3, sizeof(buffer3), "/run/media/jfloresm/766C41A15D195E71/planepl/g6/%dpl/%d/%s",order[0],order[1], argv[2]);
	
	

	len11 = strlen(argv[1]);
	len33 = strlen(argv[2]);

	char* save1;
	char* save2;
	char* save3;
	char* save4;

	save1 = argv[1];
	save3 = argv[2];


	save1[len11-7] = 0;
	save3[len33-7] = 0;
	
	snprintf(buffer5, sizeof(buffer5), "/run/media/jfloresm/766C41A15D195E71/comp/%d/g6/%s_%s_g6.txt", order[1],save1, save3);	//to save graphs that don't embed
	snprintf(buffer6, sizeof(buffer6), "/run/media/jfloresm/766C41A15D195E71/comp/%d/inf/%s_%s_inf.txt", order[1],save1, save3);	//to save graphs that don't embed

/////////////////////////////////////////////////////////////////////////////////////
//
//Find p and l from name of file, find file names for info
//
/////////////////////////////////////////////////////////////////////////////////////	

	char st[200];

	int str2 = '_';

	p = atoi(save1);

	char *ret;

	ret = strchr(save1, str2);

	strcpy(st, ret+1);


	l = atoi(st);

	
////////////////////////////////////////////////////////////////////////////////////////////////
	n = p+l;

	m = SETWORDSNEEDED(n);

	ranpl = (long int **)malloc(n*sizeof(long int*));
	
	count1 = 0;
	
	count2 = 0;


//////////////////////////////////////////////////////////////////////////////////////////////
	save4 = save3;

	len44 = strlen(save4);
		
	len44 = strlen(save4);

	strcpy(save4+len44, "_inf.txt");
	
	snprintf(buffer4, sizeof(buffer4), "/run/media/jfloresm/766C41A15D195E71/planepl/inf/%dpl/%d/%s", order[0],order[1], save4);

///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
	save2 = save1;

	len22 = strlen(save2);
		
	len22 = strlen(save2);

	strcpy(save2+len22, "_inf.txt");
	
	snprintf(buffer2, sizeof(buffer2), "/run/media/jfloresm/766C41A15D195E71/ranpl/inf/%s", save2);

///////////////////////////////////////////////////////////////////////////////////////////////////////



	file4 = fopen(buffer4, "r");	
	if(file4 == NULL){
		printf("EXIT_FAILURE buffer 4\n");
	}

	while ((read4 = getline(&line4, &len4, file4)) != -1){
	
		count2+=1;
	}

	rewind(file4);


	infpl=(int **)malloc(count2*sizeof(int*));

	for(i = 0; i<count2; i++){
		infpl[i]=(int *)malloc(4*sizeof(int)); 
	}

	i = 0;

	while(!feof(file4)){	
	     fscanf(file4, "%d %d %d %d",&infpl[i][0],&infpl[i][1],&infpl[i][2],&infpl[i][3]);
	     i+=1;                           
	}  

	fclose(file4);
	
	

	file1 = fopen(buffer1, "r");	
	if(file1 == NULL){
		printf("EXIT_FAILURE buffer 1\n");
	}

	while ((read1 = getline(&line1, &len1, file1)) != -1){
	
		count1+=1;
	}

	rewind(file1);

	file2 = fopen(buffer2, "r");	
	if(file2 == NULL){
		printf("EXIT_FAILURE buffer 1\n");
	}

	infran=(int **)malloc(count1*sizeof(int*));

	for(i = 0; i<count1; i++){
		infran[i]=(int *)malloc(4*sizeof(int)); 
	}

	i = 0;

	while(!feof(file2)){	
	     fscanf(file2, "%d %d %d %d",&infran[i][0],&infran[i][1],&infran[i][2],&infran[i][3]);
	     i+=1;                           
	}

	fclose(file2);

	ranpl = (long int **)malloc(count1*sizeof(long int*));
	
	ranpl2 = (long int **)malloc(count1*sizeof(long int*));
	
	for(i = 0; i< count1; i++){
		ranpl[i] = (long int*)malloc(m*n*sizeof(long int));
		ranpl2[i] = (long int*)malloc(m*n*sizeof(long int));
	}


	i= 0;
		
	while ((read1 = getline(&line1, &len1, file1)) != -1){
		stringtograph(line1,ranpl[i],m);
		stringtograph(line1,ranpl2[i],m);
			
		sleep(.1);
			
		i+=1;
	}	

	fclose(file1);

	


	temp1 = (long int *)malloc(m*n*sizeof(long int));

	i = 0;
	
	count3 = 0;

	
	
	int holder[count1];

	zero(holder,count1);		
	
	file3 = fopen(buffer3, "r");	
	if(file3 == NULL){
		printf("EXIT_FAILURE buffer 3\n");
	}

	while (((read3 = getline(&line3, &len3, file3)) != -1) &&(count1 != count3)){
		
		n1 = infpl[i][0]+infpl[i][1];
		m1= SETWORDSNEEDED(n1);
		
		planepl = (long int *)realloc(planepl,(m1*n1)*sizeof(long int));
		temp2 = (long int *)realloc(temp2,(m1*n1)*sizeof(long int));

		

		EMPTYGRAPH(planepl,m1,n1);
		EMPTYGRAPH(temp2,m1,n1);
		EMPTYGRAPH(temp1,m,n);
		
		

		stringtograph(line3,planepl,m1);
		sleep(.1);
		i+=1;

		for(j = 0; j<count1; j++){
			if(!emptyg(ranpl[j],m)){
				continue;
			}

			if((p+l) == n1){
				
				
			
				densenauty(planepl,lab,ptn,orbits,&options,&stats,m,n,temp2);		
				densenauty(ranpl[j],lab,ptn,orbits,&options,&stats,m,n,temp1);	
				
				

				k3 = 0;

				for(k = 0; k<m*(size_t)n; k++){

					if(temp1[k] == temp2[k]){
						k3+=1;
					}

					if(k3 == m*(size_t)n){

						EMPTYGRAPH(ranpl[j],m,n);
						//holder[j] = 1;
						count3+=1;
					
					}
				}
			
	
			}
	
		}

	}
	
	

	if(count3 != count1){

		file5 = fopen(buffer5, "a");	
		if(file5 == NULL){
			printf("EXIT_FAILURE \n");
		}

		file6 = fopen(buffer6, "w");	
			if(file6 == NULL){
			printf("EXIT_FAILURE \n");
		}

		for(j = 0; j< count1; j++){
			if(emptyg(ranpl[j],m)==1){

				
				writeg6(file5, ranpl2[j],m,n);
				
				fprintf(file6, "%d %d %d %d\n", infran[j][0],infran[j][1],infran[j][2],infran[j][3]);
		
			}
		}

	

		fclose(file5);
	
		fclose(file6);

	}

		
	
		
	free(temp1);
	free(ranpl);	//count1
	free(ranpl2);	//count1
	free(infpl);	//count2
	free(infran);
}
