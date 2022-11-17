#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Cluster{

    float x;
    float y;
    int nr_pontos;

}Cluster;

void inicializa(float *x, float *y, Cluster *clusters, int N, int K){
  
    srand(10);

    // O rand não é thread safe
    for(int i = 0; i < N; i++) {

        x[i] = (float) rand() / RAND_MAX;
        y[i] = (float) rand() / RAND_MAX;

    }

    for(int i = 0; i < K; i++) {
        clusters[i].x = x[i];
        clusters[i].y = y[i];
        clusters[i].nr_pontos = 0;
    }

}

int k_meansAux(float *x, float *y, Cluster *clusters, int N, int K){
    
    Cluster *centroid_novo = malloc(sizeof(Cluster)*K);
    float x_centroid[K], y_centroid[K], nr_pontos[K];
    
    /* Inicialization of the centroids */
    for(int i = 0; i < K; i++){
        x_centroid[i] = 0;
        y_centroid[i] = 0;
        nr_pontos[i] = 0;

        centroid_novo[i].x = 0;
        centroid_novo[i].y = 0;
        centroid_novo[i].nr_pontos = 0;
    }

    int indMin = 0, muda = 0;
    float distance, min = 1;
    
    /* Assignment of each point to its nearest centroid */
    #pragma omp parallel for private(min,indMin,distance) reduction(+:x_centroid,y_centroid,nr_pontos)
    for(int i = 0; i < N; i++){

        /* First iteration */
        min = ((x[i] - clusters[0].x) * (x[i] - clusters[0].x)) + ((y[i] - clusters[0].y) * (y[i] - clusters[0].y));
        indMin = 0;
        
        for(int j=1;j<K;j++){
            
            distance = ((x[i] - clusters[j].x) * (x[i] - clusters[j].x)) + ((y[i] - clusters[j].y) * (y[i] - clusters[j].y));

            if(distance < min){
                min = distance;
                indMin = j;
            }
            
        }

        nr_pontos[indMin] += 1;
        x_centroid[indMin] += x[i];
        y_centroid[indMin] += y[i];
    
    }

    /* Calculation of the new centroid */
    for(int i = 0; i < K; i++){

        centroid_novo[i].x = x_centroid[i]/nr_pontos[i];
        centroid_novo[i].y = y_centroid[i]/nr_pontos[i]; 
        centroid_novo[i].nr_pontos = nr_pontos[i];

    }

    /* Check if the centroids have moved to determine if another iteration is necessary */
    for(int i = 0; i<K; i++) 
        muda = muda || (centroid_novo[i].x!=clusters[i].x || centroid_novo[i].y!=clusters[i].y);
    
    /* Update the old centroid to the newly calculated one */
    for(int i=0;i<K;i++){
        clusters[i].x = centroid_novo[i].x;
        clusters[i].y = centroid_novo[i].y;
        clusters[i].nr_pontos = centroid_novo[i].nr_pontos;
    }

    return muda;

}

int k_means(float *x, float *y, Cluster *clusters, int N, int K){

    int i = 0;
    
    while(i<=20){
        k_meansAux(x,y,clusters, N, K);
        i++;
    }

    return i-1;

}

int main(int argc, char* argv[]){

    float *x, *y;
    Cluster *clusters;
    int iter;
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    x = malloc(sizeof(float)*N);
    y = malloc(sizeof(float)*N);
    clusters = malloc(sizeof(Cluster)*K);

    #ifdef _OPENMP
    int nThreads = atoi(argv[3]);
    omp_set_num_threads(nThreads);
    #endif
    
    inicializa(x,y,clusters, N, K);
    iter = k_means(x,y,clusters, N, K);

    printf("N = %d, K = %d\n",N,K);
    
    for(int i=0;i<K;i++){
        printf("Center: (%.3f,%.3f), Size: %d\n",clusters[i].x,clusters[i].y,clusters[i].nr_pontos);
    }
    printf("Iterations: %d\n",iter);


    return 0;

}
