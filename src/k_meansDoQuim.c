#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define N 10000000
#define K 4

typedef struct Cluster{

    float x;
    float y;
    int nr_pontos;

}Cluster;

typedef struct Ponto{

    float x;
    float y;
    int cluster;

}Ponto;


static inline void inicializa(Ponto *v, Cluster *clusters){
  
    srand(10);

    for(int i = 0; i < N; i++) {

        v[i].x = (float) rand() / RAND_MAX;
        v[i].y = (float) rand() / RAND_MAX;
        v[i].cluster=-1;

    }

    for(int i = 0; i < K; i++) {
        clusters[i].x = v[i].x;
        clusters[i].y = v[i].y;
        clusters[i].nr_pontos = 0;
    }

}


inline int k_meansAux(Ponto *v, Cluster *clusters){
    
    Cluster *centroid = malloc(sizeof(Cluster)*K);
    float distance, min;
    int indMin = 0, converge = 1;

    memset(centroid,0,sizeof(Ponto)*K);

    for(int i = 0; i < N; i++){

        // Primeira iteração
        min = ((v[i].x - clusters[0].x) * (v[i].x - clusters[0].x)) + ((v[i].y - clusters[0].y) * (v[i].y - clusters[0].y));
        indMin = 0;

        for(int j=1;j<K;j++){

            distance = ((v[i].x - clusters[j].x) * (v[i].x - clusters[j].x)) + ((v[i].y - clusters[j].y) * (v[i].y - clusters[j].y));
            if(distance < min){
                min = distance;
                indMin = j;
            }
            
        }

        if(v[i].cluster!=indMin){
            v[i].cluster=indMin;
            converge = 0;
        }

        centroid[indMin].nr_pontos++;
        centroid[indMin].x += v[i].x;
        centroid[indMin].y += v[i].y;
    }

    for(int i = 0; i < K; i++){

        clusters[i].x = centroid[i].x/centroid[i].nr_pontos;
        clusters[i].y = centroid[i].y/centroid[i].nr_pontos;
        clusters[i].nr_pontos = centroid[i].nr_pontos;

    }

    return converge;

}

int k_means(Ponto *v, Cluster *clusters){

    int i = 0;
    
    while(!k_meansAux(v,clusters)){
        i++;
    }

    return i;

}

int main(){

    Ponto *v;
    Cluster *clusters;
    int iter;

    v = malloc(sizeof(Ponto)*N);

    clusters = malloc(sizeof(Cluster)*K);

    inicializa(v,clusters);
    iter = k_means(v,clusters);

    printf("N = %d, K = %d\n",N,K);
    
    for(int i=0;i<K;i++){
        printf("Center: (%.3f,%.3f), Size: %d\n",clusters[i].x,clusters[i].y,clusters[i].nr_pontos);
    }
    printf("Iterations: %d\n",iter);

    return 0;

}
