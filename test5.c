#define MAXN 1000    /* Define this before including nauty.h */
#define MAXCHAR 1000
#include "nauty.h"   /* which includes <stdio.h> and other system files */
//#include <stdio.h>
#include <unistd.h>

//////////////////////////////////////////////////////////
//If b is pointed to by a return 0, else return 1
//////////////////////////////////////////////////////////

int notin(int *a,int b,int n){

	int i,k;

	k = 1;

	for(i = 0; i<n; i++){
		if(b == a[i]){
			k=0;
			break;
		}

	}

	return(k);

}


//////////////////////////////////////////////////////////
//converts every entry pointed to by a equal to n+1
//////////////////////////////////////////////////////////	

int zero(int *a,int n){

	int i;
	
	for(i=0; i<n; i++){
		a[i] = n+1;
	}

	return(0);
}

//////////////////////////////////////////////////////////
//Copies vector a unto vector b
//////////////////////////////////////////////////////////	

int copy(int *a, int *b, int n){

	int i;
	
	for(i=0; i<n; i++){
		b[i] = a[i];
	}

	return(0);
}

//////////////////////////////////////////////////////////
//converts every entry pointed to by a equal to n+1
//////////////////////////////////////////////////////////	

int nzero(int *a,int n){

	int i;
	
	for(i=0; i<n; i++){
		a[i] = -1;
	}

	return(0);
}

//////////////////////////////////////////////////////////
//returns the first entry pointed to by a equal to n+1, returns -1 if all entries are not equal to n+1
//////////////////////////////////////////////////////////

int first(int *a, int n){

	int i,k;

	k = -1;

	for(i =0; i<n;i++){
		if(a[i] == n+1){
			k = i;
			break;
		}
	}

	
	return(k);

}

int main(){
int i,i8,j,j1,k,l,m,n,a,d,e,f,h,f1,e1,d1,c1,c2,flag1,flag2,u,u1,u2;
FILE *file;

int b[n];
int q[n];
int b1[n];
int b2[n];


//static DEFAULTOPTIONS_GRAPH(options);
//	statsblk stats;
	//size_t k1;
	//int i1,i2,i3;
	//unsigned int x;			//Used to test how to read graphs


  	
/* Select option for canonical labelling */


	//options.getcanon = TRUE;



	char *line = NULL;		//Will contain graph in graph6 format
	size_t  len = 0; 		//Length of line to be read
	ssize_t read;			//Value of Getline (should be >= 0).
	int count;			//Counts number of lines in text file	z


/* Default options are set by the DEFAULTOPTIONS_GRAPH macro above.
Here we change those options that we want to be different from the
defaults.  writeautoms=TRUE causes automorphisms to be written.     */
	//options.writeautoms = TRUE;

	//scanf("%d", &n);		//Number of vertices
	n=7;
	m = SETWORDSNEEDED(n);		//m = ceiling(n/64)

	sleep(.001);


	file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/plspace7.txt","r");
		//printf("2\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}


/////////////////////////////////////////////////////////////////////////
/*
Count number of graphs in each file
*/                 
/////////////////////////////////////////////////////////////////////////

	count = 0;

	while ((read = getline(&line, &len, file)) != -1){
	
		count+=1;
	}

	graph g[count][n*m];		// 2 d array. 1st dimension tells you which graph
	graph g1[count][n*m];		// 2 d array. 1st dimension tells you which graph
	int c[count][n*m];		//each row is number of 1's in each row of g
	int t[count][n*m][n];		// each row is the position of 1's in each row of g

	int change[count][2][n*m];	//will contain partitions of bipartite graph
	
	rewind(file);

/////////////////////////////////////////////////////////////////////////
/*
Read graphs into Nauty format and save in 2d array graph g
*/                 
/////////////////////////////////////////////////////////////////////////

	i= 0;

	while ((read = getline(&line, &len, file)) != -1){
	
		//printf("%c %c %c \n", line[0],line[1],line[2]);
		stringtograph(line,g[i],m);
		sleep(.1);
		i+=1;
	}

	
	
	fclose(file);

	//printf("i = %d \n", i);	
	
	sleep(.001);

/////////////////////////////////////////////////////////////////////////
/*
Copy g into g1
*/                 
/////////////////////////////////////////////////////////////////////////

	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			g1[i][j] = g[i][j];
		}
	}



/////////////////////////////////////////////////////////////////////////
/*
Gives number of 1's in each row of adj matrix
*/                 
/////////////////////////////////////////////////////////////////////////

	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			c[i][j] = POPCOUNT(g1[i][j]);
			sleep(.1);
			//printf("%d \n", c[i][j]);
		}
	}

/////////////////////////////////////////////////////////////////////////
/*
zeros the matrix which will contain the adjacency of each row
*/                 
/////////////////////////////////////////////////////////////////////////

	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			sleep(.1);
			zero((t[i][j]),n);
		}
	}

/////////////////////////////////////////////////////////////////////////
/*
copies location of 1 in each row of adj matrix into t
*/                 
/////////////////////////////////////////////////////////////////////////

	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			for(k = 0; k<c[i][j]; k++){
				TAKEBIT(t[i][j][k],g1[i][j]);
				sleep(.1);				
			}
		}
	}
				
/////////////////////////////////////////////////////////////////////////
/*
Test that graphs are read properly
*/                 
/////////////////////////////////////////////////////////////////////////

/*for(i = 63; i >= 0; i--){
	bin2 = g1[1][0] >> i;

	if(bin2 & 1){
		printf("1");
	}

	else{
		printf("0");
	}
}

*/

/////////////////////////////////////////////////////////////////////////
///*
//For each graph, create two vectors b1,b2, which correspond to the vertex partition of each graph, and save them into array change for further use
//*/
///////////////////////////////////////////////////////////////////////////

for(i = 0; i < count; i++){
	
	a = c[i][0];
	nzero(q,n);
	zero(b1,n);
	zero(b2,n);
	zero(b,n);
	b1[0] = 0;
	h = 0;	
	u = 0;
	f = 0;
	f1 = 0;
	e = 0;
	d = 1;

	for(l = 0; l<a; l++){
		b[l] = t[i][h][l];    //0 to WORDSIZE -1
		continue;
	}	

	while((e+d)!=n && (u<n)){
		
		q[u] = h;
//		printf("u = %d, h = %d, f = %d, f1 = %d\n", u,h,f,f1);
	
		if(u %2 == 0){

			for(j= 0; j<a; j++){
				if(notin(b2,b[j],n)==1){
					b2[e] = b[j];
					//printf("%d %d \n", b2[e],b[j]);
					e+=1;
				}
			}
//			printf(" b%d is %d %d %d %d %d %d %d \n", h,b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
			
//			printf(" b      2 is %d %d %d %d %d %d %d \n", b2[0],b2[1],b2[2],b2[3],b2[4],b2[5],b2[6]);
			
			h = b2[f];

			f1+=1;

			a = c[i][h];
			
			zero(b,n);
			for(j = 0; j<a; j++){
				b[j]=t[i][h][j];    //0 to WORDSIZE -1
				continue;
			}
			
			//printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);
			c1 = 0;

			for(j= 0; j<a; j++){
				if(notin(q,b[j],n)==0){
					c1+=1;
				}
			}
			
			if(c1 == first(b,n)){
				flag1 = 1;
				f+=1;
				if(b2[f] == (n+1)){
					h = b1[f1];
					a = c[i][h];
					zero(b,n);
					for(j = 0; j<a; j++){
						b[j]=t[i][h][j];    //0 to WORDSIZE -1
						continue;
					}
					u +=1;
				}

				else{
					h = b2[f];
				}
				
			}

			else{
				flag1 =0;
			}

			u1 = u;

			while(flag1 == 1 && f != n && (u1%2 == 0)){
				a = c[i][h];
				zero(b,n);
				for(j = 0; j<a; j++){
					b[j]=t[i][h][j];    //0 to WORDSIZE -1
					continue;
				}

					
	
				c1 = 0;

				for(j = 0; j<a; j++){
					if(notin(q,b[j],n)==0){
						c1+=1;
					}
				}

	
				if(c1 == first(b,n)){
					flag1 = 1;
					f+=1;
					if(b2[f] == (n+1)){
						h = b1[f1];
						a = c[i][h];

						zero(b,n);
						for(j= 0; j<a; j++){
							b[j]=t[i][h][j];    //0 to WORDSIZE -1
							continue;
						}
						u1 += 1;
						u = u1;
					}

					else{
						h = b2[f];
					}
				
				}

				else{
					flag1 =0;
				}
			}		
				
						
		}
		
		else{
			for(j= 0; j<a; j++){
				if(notin(b1,b[j],n)==1){
					b1[d] = b[j];
					d+=1; 
				}
			}
			
		//	printf(" b%d is %d %d %d %d %d %d %d \n", h,b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
			
		//	printf(" b      1 is %d %d %d %d %d %d %d \n", b1[0],b1[1],b1[2],b1[3],b1[4],b1[5],b1[6]);
			
			f +=1;
			
			h = b1[f1];
			
			a = c[i][h];
			
			zero(b,n);
			for(j = 0; j<a; j++){
				b[j]=t[i][h][j];    //0 to WORDSIZE -1
				continue;
			}
			
			c2 = 0;

			for(j= 0; j<a; j++){
				if(notin(q,b[j],n)==0){
					c2 += 1;
				}
			}			
			
			if(c2 == first(b,n)){
				flag2 = 1;
				f1+=1;
				if(b1[f1] == (n+1)){
					h = b2[f];
					a = c[i][h];
					zero(b,n);
					for(j = 0; j<a; j++){
						b[j]=t[i][h][j];    //0 to WORDSIZE -1
						continue;
					}
					
					u+=1;
				}
				
				else{
					h = b1[f1];
				}
			}

			else{
				flag2 =0;
			}

			u2 = u;

			while(flag2 == 1 && f1 != n&&(u2 %2 == 1)){
				a = c[i][h];

				zero(b,n);
				for(j= 0; j<a; j++){
					b[j]=t[i][h][j];    //0 to WORDSIZE -1
					continue;
				}

				c2 = 0;

				for(j = 0; j<a; j++){
					if(notin(q,b[j],n)==0){
						c2+=1;
					}
				}
			
	
				if(c2 == first(b,n)){
					flag2 = 1;
					f1+=1;
					if(b1[f1] == (n+1)){
						h = b2[f];
						a = c[i][h];

						zero(b,n);
						for(j= 0; j<a; j++){
							b[j]=t[i][h][j];    //0 to WORDSIZE -1
							continue;
						}
						u2+=1;
						u = u2;
					}
				
					else{
						h = b1[f1];
					}
				
				}

				else{
					flag2 =0;
				}
			}	
			
		}
					
		u +=1;
		e = first(b2,n);
		d = first(b1,n);

		//printf("f = %d, f1 = %d \n", f, f1);

		//printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d,b1[4] = %d,b1[5] = %d,b1[6] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d,b2[4] = %d,b2[5] = %d,b2[6] = %d \n", b1[0], b1[1],b1[2], b1[3],b1[4], b1[5],b1[6],b2[0], b2[1],b2[2], b2[3],b2[4], b2[5],b2[6]);

	}
		//printf("i = %d \n",i);
		//printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d,b1[4] = %d,b1[5] = %d,b1[6] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d,b2[4] = %d,b2[5] = %d,b2[6] = %d \n", b1[0], b1[1],b1[2], b1[3],b1[4], b1[5],b1[6],b2[0], b2[1],b2[2], b2[3],b2[4], b2[5],b2[6]);
		//printf("\n");
	
//printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d \n", b1[0], b1[1],b1[2], b1[3],b2[0], b2[1],b2[2], b2[3]);
		copy(b1, change[i][0],n);
		copy(b2, change[i][1],n);

}

	file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/7partition.txt","w");
        if(file==NULL){
                printf("EXIT_FAILURE \n");
        }

	for(i = 0; i< count; i++){
		for(j = 0; j< 2; j++){
			for(k=0; k<n; k++){
				fprintf(file,"%d ", change[i][j][k]);
			}
			fprintf(file,"\n");
		}
		fprintf(file,"\n");
	}

	
	fclose(file);
		

	                                                        



return 0;

}

