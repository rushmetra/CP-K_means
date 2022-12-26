CC = gcc
MPICC = mpicc
BIN = bin/
SRC = src/
EXECS = k_means_seq
EXECP = k_means_par
EXECMPI = k_means_mpi
THREADS = 16

CFLAGS = -O2
MPIFLAGS = -np 

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXECS)
	$(CC) $(CFLAGS) -fopenmp $(SRC)k_means.c -o $(BIN)$(EXECP)
	$(MPICC) $(CFLAGS) $(SRC)k_means_mpi.c -o $(BIN)$(EXECMPI)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXECS) 10000000 $(CP_CLUSTERS)

runpar:
	./$(BIN)$(EXECP) 10000000 $(CP_CLUSTERS) $(THREADS)

runmpi:
	mpirun $(MPIFLAGS) $(PROCESSES) ./$(BIN)$(EXECMPI) 10000000 $(CP_CLUSTERS)