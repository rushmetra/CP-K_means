CC = gcc
MPICC = mpicc
BIN = bin/
SRC = src/
EXECS = k_means_seq
EXECP = k_means_par
EXECMPI = k_means_mpi
THREADS = 16

CFLAGS = -O2

.DEFAULT_GOAL = k_means


k_means:
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXECS)
	$(CC) $(CFLAGS) -fopenmp $(SRC)k_means.c -o $(BIN)$(EXECP)
	$(MPICC) $(CFLAGS) $(SRC)k_means_mpi.c -o $(BIN)$(EXECMPI)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXECS) $(AMOSTRAS) $(CP_CLUSTERS)

runpar:
	./$(BIN)$(EXECP) $(AMOSTRAS) $(CP_CLUSTERS) $(THREADS)

runmpi_physical:
	mpirun -np $(PROCESSES) ./$(BIN)$(EXECMPI) $(AMOSTRAS) $(CP_CLUSTERS)

runmpi_threads:
	mpirun --use-hwthread-cpus -np $(PROCESSES) ./$(BIN)$(EXECMPI) $(AMOSTRAS) $(CP_CLUSTERS)

test_all:
	sh test_all.sh