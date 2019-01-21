#define MAXN 1000    /* Define this before including nauty.h */
#define MAXCHAR 1000
#include "nauty.h"   /* which includes <stdio.h> and other system files */

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
int i,i1,i2,i3,i4,i5,i8,j,j1,j2,j3,j4,j5,k,l,m,n,a,c,d,e,f,h,f1,e1,d1,c1,c2,flag1,flag2,u,test,u1,x1,x2,x3,y1,y2,y3;
//unsigned int bin;
//unsigned int bin2;
FILE *file;

int b[n];
int q[n];
int b1[n];
int b2[n];


static DEFAULTOPTIONS_GRAPH(options);
	statsblk stats;
	size_t k1;
	//int i1,i2,i3;
	unsigned int x;			//Used to test how to read graphs
  	
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

for(i = 0; i < count; i++){

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
		//printf("%d \n", b[k]);
		continue;
		
	}

	while((e+d)<n){ 

		
		//printf("e=%d, d=%d, u = %d, h = %d \n", e,d,u,h);
		
		nzero(q,n);
		q[u] = h;
		printf("u = %d\n", u);
		//printf("q[2] = %d \n", q[2]);
		printf(" q%d is %d %d %d %d %d %d %d \n",h, q[0],q[1],q[2],q[3],q[4],q[5],q[6]);

		//e = first(b2,n);
		//d = first(b1,n);

		//if(d+e == n){
		//	break
		//}
			
		
		if(u %2 == 0){
			//e = first(b2,n);
			//e1 = e;

			//printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);

			for(i1= 0; i1<a; i1++){
				if(notin(b2,b[i1],n)==1){
					b2[e] = b[i1];
					e+=1;
				}
			}
			
			//printf(" b   2 is %d %d %d %d \n", b2[0],b2[1],b2[2],b2[3]);

			h = b2[f];

			//printf("h = %d, f = %d \n", h,f);

			f1+=1;

			x2 = POPCOUNT(g1[i][h]);
			a = x2;
			//printf("x2=%d \n", x2);
			zero(b,n);
			for(i2 = 0; i2<x2; i2++){
				TAKEBIT(b[i2],g1[i][h]);    //0 to WORDSIZE -1
				continue;
			}

			//printf(" b%d is %d %d %d %d %d %d %d\n",h, b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
			//printf(" q%d is %d %d %d %d %d %d %d\n",h, q[0],q[1],q[2],q[3],q[4],q[5],q[6]);

			c1 = 0;

			for(i3 = 0; i3<x2; i3++){
				if(notin(q,b[i3],n)==0){
					c1+=1;
				}
			}
			
			printf("c1=%d \n", c1);
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
				x3 = POPCOUNT(g1[i][h]);
				a = x3;
				printf("x3=%d \n", x3);

				zero(b,n);
				for(i4 = 0; i4<x3; i4++){
					TAKEBIT(b[i4],g1[i][h]);    //0 to WORDSIZE -1
					continue;
				}

					
	
				c1 = 0;

				for(i5 = 0; i5<x3; i5++){
					if(notin(q,b[i5],n)==0){
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
			//d = first(b1,n);
			//d1 = d;
			for(j1= 0; j1<a; j1++){
				if(notin(b1,b[j1],n)==1){
					b1[d] = b[j1];
					d+=1;
				}
			}

			//printf(" b      1 is %d %d %d %d \n",b1[0],b1[1],b1[2],b1[3]);
	
			f +=1;
			
			h = b1[f1];
			//printf("f1 = %d, h = %d,f = %d \n", f1,h,f);

			y2 = POPCOUNT(g1[i][h]);
			a = y2;
			//printf("y2=%d \n", y2);
			
			zero(b,n);
			for(j2 = 0; j2<y2; j2++){
				TAKEBIT(b[j2],g1[i][h]);    //0 to WORDSIZE -1
				continue;
			}

			//printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);

			c2 = 0;

			for(j3 = 0; j3<y2; j3++){
				//printf("j3 = %d \n", j);
				if(notin(q,b[j3],n)==0){
					c2 += 1;
				}
			}
			
			//printf("c2=%d \n", c2);
			//printf(" b%d is %d %d %d %d \n",h, b[0],b[1],b[2],b[3]);
			//printf(" q%d is %d %d %d %d \n",h, q[0],q[1],q[2],q[3]);			
			
			if(c2 == first(b,n)){
				flag2 = 1;
				f1+=1;
				h = b1[f1];
				
			}

			else{
				flag2 =0;
			}

			while(flag2 == 1 && f1 != n){
				y3 = POPCOUNT(g1[i][h]);
				a = y3;

				zero(b,n);
				for(j4 = 0; j4<y3; j4++){
					TAKEBIT(b[j4],g1[i][h]);    //0 to WORDSIZE -1
					continue;
				}

				c2 = 0;

				for(j5 = 0; j5<y3; j5++){
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


	}
	
	
		printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d,b1[4] = %d,b1[5] = %d,b1[6] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d,b2[4] = %d,b2[5] = %d,b2[6] = %d \n", b1[0], b1[1],b1[2], b1[3],b1[4], b1[5],b1[6],b2[0], b2[1],b2[2], b2[3],b2[4], b2[5],b2[6]);
	
//printf("b1[0] = %d, b1[1] = %d, b1[2] = %d ; b1[3] = %d; b2[0] = %d, b2[1] = %d, b2[2] = %d, b2[3] = %d \n", b1[0], b1[1],b1[2], b1[3],b2[0], b2[1],b2[2], b2[3]);


}



return 0;

}

