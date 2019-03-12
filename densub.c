#include "nauty.h"
#include <unistd.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//This algorithm works for storing graphs in nauty and applying dense subgraph extraction
//algorithm by Jie Chen and Yousef Saad.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Calculates inner product between two rows in the lower half of an adjacency matrix stored in nauty
//format.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int prod(long int * a, int x,int y, int l, int m){
	int i,j,k;
	long int c,d;

	k = 0;	

	for(j = 0; j<m; j++){
		c = a[l*m+x*m+j];
		d = a[l*m+y*m+j];
		
		for(i = 63; i>= 0; i--){
			if(((c >>i) & 1)&&((d >> i) & 1)){
				k+=1;
			}
		}
	}

	return(k);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////
////Calculates euclidean norm squared of a row in the lower half of an adjacency matrix stored in nauty
////format.
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int norm(long int* a, int x, int l, int m){

	int i,j, k;

	long int c;
	
	k = 0;

	for(j = 0; j<m; j++){

		c = a[l*m+x*m+j];

		for(i = 63; i >= 0l; i--){
			if((c>>i) & 1){
				k+=1;
			}
		}
	}

	return(k);

} 	 
			
	


int main(){
	int i,j,k,l,m,n,a,b,u1,u2,u3;
	double r;
	FILE *file;
	int *v1;
	int *v2;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	long int b1;
	int count;

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

	printf("m = %d, n = %d, l = %d,a = %d, b = %d \n", m,n,l,a,b);

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

///////////////////////////////////////////////////////////////////////////////////////
////
////Store the square of the angle between two rows in the lower halfplane in matrix angle
////NOTE: DOUBLE READING AS 0, NEED TO FIX (EVERYTHING ELSE WORKS)
///////////////////////////////////////////////////////////////////////////////////////  	

	double **angle = (double **)malloc(l*sizeof(double*));
	
	for(i = 0; i<l; i++){
		angle[i] = (double *)malloc(l*sizeof(double));

	}

	for(i = 0; i<l-1; i++){
		for(j = i+1; j<l; j++){
			u1 = prod(plane, i,j,l,m);
			u2 = norm(plane, i,l,m);
			u3 = norm(plane,j,l,m);
			printf(" %d %d %d \n", u1,u2,u3);
			r = (u1*u1)/(u2*u3);
			angle[i][j] = r;
			angle[j][i] = r;
		//	printf("%lf ", r);  
		}
	}

	/*for(i = 0; i<l;i++){
		for(j = 0; j<l; j++){
			printf("%lf ", angle[i][j]);
		}
	}*/		
			 

/*
	for(i = 63; i>= 0; i--){
		b1 = plane[m-1] >> i;

		if(b1 & 1){
			printf("1");
		}

		else{
			printf("0");
		}
	
 	}

	printf("\n");
*/
/*
        file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/g61.txt","w");
                if(file==NULL){
                            printf("EXIT_FAILURE \n");
                }

	writeg6(file,plane,m,n);

*/

	return 0;

}
