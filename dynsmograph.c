//#define MAXN 1000    /* Define this before including nauty.h */
//#define MAXCHAR 1000
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
//converts every entry pointed to by a equal to 0
//////////////////////////////////////////////////////////	

int zeroall(int *a,int n){

	int i;
	
	for(i=0; i<n; i++){
		a[i] = 0;
	}

	return(0);
}

//////////////////////////////////////////////////////////
//converts every entry pointed to by a equal to 0
//////////////////////////////////////////////////////////	

int longzeroall(long int *a,int n){

	int i;
	
	for(i=0; i<n; i++){
		a[i] = 0;
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

int first2(int *a, int n){

	int i,k;

	k = n;

	for(i =1; i<n;i++){
		if(a[i] == n+1){
			k = i;
			break;
		}
	}

	
	return(k);

}

/*
int numorbits(int *a,int *b, int n){

	int i,k,j;

	k = 0;

	for(i = 0; i<n; i++){
		for(j = 0; j<i;j++){
				
*/	

int first3(int *a, int n){

	int i,k;

	k = n;

	for(i =1; i<n;i++){
		if(a[i] == 0){
			k = i;
			break;
		}
	}

	
	return(k);

}

int order(int *a,int n){
	int i,k;

	k = 0;

	for(i=0; i< n-1; i++){
		if(a[i+1] != a[i] +1){
			k = 1;
			break;
		}
	}

	return k;
}

int order2(int *a,int n){

	int i,j,t;
	for(i = 0; i<n-1; i++){
		for(j = i; j<n;j++){
			if(a[i]>=a[j]+1){
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}

	return(0);

}
				
int choose(int *a, int x, int n){
	int i;
	for(i = 0; i<n; i++){
		if(a[i] == x){
			return(i);
		}
	}
}
			

long int swap(long int x, int p1, int p2){

	long int set1,set2,xor,res;

	set1 = (x>> (63-p1)) & ((1u << 1)-1);

	set2 = (x>> (63-p2)) & ((1u << 1)-1);

	xor = (set1^set2);

	xor = (xor<<(63-p1))|(xor<<(63-p2));

	res = x ^ xor;

	return(res);
}

int min(int x, int y){

	if(x <= y){
		return(x);
	}

	else{
		return(y);
	}
}


void autsize(double gpsize1, int gpsize2)
{
    if (gpsize2 == 0)
        printf("%.0f \n",gpsize1+0.1);
    else
    {
        while (gpsize1 >= 10.0)
        {
            gpsize1 /= 10.0;
            ++gpsize2;
        }
        printf("%14.12fe%d \n",gpsize1,gpsize2);
    }
}

int autsize2(double gpsize1, int gpsize2)
{
    int c,b,a,i;

    a = 1;

    if(gpsize2 == 0){
    	b = gpsize1+0.1;
	return(b);
	}
    else{
	for(i = 0; i<gpsize2; i++){
		a*= 10;	
	}
	
	b= gpsize1+0.1;

	c = b+a;

	return(c);
	
    }
}

int getpoint(long int *a,int n){
	
	int i,j,k,l;

	long int x;

	k = n+1;
               
	for(j = 0; j<n;j++){
                            
		for(i = 63; i >= 0; i--){
        		x = a[j] >> i;
        		if(x & 1){
				l = 63-i;
                	//	return(63-i);
				break;
       			}
		}
		
		if(l <= k){
			k = l;
		}
	}

	return(k);

}

int main(){
int i,i8,j,j1,k,l,m,n,a,d,e,f,h,f1,e1,d1,c1,c2,flag1,flag2,u,u1,u2,v1,v2,count1,count2,z,z2,gp,p,q1,q2,nump;
long int y, bin1, bin2,temp;
FILE *file;
double half;
int b[n];
int q[n];
int b1[n];
int b2[n];
int b3[n];
int b4[n];
int hold[n];
int hold2[n];
int plines[n];
int norbits[n];

static DEFAULTOPTIONS_GRAPH(options);
	statsblk stats;
	size_t k1;
	int lab[n],ptn[n],orbits[n];
	int i1,i2,i3;
	unsigned int x;			//Used to test how to read graphs


  	
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
	n=12;
	m = SETWORDSNEEDED(n);		//m = ceiling(n/64)

	sleep(.001);


	file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/plspace12.txt","r");
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

/*	long int ** g = (long int **)malloc(count*sizeof(long int*));
	
	for(i = 0; i< count; i++){
		g[i] = (long int*)malloc(m*sizeof(long int));
	}
	*/
	long int ** g1 = (long int **)malloc(count*sizeof(long int*));
	
	for(i = 0; i< count; i++){
		g1[i] = (long int*)malloc(m*n*sizeof(long int));
	}

	long int ** g2 = (long int **)malloc(count*sizeof(long int*));
	
	for(i = 0; i< count; i++){
		g2[i] = (long int*)malloc(m*n*sizeof(long int));
	}

	 int ** c = (int **)malloc(count*sizeof(int*));
	
	for(i = 0; i< count; i++){
		c[i] = (int*)malloc(n*m*sizeof(int));
	}

	int *** t = (int ***)malloc(count*sizeof(int**));
	
	for(i = 0; i< count; i++){
		t[i] = (int**)malloc(n*m*sizeof(int*));
	

		for(j = 0; j<n*m; j++){
			t[i][j] = (int*)malloc(n*sizeof(int));
		}
	}


	int *** change = (int ***)malloc(count*sizeof(int**));
	
	for(i = 0; i< count; i++){
		change[i] = (int**)malloc(2*sizeof(int*));
	

		for(j = 0; j<2; j++){
			change[i][j] = (int*)malloc(n*m*sizeof(int));
		}
	}

/*
	int *gr = (int *)malloc(count*sizeof(int));

	int *counter = (int *)malloc(count*sizeof(int));	

	int **part = (int **)malloc(n*sizeof(int*));
	for(i = 0;i<n;i++){
		part[i] = (int*)malloc(count*sizeof(int));
	}	
	
*/

	rewind(file);

/////////////////////////////////////////////////////////////////////////
/*
Read graphs into Nauty format and save in 2d array graph g1
*/                 
/////////////////////////////////////////////////////////////////////////

	i= 0;
//	printf("%d \n",m);
	while ((read = getline(&line, &len, file)) != -1){
		stringtograph(line,g1[i],m);
		sleep(.1);
		i+=1;
	}

	
	
	fclose(file);

	//printf("i = %d \n", i);	
	
	sleep(.001);

/////////////////////////////////////////////////////////////////////////
/*
Copy g into g1 and g2
*/                 
/////////////////////////////////////////////////////////////////////////

	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			g2[i][j] = g1[i][j];
		}
	}

/*
	for(i =0; i<count; i++){
		for(j = 0; j<n*m; j++){
			g2[i][j] = g[i][j];
		}
	}

	free(g);
*/
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

	free(g1);
				
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

		copy(b1, change[i][0],n);
		copy(b2, change[i][1],n);

	}

}
	free(c);

	free(t);

/////////////////////////////////////////////////////////////////////////
/////*
////Write partitions of vertices to disk
////*/
////////////////////////////////////////////////////////////////////////
//

/*
	file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/15partition.txt","w");
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
*/




/////////////////////////////////////////////////////////////////////////
///*
//For testing purposes
//*/
///////////////////////////////////////////////////////////////////////////
//

/*
	y = swap(g2[8][0],5,6);
                                           
	for(i = 63; i >= 0; i--){
        	bin2 = y >> i;

        	if(bin2 & 1){
                	printf("1");
        	}

        	else{
                	printf("0");
        	}
	}
	printf("\n");
*/	
////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
///*
//Rearranges rows and columns of adj matrix of graph so that points are first, then lines
//*/
///////////////////////////////////////////////////////////////////////////

	for(i = 0;i<count;i++){

		v1 = first2(change[i][0],n);
		v2 = first2(change[i][1],n);

		order2(change[i][0],v1);

		//printf("%d \n", v1);
	
		if(order(change[i][0],v1)==0){
			continue;
		}

		for(j = 0; j<v1; j++){
			b3[j] = change[i][0][j];
		}

		for(j = 0; j<v2; j++){
			b3[j+v1] = change[i][1][j];
		}

		//for(j = 0; j<n; j++){
		//	printf("%d ",b3[j]);
		//}

		//printf("\n");
		
		for(j = 0; j<n; j++){
			b4[j] = j;
		}


		for(j=1; j<v1; j++){
			
			z = b4[j];
			z2 = choose(b4,b3[j],n);
			b4[j] = b3[j];
			b4[z2] = z;			

			temp = g2[i][j];
			g2[i][j] = g2[i][b4[j]];
			g2[i][z2] = temp;					

			for(k = 0; k<n; k++){
				g2[i][k] = swap(g2[i][k], j, z2);
			}		

		}	

		
	}
	

/////////////////////////////////////////////////////////////////////////
///*
//Print out graphs in smo
//*/
///////////////////////////////////////////////////////////////////////////
/*
	for(i = 0; i<count; i++){
		printf("Graph = %d \n", i+1);
		for(k = 0;k<n;k++){
			for(j = 63; j >= 63-(n-1); j--){
               			bin2 = g2[i][k] >> j;

                		if(bin2 & 1){
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
        printf("\n");
*/
////////////////////////////////////////////////////////////////////////////////


/*	int *gr = (int *)malloc(count*sizeof(int));

	int **part = (int **)malloc(n*sizeof(int*));
	for(i = 0;i<n;i++){
		part[i] = (int*)malloc(count*sizeof(int));
	}	



	zeroall(gr,count);
	for(i = 0;i<n;i++){
		zeroall(part[i],count);
	}
*/

/////////////////////////////////////////////////////////////////////////
///*
//Prints out table with cardinalities of automorphism groups
//*/
///////////////////////////////////////////////////////////////////////////
/*	
for(j = 0; j<count;j++){	
	
	densenauty(g2[j],lab,ptn,orbits,&options,&stats,m,n,NULL);

	gp = autsize2(stats.grpsize1,stats.grpsize2);

	//printf("gp = %d \n",gp);
	
	flag1 = 0;

	for(i = 0; i<count;i++){
		if(gp == gr[i]){
			flag1 = 1;
			break;
		}
	}

	if(flag1 == 0){
		q1 = first3(gr,count);
		if(q1 != count){
			gr[q1] = gp;
			//printf("%d %d \n", gr[q1],q1);
		}
	}
}	


	
	q1 = first3(gr,count);

//	printf("%d \n", q1);

	order2(gr,q1);

	for(j = 0; j<count; j++){
		densenauty(g2[j],lab,ptn,orbits,&options,&stats,m,n,NULL);

		gp = autsize2(stats.grpsize1,stats.grpsize2);

		q2 = first2(change[j][0],n);

		//q2 = getpoint(g2[j],n);

	//	printf("%d \n", q2);

		for(i = 0; i<q1; i++){
			if(gp == gr[i]){
			//	printf("q2 =  %d\n", q2);
				part[q2][i] +=1;
				break;
			}
		}
	}


	for(i = 1; i<q1-1; i++){
		printf("%d " ,gr[i]);
	}

	printf("\n");
	for(j= 0; j<n; j++){
		for(i = 1; i<q1; i++){
			printf("%d ", part[j][i]);
		}
		printf("\n");
	}

	free(gr);				//free gr
	free(part);				//free part (contains cardinalities of aut groups)


*/


/////////////////////////////////////////////////////////////////////////
///*
//If n is even, checks if plane is self dual or not by seeing orbits of the action of automorphism group
//*/
///////////////////////////////////////////////////////////////////////////

/*
f = n/2;

for(j = 0; j<count;j++){	

	q2 = first2(change[j][0],n);

//	printf("%d, %d \n", q2,f);	

	if(q2 == f){

	//	printf("%d \n", q2);

		e = 0;

		//k = 1;

		densenauty(g2[j],lab,ptn,orbits,&options,&stats,m,n,NULL);

		sleep(0.1);
	

		for(l = 0; l<q2; l++){
			for(h = q2; h<n; h++){ 	
		//		printf("%d, %d \n", orbits[l], orbits[h]);	
				if(orbits[l] == orbits[h]){
					for(i = 0; i<n; i++){
						printf("%d ", orbits[i]);
					}

					printf("\n");
			
					//printf(" l = %d, h = %d, j = %d \n",l,h, j);
					e = 1;
					break;
				}
			}


			if(e ==1){
				break;
			}
		}
		 
	

	}
		
}		

*/	

	free(change);				//free change (contains partition into points and lines)

/////////////////////////////////////////////////////////////////////////
///*
//Reads projective planes in Moorhouse format
//*/
///////////////////////////////////////////////////////////////////////////

	file = fopen("/home/jfloresm/Documents/Research/linspace/25s1.txt","r");
		//printf("2\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}


	k = 0;

	while((read = getline(&line, &len, file)) != -1){
		k+=1;
	}

	a = 25; //order of plane

	l = a*a+a+1; //number of points

	j1 = a+1; // number of lines through any point

	int** plane = (int**)malloc(l*sizeof(int*));

	for(i = 0; i<l;i++){
		plane[i] = (int*)malloc(j1*sizeof(int));
	}

	rewind(file);

	d = 0;

	for(i = 0; i < l; i++){
		for(j = 0; j<j1; j++){
			if(!fscanf(file, "%d",&plane[i][j])){
				break;
			}
		}
	}
/*
	for(i = 0; i < l; i++){
		for(j = 0; j<j1; j++){
			printf("%d ", plane[i][j]);
		}
		printf("\n");
		printf("\n");
	}	
*/
	fclose(file);


/////////////////////////////////////////////////////////////////////////
///*
//Convert projective planes into nauty format
//*/
///////////////////////////////////////////////////////////////////////////

/*
	u = 2*l;

	v = SETWORDSNEEDED(u);
	

	long int *biplane = (long int*)malloc(u*v*sizeof(long int));

	longzeroall(biplane,u*v);

	for(i = 10*v; i<u*v;i++){}
		
		

	//free(plane);				//free projective plane
*/


/*

 file = fopen("/home/jfloresm/Documents/Research/linspace/graphs/g61.txt","w");
                if(file==NULL){
                            printf("EXIT_FAILURE \n");
                }

	writeg6(file,g2[0],m,n);


fclose(file);
*/
	return 0;
		//printf("\n");

}



