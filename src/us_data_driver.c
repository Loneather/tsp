#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "tsp.h"

FILE * fp ;

const double PI = 3.141592 ;
const double RRR = 6378.388 ;
void getuntil(char *str){
	char str1[100] = "0" ;
	while(strcmp(str,str1)){
		fscanf(fp,"%s",str1);
	}
}

void getuntilnumber(void){
	int c ;
	c = fgetc(fp) ;
	while(c < '0' || c > '9'){
		c = fgetc(fp) ;
	}
	ungetc(c,fp) ;
}
void getuntilch(int ch){
	while(ch != fgetc(fp)){}
}
int euc_2d_dist(long xi,long yi,long xj,long yj){
	long dx ,dy ;
	dx = xj - xi ;
	dy = yj - yi ;

	return round_to_int(sqrt((dx*dx) + (dy*dy)));
}
int round_to_int(double x){
	return (int) (x + 0.5) ;

}
double get_ltd(double x){
	int deg ;
	double min ;
	deg = round_to_int(x) ;
	min = x - deg ;
	return (PI * (deg + 5.0 * min / 3.0) / 180.0) ; 
}
double get_lat(double x){
	int deg ;
	double min ;
	deg = round_to_int(x) ;
	min = x - deg ;
	return (PI * (deg + 5.0 * min / 3.0) / 180.0) ; 
}

int geo_dist(double x1,double x2,double y1 ,double y2){
	double latx = get_lat(x1),ltdx = get_ltd(x2) ,laty = get_lat(y1) ,ltdy = get_ltd(y2) ;

	double q1 ,q2 ,q3 ;
	q1 = cos(ltdx - ltdy) ;
	q2 = cos(latx - laty) ;
	q3 = cos(latx + laty) ;
	return (int) ((RRR * acos(0.5*((1.0+q1)*q2 - (1.0-q1)*q3)) + 1.0)) ;
}
int pseudo_euc_2d(int x1 ,int x2,int y1 ,int y2){
	int xd = x1 - y1 ;
	int yd = x2 - y2 ;
	double r = sqrt((xd*xd + yd*yd) / 10.0) ;
	int t = round_to_int(r) ;
	if(t < r){return (t + 1) ;}
	return t ;
}

int main(int argc, char const *argv[])
{
	char str1[100] ,str2[100] ;
	int i ;
	int cities ,start ,j ;

	if (argc == 1) // no argument
	{
		scanf("%d",&cities) ;
		int **dist = (int **)malloc(cities * sizeof(int *));
		for (i=0; i<cities; i++)
		{
		    dist[i] = (int *)malloc(cities * sizeof(int));
		}
		start = 1 ;
		for (j = 0; j < cities; ++j)
		{
			for (i = start; i < cities; ++i)
			{
				scanf("%d",&dist[j][i]) ;
				dist[i][j] = dist[j][i];
			}
		start++;
		}
		for (i = 0; i < cities; ++i)
		{
			dist[i][i] = 0 ;
		}
		evolve(cities,dist) ;
	}
	if (argc == 2) //-c argument 
	{
		scanf("%d",&cities);
		int **dist = (int **)malloc(cities * sizeof(int *));
		for (i=0; i<cities; i++)
		{
		    dist[i] = (int *)malloc(cities * sizeof(int));
		}
		start = 1 ;
		for (j = 0; j < cities; ++j)
		{
			for (i = start; i < cities; ++i)
			{
				scanf("%d",&dist[j][i]) ;
				dist[i][j] = dist[j][i];
			}
		start++;
		}
		for (i = 0; i < cities; ++i)
		{
			dist[i][i] = 0 ;
		}	    
		int ispath[cities] ,checkpath[cities] ;
		for (i = 0; i < cities; ++i)
		{
			scanf("%d",&ispath[i]);
			checkpath[i] = ispath[i] ;
		}	
		insertion_sort(checkpath,cities);
		for (i = 0; i < cities; ++i)
		{
			if (checkpath[i] != i + 1)
			{
				return 1 ;
			}
		}	
		printf("Path Length %f\n",1 / fitness(ispath,dist ,cities));
		return 0 ;

	}
	if(argc == 3) //-i argument 
	{
		fp = fopen(argv[2],"r") ;
		getuntilch(':') ; //NAME
		getuntilch(':') ; //TYPE
		getuntilch(':') ; //COMMENT
		getuntilch(':') ; //DIMENSION
		fscanf(fp,"%d",&cities) ; //GET DIMENSION
		getuntilch(':'); //EDGE_WEIGHT_TYPE
		fscanf(fp,"%s",str1) ; //GET EDGE_WEIGHT_TYPE
		int **dist = (int **)malloc(cities * sizeof(int *));
		for (i=0; i<cities; i++)
		{
		    dist[i] = (int *)malloc(cities * sizeof(int));
		}
 		if (!strcmp(str1,"EUC_2D") )
		{
 			getuntilnumber() ;
			double dud ,start ;
			int j ;

			double **coordinates = (double **)malloc(cities * sizeof(double *));
			for (i=0; i<cities; i++)
			{
		 		coordinates[i] = (double *)malloc(2 * sizeof(double));
			}

			for (i = 0; i < cities; ++i)
 			{
				fscanf(fp,"%lf %lf %lf",&dud ,&coordinates[i][0] ,&coordinates[i][1] ); 
  			}
  			for (i = 0; i < cities; ++i)
  			{
  				printf("%lf %lf\n",coordinates[i][0] ,coordinates[i][1] );
  			}
			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = euc_2d_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}
			evolve(cities,dist) ;
 		}
 		else if(!strcmp(str1,"GEO"))
 		{
 			getuntilnumber() ;
 			int start ,j ;
			double **coordinates = (double **)malloc(cities * sizeof(double *));
			for (i=0; i<cities; i++)
			{
		 		coordinates[i] = (double *)malloc(2 * sizeof(double));
			}
			double dud ,round1 ,round2 ;
 			for (i = 0; i < cities; ++i)
 			{
				getuntilnumber(); //ignore space 
				fscanf(fp,"%lf %lf %lf",&dud ,&round1 ,&round2 ); 
				coordinates[i][0] = round1 ;
				coordinates[i][1] = round2 ;
  			}

			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
					dist[j][i] = geo_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
					dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}

			evolve(cities,dist) ;
 		}
 		else if(!strcmp(str1,"ATT"))
 		{
 			getuntilnumber() ;
 			int start ,j ;
			int **coordinates = (int **)malloc(cities * sizeof(int *));

			for (i=0; i<cities; i++)
			{
		 		coordinates[i] = (int *)malloc(2 * sizeof(int));
			}
 			double dud ,round1 ,round2 ;
 			for (i = 0; i < cities; ++i)
 			{
				fscanf(fp,"%lf %lf %lf",&dud ,&round1 ,&round2 ); 
				coordinates[i][0] = round_to_int(round1) ;
				coordinates[i][1] = round_to_int(round2) ;
  			}

			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = pseudo_euc_2d(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}

			evolve(cities,dist) ;
		}
 		else if (!strcmp(str1,"EXPLICIT"))
 		{
 			getuntilch(':');
 			fscanf(fp,"%s",str2);
 			if (!strcmp(str2,"FULL_MATRIX"))
 			{
 				getuntilnumber() ;
 				int start ,j ;

 				for (i = 0; i < cities; ++i)
 				{
 					for (j = 0; j < cities; ++j)
 					{
 						fscanf(fp,"%d",&dist[i][j]) ;
 					}
 				}
				printf("..OK..\n");		
 			}
 			else if(!strcmp(str2,"UPPER_ROW"))
 			{
 				getuntilnumber() ;
	 			int start ,j ;

				start = 1 ;
				for (j = 0; j < cities; ++j)
				{
					for (i = start; i < cities; ++i)
					{
						fscanf(fp,"%d",&dist[j][i]) ;
						dist[i][j] = dist[j][i];
					}
				start++;
				}
				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}

				printf("..ok..\n");

			}
 			else if(!strcmp(str2,"LOWER_DIAG_ROW"))
 			{
 				getuntilnumber() ;
	 			int end ,j ,bin ;
	 			end = 1 ;
				for (i = 1; i < cities; ++i)
				{
					fscanf(fp,"%d",&bin) ;
					for (j = 0; j < end; ++j)
					{
						fscanf(fp,"%d",&dist[i][j]) ;
						dist[j][i] = dist[i][j] ;
					}
					end++;
				}

				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}

				printf("...ok...\n");
			}
 			else if(!strcmp(str2,"UPPER_DIAG_ROW"))
 			{
 				getuntilnumber() ;
	 			int start ,j ,bin ;

				start = 1 ;
				for (j = 0; j < cities; ++j)
				{
					fscanf(fp,"%d",&bin) ;
					for (i = start; i < cities; ++i)
					{
						fscanf(fp,"%d",&dist[j][i]) ;
						dist[i][j] = dist[j][i];
					}
				start++;
				}
				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}

				printf("...ok...\n");
			}				
			evolve(cities,dist) ;
		}
 		else if (!strcmp(str1,"CEIL_2D"))
 		{
 			getuntilnumber() ;
			long dud ,start ,j ;

			long **coordinates = (long **)  malloc(cities * sizeof(long *));
			for (i = 0; i < cities; ++i)
			{
				coordinates[i] = (long *) malloc(2 * sizeof(long ));
			}

			for (i = 0; i < cities; ++i)
 			{
				fscanf(fp,"%ld %ld %ld",&dud ,&coordinates[i][0] ,&coordinates[i][1] ); 
  			}

			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = euc_2d_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}

			printf("..OK..\n");
			evolve(cities,dist) ;
		}
		fclose(fp) ;
	}
	if (argc == 4)//-c -i argument
	{
		fp = fopen(argv[3],"r") ;
		getuntilch(':') ; //NAME
		getuntilch(':') ; //TYPE
		getuntilch(':') ; //COMMENT
		getuntilch(':') ; //DIMENSION
		fscanf(fp,"%d",&cities) ; //GET DIMENSION
		getuntilch(':'); //EDGE_WEIGHT_TYPE
		fscanf(fp,"%s",str1) ; //GET EDGE_WEIGHT_TYPE
		int **dist = (int **)malloc(cities * sizeof(int *));
		for (i=0; i<cities; i++)
		{
		    dist[i] = (int *)malloc(cities * sizeof(int));
		}
		if (!strcmp(str1,"EUC_2D") )
		{
			getuntilnumber() ;
			int dud ,start ,j ;

			int **coordinates = (int **)malloc(cities * sizeof(int *));
			for (i=0; i<cities; i++)
			{
				coordinates[i] = (int *)malloc(2 * sizeof(int));
			}

			for (i = 0; i < cities; ++i)
			{
				fscanf(fp,"%d %d %d",&dud ,&coordinates[i][0] ,&coordinates[i][1] ); 
			}

			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = euc_2d_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}
		}
		else if(!strcmp(str1,"GEO"))
		{
			getuntilnumber() ;
			int start ,j ;
			
			int **coordinates = (int **)malloc(cities * sizeof(int *));
			for (i=0; i<cities; i++)
			{
				coordinates[i] = (int *)malloc(2 * sizeof(int));
			}
			double dud ,round1 ,round2 ;
			for (i = 0; i < cities; ++i)
			{
				getuntilnumber(); //ignore space 
				fscanf(fp,"%lf %lf %lf",&dud ,&round1 ,&round2 ); 
				coordinates[i][0] = round_to_int(round1) ;
				coordinates[i][1] = round_to_int(round2) ;
			}

			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = geo_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}
		}
		else if(!strcmp(str1,"ATT"))
		{
			getuntilnumber() ;
			int start ,j ;

			int **coordinates = (int **)malloc(cities * sizeof(int *));
			for (i=0; i<cities; i++)
			{
				coordinates[i] = (int *)malloc(2 * sizeof(int));
			}
			double dud ,round1 ,round2 ;
			for (i = 0; i < cities; ++i)
			{
				fscanf(fp,"%lf %lf %lf",&dud ,&round1 ,&round2 ); 
				coordinates[i][0] = round_to_int(round1) ;
				coordinates[i][1] = round_to_int(round2) ;
			}
			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
					dist[j][i] = pseudo_euc_2d(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
					dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}
		}
		else if (!strcmp(str1,"EXPLICIT"))
		{
			getuntilch(':');
			fscanf(fp,"%s",str2);

			if (!strcmp(str2,"FULL_MATRIX"))
			{
				getuntilnumber() ;
				int start ,j ;
				int **dist = (int **)malloc(cities * sizeof(int *));
				for (i=0; i<cities; i++)
				{
					dist[i] = (int *)malloc(cities * sizeof(int));
				}

				for (i = 0; i < cities; ++i)
				{
					for (j = 0; j < cities; ++j)
					{
						fscanf(fp,"%d",&dist[i][j]) ;
					}
				}

				for (i = 0; i < cities; ++i)
				{
					for (j = 0; j < cities; ++j)
					{
						printf("%d ",dist[i][j]);
					}
					putchar('\n');
				}
				printf("..OK..\n");	

			}
			else if(!strcmp(str2,"UPPER_ROW"))
			{
				getuntilnumber() ;
				int start ,j ;

				start = 1 ;
				for (j = 0; j < cities; ++j)
				{
					for (i = start; i < cities; ++i)
					{
						fscanf(fp,"%d",&dist[j][i]) ;
						dist[i][j] = dist[j][i];
					}
				start++;
				}
				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}
				printf("..ok..\n");

			}
			else if(!strcmp(str2,"LOWER_DIAG_ROW"))
			{
				getuntilnumber() ;
				int end ,j ,bin ;

				end = 1 ;
				for (i = 1; i < cities; ++i)
				{
					fscanf(fp,"%d",&bin) ;
					for (j = 0; j < end; ++j)
					{
						fscanf(fp,"%d",&dist[i][j]) ;
						dist[j][i] = dist[i][j] ;
					}
					end++;
				}

				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}

			}
			else if(!strcmp(str2,"UPPER_DIAG_ROW"))
			{
				getuntilnumber() ;
				int start ,j ,bin ;

				start = 1 ;
				for (j = 0; j < cities; ++j)
				{
					fscanf(fp,"%d",&bin) ;
					for (i = start; i < cities; ++i)
					{
						fscanf(fp,"%d",&dist[j][i]) ;
						dist[i][j] = dist[j][i];
					}
				start++;
				}
				for (i = 0; i < cities; ++i)
				{
					dist[i][i] = 0 ;
				}
				printf("...ok...\n");
			}
		}
		else if (!strcmp(str1,"CEIL_2D"))
		{
			getuntilnumber() ;
			int start ,j ;

			long **coordinates = (long **)  malloc(cities * sizeof(long *)),dud ;
			for (i = 0; i < cities; ++i)
			{
				coordinates[i] = (long *) malloc(2 * sizeof(long ));
			}
			for (i = 0; i < cities; ++i)
			{
				fscanf(fp,"%ld %ld %ld",&dud ,&coordinates[i][0] ,&coordinates[i][1] ); 
			}
			start = 1 ;
			for (j = 0; j < cities; ++j)
			{
				for (i = start; i < cities; ++i)
				{
				dist[j][i] = euc_2d_dist(coordinates[i][0],coordinates[i][1],coordinates[j][0],coordinates[j][1]);
				dist[i][j] = dist[j][i];
				}
			start++;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}
			for (i = 0; i < cities; ++i)
			{
				dist[i][i] = 0 ;
			}	    
		}
		fclose(fp) ;
		int ispath[cities] ,checkpath[cities] ;
		for (i = 0; i < cities; ++i)
		{
			scanf("%d",&ispath[i]);
			checkpath[i] = ispath[i] ;
		}	
		insertion_sort(checkpath,cities);
		for (i = 0; i < cities; ++i)
		{
			if (checkpath[i] != i + 1)
			{
				return 1 ;
			}
		}	
		printf("Path Length %lf\n",1 / fitness(ispath,dist ,cities));
		return 0 ;
	}
	return 0;
}