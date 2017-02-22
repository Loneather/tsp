# tsp
==TRAVELLING SALESMAN PROBLEM==

=COMPILATION=
Go to src directory and run the following commands:
--$gcc -c tsp.c -o ../obj/tsp.o -lm 
--$gcc -c tsp_flib.c -o ../obj/tsp_flib.o -lm
--$gcc -c us_data_driver.c -o ../obj/us_data_driver.o -lm

Go to obj directory run:
--$gcc *.o -o ../bin/tsp -lm 

Go to bin and run the programm from there 

=OPTIONS=
* no argument
input data from stdin .First input the number of cities ,then input the weights as an upper triangular matrix.
*-c argument
input data from stdin .First input the number of cities ,then input the weights as an upper triangular matrix.
Then input the path that you want to check 
*-i argument 
the data is inputed from a .tsp file after -i give the path to the file 
*-c -i argument 
the data is inputed from a .tsp file after -i give the path to the file and finally the path you want to check.

=DESCRIPTION
All the parameters are defined as constants .
The number of x variables the programm is to maximize are given in the command line as argument.The programm also uses the math.h library as well as the time.h and stdlib.h/stdio.h .To change the parameters you have to change the source file and then re-compile the programm (see COMPILATION)

-Tournament Selection

	Tournament selection is a selection operator that     determines based 
	on a random number which of the 2 members of the  species   will    be 
	promoted and replace the other.Tournament selection favors  the fitter
	of the competing members 
	Reference [http://watchmaker.uncommons.org/manual/ch03s04.html]

Default Parameters
------------------------------------------------------------------------------------------------------
Name 	Value 		Description
------------------------------------------------------------------------------------------------------
POPL 	10			Sets the population number 
GENS 	50			Sets the maximum number of generations
p_mut	0.1			Sets the possibility of mutation 
p_cross 0.3 		Sets the possibility of crossover
p_tourn 0.65		Sets the possibility of the fittest wining the tournament 

-Libraries
stdio
stdlib
time 
math.h 
