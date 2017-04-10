#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAM 1000

int main(int argc, char const *argv[])
{
    int num;
    int num1;
    FILE *mi_archivo1;
    FILE *mi_archivo2;
    mi_archivo1 = fopen(argv[1], "r");
    mi_archivo2 = fopen(argv[2], "r");
    int *vect1 = malloc(TAM*sizeof(int));;
    int *vect2 = malloc(TAM*sizeof(int));;
    int suma;
    int i = 0;
    while (fscanf(mi_archivo1, "%d", &num) > 0) {
        printf("%d\n", num );
        vect1[i] = num;
        i++;
    }
    printf("--------- Fin Vector 1 ---------\n");
    i = 0;
    while (fscanf(mi_archivo2, "%d", &num1) > 0) {
        printf("%d\n", num1 );
        vect2[i] = num1;
        i++;
    }
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    printf("--------- Fin Vector 2 ---------\n");
    for (int i = 0; i < TAM; ++i) {
        suma += vect1[i] * vect2[i];
    }
    printf("El producto vectorial entre los dos vectores de %d numeros es: %d\n", TAM, suma);
    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - begin.tv_sec) +
                     ((end.tv_usec - begin.tv_usec) / 1000000.0);
    printf("Tiempo Transcurrido: %f segundos.\n", elapsed);

    return 0;
}
