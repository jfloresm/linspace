/* This program prints generators for the automorphism group of an
n-vertex polygon, where n is a number supplied by the user.
This version uses a fixed limit for MAXN.
*/
#define MAXN 1000    /* Define this before including nauty.h */
#define MAXCHAR 1000
#include "nauty.h"   /* which includes <stdio.h> and other system files */
int main(){
/*Set up for Static Allocation. Will change to Dynamic for memory purposes.*/

	/*DYNALLSTAT(int,lab1,lab1_sz);
	DYNALLSTAT(int,lab2,lab2_sz);
	DYNALLSTAT(int,ptn,ptn_sz);
	DYNALLSTAT(int,orbits,orbits_sz);
	DYNALLSTAT(int,map,map_sz);
	*/


	/*DYNALLSTAT(graph,g1,g1_sz);
	DYNALLSTAT(graph,g2,g2_sz);*/


//	DYNALLSTAT(graph,cg1,cg1_sz);
//	DYNALLSTAT(graph,cg2,cg2_sz);

	//int lab[MAXN],ptn[MAXN],orbits[MAXN];
	static DEFAULTOPTIONS_GRAPH(options);
	statsblk stats;
	int n,m,v,i,j,k,l;
	size_t k1;
	int i1,i2,i3;
	unsigned int x;			//Used to test how to read graphs
  	unsigned int x1;
/* Select option for canonical labelling */
	options.getcanon = TRUE;



	char *line = NULL;		//Will contain graph in graph6 format
	size_t  len = 0; 		//Length of line to be read
	ssize_t read;			//Value of Getline (should be >= 0).
	int count;			//Counts number of lines in text file	


/* Default options are set by the DEFAULTOPTIONS_GRAPH macro above.
Here we change those options that we want to be different from the
defaults.  writeautoms=TRUE causes automorphisms to be written.     */
	//options.writeautoms = TRUE;

	//printf("Integer 2 <= n <= 8: \n");
	//scanf("%d", &n);		//Number of vertices
	n=4;
	m = SETWORDSNEEDED(n);		//m = ceiling(n/64)
	

/* The following optional call verifies that we are linking
to compatible versions of the nauty routines.            */
//nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

/*
	DYNALLOC1(int,lab1,lab1_sz,n,"malloc");
	DYNALLOC1(int,lab2,lab2_sz,n,"malloc");
	DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
	DYNALLOC1(int,orbits,orbits_sz,n,"malloc");
	DYNALLOC1(int,map,map_sz,n,"malloc");   */


/* Since we are not requiring a canonical labelling, the last
parameter to densenauty() is not required and can be NULL. */
//densenauty(g,lab,ptn,orbits,&options,&stats,m,n,NULL);
/* The size of the group is returned in stats.grpsize1 and
stats.grpsize2. */
//printf("Automorphism group size = ");
//writegroupsize(stdout,stats.grpsize1,stats.grpsize2);
//printf("\n");
//}

/////////////////////////////////////////////////////////////////////////
/*
To Open and Read Graph6 Files, (Find a better method)
*/                 
/////////////////////////////////////////////////////////////////////////


	FILE *file;
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
	

	case 7:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace7.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	

	case 8:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace8.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	

	case 9:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace9.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	

	case 10:
		file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace10.txt","r");
		//printf("4\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}
		break;
	}
	
/////////////////////////////////////////////////////////////////////////
/*
Count number of graphs in each file
*/                 
/////////////////////////////////////////////////////////////////////////

	//fgets(s,MAXCHAR,file);

	i=0;
	k=0;
	i3=0;
	count = 0;

	while ((read = getline(&line, &len, file)) != -1){
	
		count+=1;
	}

	graph g[count][n*m];		// 2 d array. 1st dimension tells you which graph
	
	rewind(file);

	
	/*DYNALLOC2(graph,g1,g1_sz,n,m,"malloc");

	DYNALLOC2(graph,g2,2_sz,n,m,"malloc");*/

/////////////////////////////////////////////////////////////////////////
/*
Read graphs into Nauty format and save in 2d array graph g
*/                 
/////////////////////////////////////////////////////////////////////////

	while ((read = getline(&line, &len, file)) != -1){
	
		//printf("%c %c %c \n", line[0],line[1],line[2]);
		stringtograph(line,g[i],m);
		i+=1;
	}

	fclose(file);

/////////////////////////////////////////////////////////////////////////
/*
Create canonical graphs
*/                 
/////////////////////////////////////////////////////////////////////////
	
/*	DYNALLOC2(graph,cg1,cg1_sz,n,m,"malloc");
	DYNALLOC2(graph,cg2,cg2_sz,n,m,"malloc");

	for(i1 = 0; i1<count-1 ; i1++){
		if(g[i1][0] == -1){
			continue;
		}
		for(i2 = i1+1; i2<count ; i2++){
			if(g[i2][0] == -1){
				continue;
			}

			else{
				densenauty(g[i1],lab1,ptn,orbits,&options,&stats,m,n,cg1);
				densenauty(g[i2],lab2,ptn,orbits,&options,&stats,m,n,cg2);		
			*/
      
/////////////////////////////////////////////////////////////////////////
/*
Compare canonical graphs
*/                 
/////////////////////////////////////////////////////////////////////////
/*
				for (k1 = 0; k1 < m*(size_t)n; ++k1){
		
					if (cg1[k1] != cg2[k1]) break;
				}
			
				if (k1 == m*(size_t)n)
				{
					g[i2][0] = -1;	
				}
		
			}
		}
	}
	*/
/////////////////////////////////////////////////////////////////////////
/*
Print
*/                 
/////////////////////////////////////////////////////////////////////////	
	/*for(k = 0; k<count; k++){
		if(g[k][0] != -1){
			i3 +=1;
		}
	}
	printf("count is %d \n", count);
	printf("There are %d non-isomorphic graphs \n",i3);*/

	 
	l = FIRSTBIT(g[0][0]);
	printf("%d \n", l);

	x = g[0][0];
	//x = (g[0][0] >> (63-3));
for(i = 63; i>=0; i--){

	//printf("%d \n", i);

	x1 = g[0][0] >> i;
	
	if(x1 & 1){
		printf("1");
	}

	else{
		printf("0");
	}
}
	exit(0);

}
