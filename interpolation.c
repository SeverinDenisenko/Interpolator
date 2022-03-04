//
// Created by Severin on 28.02.2022.
//

#include "math.h"
#include "stdio.h"

#include "interpolation.h"

double uniform_x(int k, int n){
    return 2.0 * (double) k / (double) n - 1.0;
}

double chebyshev_x(int k, int n){
    return cos(M_PI * (2.0*(double)k + 1.0)/(2.0*(double)n + 2.0));
}

int uniform(double *data, double *result, double a, double b, int n, int q){

    for (int k = 0; k < n * q + 1; ++k) {

        double x = uniform_x(k, n * q);
        double basics_polinomial = 1;
        double lagrange_polinomial = 0;

        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                if (j == i) {
                    continue;
                }
                basics_polinomial *= (x - uniform_x(j, n))/(uniform_x(i, n) - uniform_x(j, n));
            }
            lagrange_polinomial += basics_polinomial * data[i];
            basics_polinomial = 1;
        }

        result[k] = lagrange_polinomial;
    }

    return 0;
}

int chebyshev(double *data, double *result, double a, double b, int n, int q){

    for (int k = 0; k < n * q + 1; ++k) {

        double x = chebyshev_x(k, n * q);
        double basics_polinomial = 1;
        double lagrange_polinomial = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j == i) {
                    continue;
                }
                basics_polinomial *= (x - chebyshev_x(j, n))/(chebyshev_x(i, n) - chebyshev_x(j, n));
            }
            lagrange_polinomial += basics_polinomial * data[i];
        }

        result[k] = lagrange_polinomial;
    }

    return 0;
}
