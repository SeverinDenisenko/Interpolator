//
// Created by Severin on 28.02.2022.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "interpolation.h"

double uniform_x(int k, int n, double a, double b)
{
    return a + (b - a) / n * k;
}

double chebyshev_x(int k, int n, double a, double b)
{
    return (a + b) / 2.0 + (a - b) / 2.0 * cos((2.0 * k + 1.0) / (2.0 * n + 2.0) * M_PI);
}

int uniform(double *data, double *result, double a, double b, int n, int q)
{

    for (int k = 0; k < n * q + 1; ++k)
    {
        double x = uniform_x(k, n * q, a, b);
        double basics_polynomial = 1;
        double lagrange_polynomial = 0;

        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                if (j == i)
                {
                    continue;
                }
                basics_polynomial *= (x - uniform_x(j, n, a, b)) / (uniform_x(i, n, a, b) - uniform_x(j, n, a, b));
            }
            lagrange_polynomial += basics_polynomial * data[i];
            basics_polynomial = 1;
        }

        result[k] = lagrange_polynomial;
    }

    return 0;
}

int chebyshev(double *data, double *result, double a, double b, int n, int q)
{
    double *chebyshev_nodes = (double *)malloc(sizeof(double) * (n + 1));
    for (int k = 0; k < n + 1; k++)
    {
        chebyshev_nodes[k] = chebyshev_x(k, n, a, b);
    }

    double *basics_polynomial = (double *)malloc(sizeof(double) * (n + 1));

    for (int k = 0; k < n * q + 1; ++k)
    {
        double x = uniform_x(k, n * q, a, b);
        double lagrange_polynomial = 0;

        for (int i = 0; i < n + 1; i++)
        {
            for (int k = 0; k < n + 1; k++)
            {
                basics_polynomial[k] = 1;
            }

            for (int j = 0; j < n + 1; j++)
            {
                for (int l = 0; l < n + 1; l++)
                {
                    if (j == l)
                    {
                        continue;
                    }
                    basics_polynomial[j] *= (x - chebyshev_nodes[l]) / (chebyshev_nodes[j] - chebyshev_nodes[l]);
                }
            }

            lagrange_polynomial += basics_polynomial[i] * data[i];
        }

        result[k] = lagrange_polynomial;
    }

    free(chebyshev_nodes);
    free(basics_polynomial);

    return 0;
}
