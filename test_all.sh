make
export CLUSTERS=4

export AMOSTRAS=10000000
echo "Vai executar 5 vezes com $AMOSTRAS amostras e $CLUSTERS clusters, openMP"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runpar >> output.out
export AMOSTRAS=50000000
echo "Vai executar 5 vezes com $AMOSTRAS amostras e $CLUSTERS clusters, openMP"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runpar >> output.out
export AMOSTRAS=100000000
echo "Vai executar 5 vezes com $AMOSTRAS amostras e $CLUSTERS clusters, openMP"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runpar >> output.out

sleep 1

export AMOSTRAS=10000000
export PROCESSES=4

export CLUSTERS=4
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out
export CLUSTERS=8
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out
export CLUSTERS=16
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out
export CLUSTERS=32
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out

sleep 1

export AMOSTRAS=10000000
export CLUSTERS=4

export PROCESSES=2
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out
export PROCESSES=4
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos: MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_physical >> output.out
export PROCESSES=8
echo "Vai executar 5 vezes com $AMOSTRAS amostras, $CLUSTERS clusters e $PROCESSES processos (aqui algum são virtuais): MPI"
perf stat -o output.out --append -r 5 -e instructions,cycles,L1-dcache-load-misses,l2_rqsts.all_demand_miss -M cpi make runmpi_threads >> output.out
