#define MAXN 1000    /* Define this before including nauty.h */
#define MAXCHAR 1000
#include "nauty.h"   /* which includes <stdio.h> and other system files */

//////////////////////////////////////////////////////////
//If b is pointed to by a return 0, else return 1
//////////////////////////////////////////////////////////

int notin(int *a,int b,int n){

	int t1,t2;

	t2 = 1;

	for(t1 = 0; t1<n; t1++){
		if(b == a[t1]){
			t2=0;
			break;
		}

	}

	return(t2);

}


//////////////////////////////////////////////////////////
//converts every entry pointed to by a equal to n+1
//////////////////////////////////////////////////////////	

int zero(int *a,int n){

	int t1;
	
	for(t1=0; t1<n; t1++){
		a[t1] = n+1;
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
int i,i8,j,j1,k,l,m,n,a,d,e,f,h,f1,e1,d1,c1,c2,flag1,flag2,u,a1,k3,k2;
//unsigned int bin;
//unsigned int bin2;
FILE *file;

int b[n];
int q[n];
int b1[n];
int b2[n];


static DEFAULTOPTIONS_GRAPH(options);
	statsblk stats;
	//size_t k1;
	//int i1,i2,i3;
	//unsigned int x;			//Used to test how to read graphs
  	
/* Select option for canonical labelling */
	options.getcanon = TRUE;



	char *line = NULL;		//Will contain graph in graph6 format
	size_t  len = 0; 		//Length of line to be read
	ssize_t read;			//Value of Getline (should be >= 0).
	int count;			//Counts number of lines in text file	z


/* Default options are set by the DEFAULTOPTIONS_GRAPH macro above.
Here we change those options that we want to be different from the
defaults.  writeautoms=TRUE causes automorphisms to be written.     */
	//options.writeautoms = TRUE;

	//printf("Integer 2 <= n <= 8: \n");
	//scanf("%d", &n);		//Number of vertices
	n=7;
	m = SETWORDSNEEDED(n);		//m = ceiling(n/64)




	file = fopen("/home/jfloresm/Documents/Research/linspace/nauty26r11/plspace7.txt","r");
		//printf("2\n");
		if(file==NULL){
			printf("EXIT_FAILURE \n");
		}


/////////////////////////////////////////////////////////////////////////
/*
Count number of graphs in each file
*/                 
/////////////////////////////////////////////////////////////////////////

	//fgets(s,MAXCHAR,file);

	//i=0;
	//k=0;
	//i3=0;
	count = 0;

	while ((read = getline(&line, &len, file)) != -1){
	
		count+=1;
	}

	graph g[count][n*m];		// 2 d array. 1st dimension tells you which graph
	graph g1[count][n*m];		// 2 d array. 1st dimension tells you which graph
	int c[count][n*m];
	int t[count][n*m];
	
	rewind(file);
//printf("hi\n");
/////////////////////////////////////////////////////////////////////////
/*
Read graphs into Nauty format and save in 2d array graph g
*/                 
/////////////////////////////////////////////////////////////////////////

	i8= 0;

	while ((read = getline(&line, &len, file)) != -1){
	
		//printf("%c %c %c \n", line[0],line[1],line[2]);
		stringtograph(line,g[i8],m);
		i8+=1;
	}

	fclose(file);

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

///////////////////////////////////////////////////////////////////


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

//printf("hi\n");
//a1 = FIRSTBIT(g1[2][1]);
//printf("before...     a1 = %d\n", a1);

for(i = 0; i < count; i++){
	for(j = 0; j< n*m; j++){
		


for(i = 0; i < count; i++){

	a1 = FIRSTBIT(g1[2][1]);
		printf("before...     a1 = %d, i =%d\n", a1,i);

	nzero(q,n);
	//printf("q is %d %d %d %d %d %d %d \n",h, q[0],q[1],q[2],q[3],q[4],q[5]);
	//printf("h \n");
	zero(b1,n);
	zero(b2,n);
	zero(b,n);
	b1[0] = 0;
	//q[0] = 0;
	h = 0;		
	u = 0;
	f = 0;
	f1 = 0;
	e = 0;
	d = 1;

	a = POPCOUNT(g1[i][0]);

	
	for(l = 0; l<a; l++){
		TAKEBIT(b[l],g1[i][0]);    //0 to WORDSIZE -1
		continue;
		
	}

	while((e+d)!=n){
		
		//nzero(q,n);
		q[u] = h;
		printf("u = %d, h = %d\n", u,h);
		//printf("q[2] = %d \n", q[2]);
		//printf(" q%d is %d %d %d %d \n",h, q[0],q[1],q[2],q[3]);

		if(u %2 == 0){

			for(j= 0; j<a; j++){
				if(notin(b2,b[j],n)==1){
					b2[e] = b[j];
					e+=1;
				}
			}
			printf(" b%d is %d %d %d %d %d %d %d \n", h,b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
			
			printf(" b      2 is %d %d %d %d %d %d %d \n", b2[0],b2[1],b2[2],b2[3],b2[4],b2[5],b2[6]);
			
			h = b2[f];

			

			f1+=1;

			a = POPCOUNT(g1[i][h]);
			
			zero(b,n);
			for(j = 0; j<a; j++){
				TAKEBIT(b[j],g1[i][h]);    //0 to WORDSIZE -1
				continue;
			}
			
			printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);
			c1 = 0;

			for(j= 0; j<a; j++){
				if(notin(q,b[j],n)==0){
					c1+=1;
				}
			}
			
			if(c1 == first(b,n)){
				flag1 = 1;
				f+=1;
				h = b2[f];
				printf("h=%d \n", h);
				
			}

			else{
				flag1 =0;
			}

			while(flag1 == 1 && f != n){
				a = POPCOUNT(g1[i][h]);
				zero(b,n);
				for(j = 0; j<a; j++){
					TAKEBIT(b[j],g1[i][h]);    //0 to WORDSIZE -1
					continue;
				}

					
	
				c1 = 0;

				for(j = 0; j<a; j++){
					if(notin(q,b[j],n)==0){
						c1+=1;
					}
				}

				//printf("c1=%d \n", c1);
				//printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);			
	
				if(c1 == first(b,n)){
					flag1 = 1;
					f+=1;
					h = b2[f];
				
				}

				else{
					flag1 =0;
				}
			}		
				
						
		}
		
		else{
			//printf(" b      1 is %d %d %d %d \n", b1[0],b1[1],b1[2],b1[3]);
			for(j= 0; j<a; j++){
				if(notin(b1,b[j],n)==1){
					b1[d] = b[j];
					d+=1;
					//printf("d = %d, b1[d] = %d\n", d, b1[d-1]); 
				}
			}
			

			printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);
			
			printf(" b      1 is %d %d %d %d \n", b1[0],b1[1],b1[2],b1[3]);
			
			f +=1;
			
			h = b1[f1];
			a1 = FIRSTBIT(g1[i][h]);
			a = POPCOUNT(g1[i][h]);
			//a = a1;
			printf("a1 = %d, h = %d \n", a1,h);
			

			
			zero(b,n);
			for(j = 0; j<a; j++){
				TAKEBIT(b[j],g1[i][h]);    //0 to WORDSIZE -1
				continue;
			}
			printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);
			
			//printf(" b      2 is %d %d %d %d \n", b2[0],b2[1],b2[2],b2[3]);
			
			c2 = 0;

			for(j= 0; j<a; j++){
				if(notin(q,b[j],n)==0){
					c2 += 1;
				}
			}			
			
			if(c2 == first(b,n)){
				flag2 = 1;
				f1+=1;
				h = b1[f1];
				
			}

			else{
				flag2 =0;
			}

			while(flag2 == 1 && f1 != n){
				a = POPCOUNT(g1[i][h]);

				zero(b,n);
				for(j= 0; j<a; j++){
					TAKEBIT(b[j],g1[i][h]);    //0 to WORDSIZE -1
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
					h = b1[f1];
				
				}

				else{
					flag2 =0;
				}
			}	
			
		}
					
		u +=1;
		e = first(b2,n);
		d = first(b1,n);
		//a1 = FIRSTBIT(g[2][1]);
		//printf("before...     a1 = %d\n", a1);


	}
/*
	for(k3 =0; k3<count; k3++){
		for(k2 = 0; k2<n*m; k2++){
			g1[k3][k2] = g[k3][k2];
		}
	}
*/
	a1 = FIRSTBIT(g1[2][1]);
		printf("before...     a1 = %d, i =%d\n", a1,i);
	
		printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d,b1[4] = %d,b1[5] = %d,b1[6] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d,b2[4] = %d,b2[5] = %d,b2[6] = %d \n", b1[0], b1[1],b1[2], b1[3],b1[4], b1[5],b1[6],b2[0], b2[1],b2[2], b2[3],b2[4], b2[5],b2[6]);
	
//printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d \n", b1[0], b1[1],b1[2], b1[3],b2[0], b2[1],b2[2], b2[3]);


}



return 0;

}

