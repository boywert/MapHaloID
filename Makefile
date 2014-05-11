all:
	mpicc --std=c99 src/main.c -L/home1/01937/cs390/MapHaloID/sqlite/lib/ -I/home1/01937/cs390/MapHaloID/sqlite/include -o test -lsqlite3
