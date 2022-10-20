#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define N 10000000 // 10 000 000
#define K 4

typedef struct Ponto{

    float x;
    float y;
    int cluster;

}Ponto;




void inicializa(Ponto *v, Ponto *clusters){
  
    srand(10);
    Ponto p;
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

    float distance, min = 1;

    for(int i = 0; i < N; i++){

        for(int j=0;j<K;j++){

            distance = sqrt(pow((v[i].x - clusters[j].x),2) + pow((v[i].y - clusters[j].y),2));
            if(distance <= min){
                
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
    
    float soma0X=0, soma1X=0, soma2X=0, soma3X=0;
    float soma0Y=0, soma1Y=0, soma2Y=0, soma3Y=0;
    float n_pontos0=0, n_pontos1=0, n_pontos2=0, n_pontos3=0;
    Ponto centroid[K];

    for(int i = 0; i < N; i++){

        switch (v[i].cluster){

            case 0:

                soma0X+=v[i].x;
                soma0Y+=v[i].y;
                n_pontos0++;
                break;

            case 1:

                soma1X+=v[i].x;
                soma1Y+=v[i].y;
                n_pontos1++;
                break;

            case 2:

                soma2X+=v[i].x;
                soma2Y+=v[i].y;
                n_pontos2++;
                break;

            case 3:

                soma3X+=v[i].x;
                soma3Y+=v[i].y;
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

            distance = sqrt(pow( (v[i].x - centroid[j].x),2) + pow( (v[i].y - centroid[j].y),2));
            if(distance <= min){
                
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
        else
            muda = 0;

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

int k_means(Ponto *v, Ponto *clusters){

    int muda = 1, i = 0;
    
    while(muda){

        muda = k_meansAux(v,clusters);
        i++;

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

    printf("Center: (%f,%f), Size: %d\n",clusters[0].x,clusters[0].y,clusters[0].cluster);
    printf("Center: (%f,%f), Size: %d\n",clusters[1].x,clusters[1].y,clusters[1].cluster);
    printf("Center: (%f,%f), Size: %d\n",clusters[2].x,clusters[2].y,clusters[2].cluster);
    printf("Center: (%f,%f), Size: %d\n",clusters[3].x,clusters[3].y,clusters[3].cluster);
    printf("Iterações: %d\n",iter);

    return 0;

}
