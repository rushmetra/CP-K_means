#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define N 10000000 // 10 000 000
#define K 4

typedef struct Ponto{

    float x;
    float y;
    int cluster;//se for centroid é size

}Ponto;




void inicializa(Ponto *v, Ponto *clusters){
  
    srand(10);
    Ponto p;
    float distance, min = 1;
    p.cluster=-1;

    for(int i = 0; i < N; i++) {

        p.x = (float) rand() / RAND_MAX;
        p.y = (float) rand() / RAND_MAX;
        v[i] = p;

    }

    for(int i = 0; i < K; i++) {
        clusters[i].x = v[i].x;
        clusters[i].y = v[i].y;
        clusters[i].cluster = 0;
    }


    for(int i = 0; i < N; i++){

        distance = ((v[i].x - clusters[0].x) * (v[i].x - clusters[0].x)) + ((v[i].y - clusters[0].y) * (v[i].y - clusters[0].y));
        if(distance < min){

            min = distance;                   
            v[i].cluster=0;
            clusters[0].cluster++;

        }

        for(int j=1;j<K;j++){

            distance = ((v[i].x - clusters[j].x) * (v[i].x - clusters[j].x)) + ((v[i].y - clusters[j].y) * (v[i].y - clusters[j].y));
            if(distance < min){
                
                min = distance;
                clusters[v[i].cluster].cluster--;                 
                v[i].cluster=j;
                clusters[j].cluster++;

            }

        }

            min = 1;

    }

}


int k_meansAux(Ponto *v, Ponto *clusters){
    
    Ponto *medias = malloc(sizeof(Ponto)*K);
    Ponto *centroid = malloc(sizeof(Ponto)*K);
    float distance, min = 1;

    for(int i=0;i<K;i++){
        medias[i].x = 0;
        medias[i].y = 0;
        medias[i].cluster = 0; //aqui é número de pontos
    }

    for(int i = 0; i < N; i++){
    
        medias[v[i].cluster].x+=v[i].x;
        medias[v[i].cluster].y+=v[i].y;
        medias[v[i].cluster].cluster++; //aqui é número de pontos       

    }

    for(int i=0;i<K;i++){

        centroid[i].x = medias[i].x/medias[i].cluster; //aqui é número de pontos
        centroid[i].y = medias[i].y/medias[i].cluster; //aqui é número de pontos

    }

    for(int i = 0; i < N; i++){

        for(int j=0;j<K;j++){

            distance = ( (v[i].x - centroid[j].x) * (v[i].x - centroid[j].x)) + ( (v[i].y - centroid[j].y) * (v[i].y - centroid[j].y));
            if(distance < min){
                
                min = distance;
                clusters[v[i].cluster].cluster--;
                v[i].cluster=j;
                clusters[j].cluster++;

            }

        }

            min = 1;

    }

    int muda;

    for(int i = 0; i<K; i++){
        if(!(centroid[i].x==clusters[i].x && centroid[i].y==clusters[i].y)){
            muda = 1;
            break;
        }
        else{
            muda = 0;
        }
    }

    
    for(int i=0;i<K;i++){
        clusters[i].x = centroid[i].x;
        clusters[i].y = centroid[i].y;
    }

    return muda;

}

int k_means(Ponto *v, Ponto *clusters){

    int muda = 1, i = 0;
    
    while(muda){

        if((muda = k_meansAux(v,clusters))){
            i++;
        }

    }

    return i;

}



int main(){

    Ponto *v;
    Ponto *clusters;
    int iter;

    v = malloc(sizeof(Ponto)*N);
    clusters = malloc(sizeof(Ponto)*K);

    inicializa(v,clusters);
    iter = k_means(v,clusters);

    printf("N = %d, K = %d\n",N,K);
    
    for(int i=0;i<K;i++){
        printf("Center: (%.3f,%.3f), Size: %d\n",clusters[i].x,clusters[i].y,clusters[i].cluster);
    }
    printf("Iterations: %d\n",iter);

    return 0;

}
