#include <stdlib.h>
#include <stdio.h>
#include "tsp.h"

void insertion_sort(int *A,int length){
	int min ,i ,j ,temp ;
	for (i = 0; i < length; ++i)
	{
		min = A[i] ;
		for (j = i; j < length; ++j)
		{
			if (A[j] < min )
			{
				min = A[j] ;
				temp = A[i] ;
				A[i] = A[j] ;
				A[j] = temp ;
			}
		}
	}	
}

double random0to1(){
    int temp ;
    temp = rand() ;
    return ((double) temp) / RAND_MAX ;
}


int random_upn_wo0(int n ){
	int temp ;
	temp = rand() % n ;
	if(temp > 0)
		return temp ;
	else 
		return random_upn_wo0(n) ;
}

int random_upn_w0(int n ){
	int temp ;
	temp = rand() % n ;
	return temp ;
}

void crossover(int *A,int *B ,int length){
	int auxA[length] ;
	int cross_1 = random_upn_wo0(length - 1) ,cross_2 = random_upn_wo0(length - 1) ,i ;
	while(cross_1 == cross_2 || cross_1 == cross_2 + 1 || cross_2 == cross_1 + 1){cross_2 = random_upn_wo0(length - 1);}
	if (cross_1 > cross_2)
	{
		cross_1 = cross_1 ^ cross_2 ; cross_2 = cross_1 ^ cross_2 ; cross_1 = cross_1 ^ cross_2 ;
	}

	for (i = 0; i < length; ++i)
	{
		auxA[i] = -1 ;
	}
	int counta ,countb ,cond = 0 ;
	counta = cross_2 ;
	countb = cross_2 ;
	while(counta != cross_1 + 1){
		cond = 0 ;
		if (counta == length)
		{
			counta = 0 ;
			continue ;
		}
		if (countb == length)
		{
			countb = 0 ;
			continue ;
		}
		for (i = cross_1 + 1 ; i < cross_2 ; ++i)
		{
			if (B[countb] == A[i])
			{
				countb++;
				cond = 1 ;
				break ;
			}
		}
		if(cond == 0){auxA[counta++] = B[countb++] ;}
		
	}

	counta = cross_2 ;
	countb = cross_2 ;
	while(countb != cross_1 + 1){
		cond = 0 ;
		if (counta == length)
		{
			counta = 0 ;
			continue ;
		}
		if (countb == length)
		{
			countb = 0 ;
			continue ;
		}
		for (i = cross_1 + 1 ; i < cross_2 ; ++i)
		{
			if (A[counta] == B[i])
			{
				counta++;
				cond = 1 ;
				break ;
			}
		}
		if(cond == 0){B[countb++] = A[counta++] ;}
	}
	for (i = 0; i < length; ++i)
	{
		if (auxA[i] != -1 )
		{
			A[i] = auxA[i] ;
		}
	}
}

void mutate(int *A,int length){
	int p1 = random_upn_w0(length),p2 = random_upn_w0(length), temp ;
	temp = A[p1] ;
	A[p1] = A[p2] ;
	A[p2] = temp ;
}
double fitness(int *A,int **dist ,int length){
	double sum = 0 ;
	int i ;
	for (i = 0; i < length - 1; ++i)
	{
		sum += dist[A[i] - 1][A[i+1] - 1];
	}
	sum += dist[A[length - 1] - 1][A[0] - 1] ;
	return 1 / sum ;
}
