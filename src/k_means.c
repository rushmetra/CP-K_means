#include <stdio.h>
#include <stdlib.h>

//#define N 10000000
//#define K 32

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

    #pragma omp parallel for
    for(int i = 0; i < K; i++) {
        clusters[i].x = x[i];
        clusters[i].y = y[i];
        clusters[i].nr_pontos = 0;
    }

}


int k_meansAux(float *x, float *y, Cluster *clusters, int N, int K){
    
    Cluster *centroid_novo = malloc(sizeof(Cluster)*K);
    float x_centroid[K], y_centroid[K], nr_pontos[K];
    
    #pragma omp parallel for
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
    
    #pragma omp parallel for private(min,indMin,distance) reduction(+:x_centroid,y_centroid,nr_pontos)
    for(int i = 0; i < N; i++){

        // Primeira iteração
        min = ((x[i] - clusters[0].x) * (x[i] - clusters[0].x)) + ((y[i] - clusters[0].y) * (y[i] - clusters[0].y));
        indMin = 0;
        //float *arr = malloc(sizeof(float)*K);

        //#pragma omp parallel for private(min,indMin,distance)// aqui entra num loop "infinito"
        for(int j=1;j<K;j++){

            //arr[j] = ((x[i] - clusters[j].x) * (x[i] - clusters[j].x)) + ((y[i] - clusters[j].y) * (y[i] - clusters[j].y));
            
            distance = ((x[i] - clusters[j].x) * (x[i] - clusters[j].x)) + ((y[i] - clusters[j].y) * (y[i] - clusters[j].y));

            if(distance < min){
                min = distance;
                indMin = j;
            }
            
        }

        // min = arr[0];
        // for(int j=1;j<K;j++){

        //     //if(arr[j]<min) indMin=j-1;
        //     //else indMin=j;
        //     indMin = arr[j]<min ? j-1 : j;

        // }
    
        nr_pontos[indMin] += 1;
        x_centroid[indMin] += x[i];
        y_centroid[indMin] += y[i];
    
    }

    #pragma omp parallel for
    for(int i = 0; i < K; i++){

        centroid_novo[i].x = x_centroid[i]/nr_pontos[i];
        centroid_novo[i].y = y_centroid[i]/nr_pontos[i]; 
        centroid_novo[i].nr_pontos = nr_pontos[i];

    }

    #pragma omp parallel for reduction(||:muda)
    for(int i = 0; i<K; i++){
        if((centroid_novo[i].x!=clusters[i].x || centroid_novo[i].y!=clusters[i].y)){
            muda = 1;
            //break;
        }
        else{
            muda = 0;
        }
    }
    
    #pragma omp parallel for
    for(int i=0;i<K;i++){
        clusters[i].x = centroid_novo[i].x;
        clusters[i].y = centroid_novo[i].y;
        clusters[i].nr_pontos = centroid_novo[i].nr_pontos;
    }

    return muda;

}

int k_means(float *x, float *y, Cluster *clusters, int N, int K){

    int i = 0;
    
    while(i<20){
        k_meansAux(x,y,clusters, N, K);
        i++;
    }

    return i;

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

    inicializa(x,y,clusters, N, K);
    iter = k_means(x,y,clusters, N, K);

    printf("N = %d, K = %d\n",N,K);
    
    for(int i=0;i<K;i++){
        printf("Center: (%.3f,%.3f), Size: %d\n",clusters[i].x,clusters[i].y,clusters[i].nr_pontos);
    }
    printf("Iterations: %d\n",iter);

    return 0;

}
