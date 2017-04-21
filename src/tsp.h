#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random0to1(void) ;
int random_upn(int ) ;
int random_upn_w0(int );
void crossover(int *,int *,int ) ;
double fitness(int*,int** ,int ) ;
void insertion_sort(int *,int ) ;
int evolve(int ,int**) ;
void initialize(int **a,int size,int length);
void yates_shuffle(int *mat,int length);
void swap(int *a,int *b);
