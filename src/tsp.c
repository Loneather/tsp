#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tsp.h"
#define POPL 40 
#define GENS 10000
#define p_mut 0.1
#define p_cross 0.5
#define p_tourn 0.75

int evolve(int cities ,int **dist){

	/* Number of cities entry */

	srand(time(NULL)) ;

	/* Static Tables */
	double maxf_archive[GENS+1] ;
	double avf_archive[GENS+1] ;
	double bins[POPL] ;
	/*Dynamic 2-D tables */
    int *temppop[POPL] ,i ;
    for (i=0; i<POPL; i++)
         temppop[i] = (int *)malloc(cities * sizeof(int));

    int *f_archive[GENS+1];
    for (i=0; i<GENS+1; i++)
         f_archive[i] = (int *)malloc(cities * sizeof(int));

    int *population[POPL];
    for (i=0; i<POPL; i++)
         population[i] = (int *)malloc(cities * sizeof(int));

	/* Variables */
	double temp = 0 ,tempa = 0 ,tempb = 0 ;
	double fitsum ,maxfit = 0 ;
	double sumofbins = 0 ;
	double check_sel = 0 ,check_cross = 0 ,check_mut = 0 ,check_tour = 0;
	int    max_place , findmax ,findplace ;
	int    j ,start ,l ;
	int    gencount = 0 , k ;
	int    counta ,countb ,tempcount ;


	/* Population Entry */
	/* Create first cluster */
	for (i = 0; i < POPL / 2; ++i)
	{
		for (j = 0; j < cities; ++j)
		{
			population[i][j] = j + 1 ;
		}
	}

	/* Create second cluster */
	for (i = POPL / 2; i < POPL; ++i)
	{
		for (j = 0; j < cities; ++j)
		{
			population[i][j] = cities - j  ;
		}
	}

	/* Randomising the 0th population */
	for (i = 0; i < POPL; ++i)
	{
		for (j = 0; j < 6; ++j)
		{
			mutate(population[i] ,cities) ;
		}
	}

	/*Find fittest and average of the 0th generation */
	max_place = 0 ;
	for (i = 0; i < POPL; ++i)
	{
		temp = fitness(population[i],dist ,cities);
		avf_archive[gencount] = avf_archive[gencount] + temp ;
		if (temp > maxf_archive[gencount])
		{
			maxf_archive[gencount] = temp ;
			max_place = i ;
		}
	}
	avf_archive[gencount] = avf_archive[gencount] / ((double) POPL) ;
	for (i = 0; i < cities; ++i)
	{
		f_archive[gencount][i] = population[max_place][i] ;
	}
	gencount++;	

	while(gencount < GENS)
	{
		/*Empty bin(ranges) */
		for (i = 0; i < POPL; ++i)
		{
			bins[i] = 0 ;
		}

		/* Empty temporary population */
		for (i = 0; i < POPL; ++i)
		{
			for (j = 0; j < cities; ++j)
				{
					temppop[i][j] = 0 ;
				}	
		}

		/* Start of selection proccess */
		fitsum = 0.0 ;
		for (i = 0; i < POPL; ++i)
		 {
		 	fitsum = fitness(population[i],dist ,cities) + fitsum ;
		 } 

		/* Create ranges */
		sumofbins = 0 ;
		for (i = 0; i < POPL; ++i)
		{
			bins[i] = (fitness(population[i],dist ,cities) / fitsum) + sumofbins ;
			sumofbins = (fitness(population[i],dist ,cities) / fitsum) + sumofbins ;
		}

		/* Create temporary population */
		tempcount = 0 ;
		while(tempcount < POPL)
		{
			check_sel = 0 ;
		 	check_sel = random0to1() ;
		 	for (i = 0; i < POPL; ++i)
		 	{
		 		if (i == 0 )
		 		{
		 			if (0 <= check_sel && check_sel < bins[i] )
		 			{
		 				for (k = 0; k < cities; ++k)
		 				{
		 					temppop[tempcount][k] = population[i][k] ;
		 				}
		 				tempcount++;
		 			}
		 		}
		 		else
		 		{
		 			if (bins[i-1] <= check_sel && check_sel < bins[i]){
		 				for (k = 0; k < cities; ++k)
		 					{
								temppop[tempcount][k] = population[i][k] ;
		 					}
		 				tempcount++;
		 			}
		 		}
		 	}
		}

		/* Tournament Selection */
		/* Pairs two consecutive chromosomes and favors the fittest to replace the 
		weaker */
		counta = 0 ;
		countb = 1 ;
		for (i = 0; i < POPL/2; ++i)
		{
			check_tour = random0to1() ;
			tempa = fitness(temppop[counta],dist ,cities);
			tempb = fitness(temppop[countb],dist ,cities) ;

			if (check_tour < p_tourn)
			{

				if (tempa > tempb )
				{
					for (j = 0; j < cities; ++j)
					{
						temppop[countb][j] = temppop[counta][j];
					}
				}
				else
					for (j = 0; j < cities; ++j)
					{
						temppop[counta][j] = temppop[countb][j];
					}
			}
			else
			{
				if (tempa < tempb )
				{
					for (j = 0; j < cities; ++j)
					{
						temppop[countb][j] = temppop[counta][j];
					}
				}
				else
					for (j = 0; j < cities; ++j)
					{
						temppop[counta][j] = temppop[countb][j];
					}
			}
			counta = counta + 2 ;
			countb = countb + 2 ;
		}

		/* Crossover */ 
		counta = 0 ;
		countb = 1 ;
		for (i = 0; i < POPL / 2; ++i)
		{
			check_cross = random0to1() ;
			if (check_cross < p_cross)
			{
				crossover(temppop[counta],temppop[countb],cities) ;
			}
			counta = counta + 2 ;
			countb = countb + 2 ;
		}

		/* Mutation */
		check_mut = 0 ;
		for (i = 0; i < POPL; ++i)
		{
			check_mut = random0to1() ;
			if (check_mut < p_mut)
			{
				mutate(temppop[i] ,cities) ;
			}
		}

		/* Temporary population becomes next generation */
		for (i = 0; i < POPL; ++i)
		{
			for (j = 0; j < cities; ++j)
			{
				population[i][j] = temppop[i][j] ;
			}
		}
		
		/* Find fittest and average of this population */
		max_place = 0 ;
		for (i = 0; i < POPL; ++i)
		{
			temp = fitness(population[i],dist ,cities);
			avf_archive[gencount] = avf_archive[gencount] + temp ;
			if (temp > maxf_archive[gencount])
			{
				maxf_archive[gencount] = temp ;
				max_place = i ;
			}
		}
		avf_archive[gencount] = avf_archive[gencount] / ((double) POPL) ;
		for (i = 0; i < cities; ++i)
		{
			f_archive[gencount][i] = population[max_place][i] ;
		}
		/* Print the results of current generation */		
		printf("Generation %d: BFit = %f  AvFit = %04.4f BLength = %f \n" ,gencount ,maxf_archive[gencount] ,avf_archive[gencount],1 / maxf_archive[gencount]);
		gencount++;
	}

	/* Find max of all generations */
	findmax = maxf_archive[0] ;
	findplace = 0 ;
	for (i = 1; i < GENS+1; ++i)
	{
		if (maxf_archive[i] > findmax)
		{
			findmax = maxf_archive[i] ;
			findplace = i - 1;
		}
	}

	printf("\nBest chromosome is : ");
	for (i = 0; i < cities; ++i)
	{
		printf("%d ",f_archive[findplace][i]) ;
	}
	
	/* Print results */
	printf("\nPath Length = %f \n",1/maxf_archive[findplace]);

	for (i = 0; i < cities; ++i)
	{
		free(dist[i]);
	}
	free(dist) ;
}


