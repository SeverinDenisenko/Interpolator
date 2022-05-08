//
// Created by Severin on 28.02.2022.
//

#ifndef NUMERICAL_TASK_2_1_INTERPOLATION_H
#define NUMERICAL_TASK_2_1_INTERPOLATION_H

int uniform(double *data, double *result, double a, double b, int n, int q);
int optimized_uniform(double *data, double *result, double a, double b, int n, int q);
int chebyshev(double *data, double *result, double a, double b, int n, int q);

#endif //NUMERICAL_TASK_2_1_INTERPOLATION_H
