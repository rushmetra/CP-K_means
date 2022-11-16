CC = gcc
BIN = bin/
SRC = src/
EXECS = k_means_seq
EXECP = k_means_par
THREADS = 8

CFLAGS = -O2

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXECS)
	$(CC) $(CFLAGS) -fopenmp $(SRC)k_means.c -o $(BIN)$(EXECP)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXECS) 10000000 $(CP_CLUSTERS)

runpar:
	./$(BIN)$(EXECP) 10000000 $(CP_CLUSTERS) $(THREADS)
