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
        printf("Error: file .dat doesn't exist.\n");
        exit(1);
    }

    // Reading data

    if(getc(DATA) != '#'){
        printf("Error: file in wrong format.\n");
        exit(1);
    }

    int n;
    double a, b;
    fscanf(DATA, "%d", &n);
    fscanf(DATA, "%lf", &a);
    fscanf(DATA, "%lf", &b);


    return 0;
}