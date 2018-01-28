CC = clang
WRN = -Wall -Wextra -pedantic
DBG = -g3
OPT = -O2
MATH = -lm

tsp : tsp.o tsp_flib.o us_data_driver.o
	$(CC) tsp.o tsp_flib.o us_data_driver.o -o tsp $(WRN) $(DBG) $(OPT) $(MATH)
tsp_flib.o : tsp_flib.c
	$(CC) -c tsp_flib.c $(WRN) $(DBG) $(OPT)
tsp.o : tsp.c
	$(CC) -c tsp.c $(WRN) $(DBG) $(OPT)
us_data_driver.o : us_data_driver.c
	$(CC) -c us_data_driver.c $(WRN) $(DBG) $(OPT)

clean:
	rm -r *.o
