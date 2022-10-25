#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define N 10000000 // 10 000 000
#define K 4

typedef struct Ponto{

    float x;
    float y;
    int n_pontos;//se for centroid é size

}Ponto;




void inicializa(float *x,float *y,int *cluster, Ponto *clusters){
  
    srand(10);

    for(int i = 0; i < N; i++) {

        x[i] = (float) rand() / RAND_MAX;
        y[i] = (float) rand() / RAND_MAX;

    }

    for(int i = 0; i < K; i++) {
        clusters[i].x = x[i];
        clusters[i].y = y[i];
        clusters[i].n_pontos = 0;
    }

    float distance, min = 1;

    for(int i = 0; i < N; i++){

        for(int j=0;j<K;j++){

            distance = ((x[i] - clusters[j].x) * (x[i] - clusters[j].x)) + ((y[i] - clusters[j].y) * (y[i] - clusters[j].y));
            if(distance < min){
                
                min = distance;
                clusters[cluster[i]].n_pontos--;
                cluster[i]=j;
                clusters[j].n_pontos++;

            }

        }

            min = 1;

    }

}


int k_meansAux(float *x,float *y,int *cluster, Ponto *clusters){
    
    float soma0X=0, soma1X=0, soma2X=0, soma3X=0;
    float soma0Y=0, soma1Y=0, soma2Y=0, soma3Y=0;
    float n_pontos0=0, n_pontos1=0, n_pontos2=0, n_pontos3=0;
    Ponto centroid[K];

    for(int i = 0; i < N; i++){

        switch (cluster[i]){

            case 0:

                soma0X+=x[i];
                soma0Y+=y[i];
                n_pontos0++;
                break;

            case 1:

                soma1X+=x[i];
                soma1Y+=y[i];
                n_pontos1++;
                break;

            case 2:

                soma2X+=x[i];
                soma2Y+=y[i];
                n_pontos2++;
                break;

            case 3:

                soma3X+=x[i];
                soma3Y+=y[i];
                n_pontos3++;
                break;
            }

    }

    centroid[0].x = soma0X/n_pontos0;
    centroid[0].y = soma0Y/n_pontos0;
    centroid[1].x = soma1X/n_pontos1;
    centroid[1].y = soma1Y/n_pontos1;
    centroid[2].x = soma2X/n_pontos2;
    centroid[2].y = soma2Y/n_pontos2;
    centroid[3].x = soma3X/n_pontos3;
    centroid[3].y = soma3Y/n_pontos3;


    float distance, min = 1;

    for(int i = 0; i < N; i++){

        for(int j=0;j<K;j++){

            distance = ( (x[i] - centroid[j].x) * (x[i] - centroid[j].x)) + ( (y[i] - centroid[j].y) * (y[i] - centroid[j].y));
            if(distance < min){
                
                min = distance;
                clusters[cluster[i]].n_pontos--;
                cluster[i]=j;
                clusters[j].n_pontos++;

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

    

    clusters[0].x = centroid[0].x;
    clusters[0].y = centroid[0].y;
    clusters[1].x = centroid[1].x;
    clusters[1].y = centroid[1].y;
    clusters[2].x = centroid[2].x;
    clusters[2].y = centroid[2].y;
    clusters[3].x = centroid[3].x;
    clusters[3].y = centroid[3].y;

    return muda;

}

int k_means(float *x,float *y,int *cluster, Ponto *clusters){

    int muda = 1, i = 0;
    
    while(muda){

        if((muda = k_meansAux(x,y,cluster,clusters))){
            i++;
        }

    }

    return i;

}



int main(){

    float *x, *y;
    Ponto *clusters;
    int iter, *cluster;

    x = malloc(sizeof(float)*N);
    y = malloc(sizeof(float)*N);
    cluster = malloc(sizeof(int)*N);
    clusters = malloc(sizeof(Ponto)*K);

    inicializa(x,y,cluster,clusters);
    iter = k_means(x,y,cluster,clusters);

    printf("N = %d, K = %d\n",N,K);
    
    for(int i=0;i<K;i++){
        printf("Center: (%.3f,%.3f), Size: %d\n",clusters[i].x,clusters[i].y,clusters[i].n_pontos);
    }
    printf("Iterations: %d\n",iter);

    return 0;

}
