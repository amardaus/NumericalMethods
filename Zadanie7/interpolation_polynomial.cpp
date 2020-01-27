//
// Created by olcia on 27.12.2019.
//

#include <gsl/gsl_matrix.h>
#include <cmath>
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <iomanip>

int main(){
    double x[] = {0.062500, 0.187500, 0.312500, 0.437500, 0.562500, 0.687500, 0.812500, 0.935700};
    double fx[] = {0.687959, 0.073443, -0.517558, -1.077264, -1.600455, -2.080815, -2.507266, -2.860307};

    int n = sizeof(x)/sizeof(x[0]);
    double* data = new double[n*n];

    for(int i = 0; i < n; i++){
        std::cout << x[i] << " " << fx[i] << std::endl;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            data[i*n+j] = pow(x[i],j);
            //std::cout << data[i*n+j] << " ";
        }
        //std::cout << std::endl;
    }

    gsl_matrix_view m = gsl_matrix_view_array(data, n, n);
    gsl_vector_view b = gsl_vector_view_array(fx, n);
    gsl_vector* res = gsl_vector_alloc(n);
    gsl_permutation* p = gsl_permutation_alloc(n);
    int s;

    gsl_linalg_LU_decomp(&m.matrix, p, &s);
    gsl_linalg_LU_solve(&m.matrix, p, &b.vector, res);

    std::cout << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << std::setprecision(5) << gsl_vector_get(res, n-i-1) << " ";
    }

    std::cout << std::endl;
    for(double d = -1.0; d <= 1.0; d += 0.001){
        double tmp = 0;
        for(int i = 0; i < n; i++){
            tmp += gsl_vector_get(res, i) * pow(d,i);
        }
        //std::cout << d << " " << tmp << std::endl;
    }

    gsl_permutation_free(p);
    gsl_vector_free(res);
}