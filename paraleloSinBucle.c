#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define TAM 1000000

sem_t suma_total;
int total = 0;
int vect1[TAM];
int vect2[TAM];
pthread_mutex_t lock;

struct parametros_hilo{
    int min;
    int max;
    int suma_temp;
};

void prodVect(void* parametros){
    struct parametros_hilo* params = (struct parametros_hilo*) parametros;
    int tmp_suma = 0;

    for (int i = params->min; i < params->max; ++i) {
        tmp_suma += vect1[i]*vect2[i];
    }

    //int sem_suma = sem_trywait(&suma_total);
     pthread_mutex_lock(&lock);
//    if (sem_suma == 0) {
//        total += tmp_suma;
//    }
    total += tmp_suma;
    pthread_mutex_unlock(&lock);
    //sem_post(&suma_total);
    printf("total:%d\n",total);

}

int main(int argc, char const *argv[])
{
    int num;
    int num1;

    FILE *mi_archivo1;
    FILE *mi_archivo2;
    int numHilos = atoi(argv[3]);
    pthread_t hilos_ids[numHilos];

    mi_archivo1 = fopen(argv[1],"r");
    mi_archivo2 = fopen(argv[2],"r");

    int i = 0;
    while(fscanf(mi_archivo1,"%d",&num)>0){
        printf("%d\n", num );
        vect1[i] = num;
        i++;
    }
    printf("--------- Fin Vector 1 ---------\n");

    i=0;
    while(fscanf(mi_archivo2,"%d",&num1)>0){
        printf("%d\n", num1 );
        vect2[i] = num1;
        i++;
    }
    printf("--------- Fin Vector 1 ---------\n");

    int porcion = TAM/numHilos;
    struct parametros_hilo paramHilo[numHilos];
    for (int i = 0; i < numHilos; ++i) {
        // Aquí puede estar la porcion de cada vector para cada hilo. ej: porcion += TAM/numHilos
        //struct parametros_hilo paramHilo;
        paramHilo[i].min = i*porcion;
        paramHilo[i].max = (i+1)*porcion;
    }
    for (int i = 0; i < numHilos; ++i) {
        pthread_create(&hilos_ids[i], NULL, (void *)prodVect, &paramHilo[i]);
    }

    for (int i = 0; i < numHilos; ++i) {
        pthread_join(hilos_ids[i], NULL);
    }
    printf("El producto vectorial entre los dos vectores de %d numeros es: %d\n",TAM,total);

    return 0;
}
