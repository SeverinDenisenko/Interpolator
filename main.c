//
// Created by Severin on 28.02.2022.
//

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include "interpolation.h"

int main(int argc, char *argv[]){

    // Creating and opening files

    FILE *DATA, *RESULT;

    // Reading commandline arguments

    if (argc != 2){
        printf("Usage: interpolator -u or -c\n");
        exit(1);
    }

    int opt;
    while((opt = getopt(argc, argv, "uc")) != -1)
    {
        switch(opt)
        {
            case 'u':
                DATA = fopen("uniform.dat", "r");
                RESULT = fopen("res_uniform.dat", "w+");
                break;
            case 'c':
                DATA = fopen("chebyshev.dat", "r");
                RESULT = fopen("res_chebyshev.dat", "w+");
                break;
            default:
                printf("Usage: interpolator -u or -c\n");
                exit(1);
        }
        break;
    }

    if (DATA == NULL){
        printf("Error: source .dat file doesn't exist.\n");
        exit(1);
    }

    if (RESULT == NULL){
        printf("Error: can't create the result.dat.\n");
        exit(1);
    }

    // Reading data

    if(getc(DATA) != '#'){
        printf("Error: file in wrong format.\n");
        exit(1);
    }

    int n; // Source number of intervals;
    int q = 50; // Final number of intervals is n*q
    double a, b; // Source interval

    fscanf(DATA, "%d", &n);
    fscanf(DATA, "%lf", &a);
    fscanf(DATA, "%lf", &b);

    double *data = malloc(sizeof(double) * (n + 1));
    double *result = malloc(sizeof(double) * (q * n + 1));

    if (data == NULL || result == NULL){
        printf("Error allocating space.\n");
        exit(1);
    }

    for (int i = 0; i < n + 1; ++i) {
        fscanf(DATA, "%lf", &data[i]);
    }

    // Performing interpolation

    switch(opt)
    {
        case 'u':
            uniform(data, result, a, b, n, q);
            break;
        case 'c':
            chebyshev(data, result, a, b, n, q);
            break;
    }

    // Writing file

    fprintf(RESULT, "# %d\n", n * q);
    fprintf(RESULT, "%lf %lf\n", a, b);

    for (int i = 0; i < n * q + 1; ++i) {
        fprintf(RESULT, "%lf\n", result[i]);
    }

    fclose(DATA);
    fclose(RESULT);

    free(data);
    free(result);

    return 0;
}